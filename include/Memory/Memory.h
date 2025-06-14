#pragma once
#include <stdint.h>
#include <iostream>

#include "APU/APU.h"

// GB Memory consists of memory addressed from 0000 to FFFF (2^16-1)
// Only addresses 8000 - 9FFF and C000 - FFFF are stored on the GB itself
using address = unsigned short;
constexpr unsigned int VRAMSize = 0x2000; // 8000 - 9FFF
constexpr unsigned int WRAMSize = 0x2000; // C000 - DFFF
constexpr unsigned int OAMSize = 0x00A0; // FE00 - FE9F
constexpr unsigned int IORegisterCount = 0x0080; // FF00 - FF7F
constexpr unsigned int HRAMSize = 0x007F; // FF80 - FFFE

// Each address points to 8 bits (1 byte) of data
using byte = uint8_t;

// GB Cartridges can contain up to 512 ROM Banks each 16KiB in size
constexpr unsigned int maxROMBanks = 512;
constexpr unsigned int ROMBankSize = 0x4000;

class ROMBank {
private:
	byte data[ROMBankSize]{ 0 };

public:
	byte& read(address addr) { return data[addr]; }

	// Only for use when reading from ROM Files
	void write(address addr, byte val) { data[addr] = val; }
};

// And up to 16 RAM Banks each 8KiB in size
constexpr unsigned int maxRAMBanks = 16;
constexpr unsigned int RAMBankSize = 0x2000;

// And up to 20 cartridge registers
constexpr unsigned int maxCartRegs = 20;

class RAMBank {
private:
	byte data[RAMBankSize]{ 0 };

public:
	byte& read(address addr) { return data[addr]; }

	void write(address addr, byte val) { data[addr] = val; }
};

// Number of ROM Banks and RAM Banks used will depend on the MBC inside the loaded cartridge
enum MBC {
	None,
	MBC1,
	MBC2,
	MBC3,
	MBC5,
	MBC6,
	MBC7,
	MMM01,
	M161,
	HuC1,
	HuC3,
};

class GBMemory {
private:
	// Memory mapped in the following way
	// 0000 - 3FFF: 16KiB ROM Bank 0          (From Cartridge)
	// 4000 - 7FFF: 16Kib ROM Bank 1          (From Cartridge) 
	// 8000 - 9FFF: 8 KiB Video RAM           (CGB Mode have switchable banks)
	// A000 - BFFF: 8 KiB External RAM	      (From Cartridge)
	// C000 - CFFF: 4 KiB Work RAM
	// D000 - DFFF: 4 KiB Work RAM            (CGB Mode have switchable banks)
	// E000 - FDFF: Mirror of C000 - DDFF     
	// FE00 - FE9F: Object-Attribute-Memory 
	// FEA0 - FEFF: Unused                    (Use Prohibited => Not Emulated)
	// FF00 - FF7F: I/O Registers
	// FF80 - FFFE: High RAM
	// FFFF - FFFF: Interrupt Enable Register

	byte VRAM[VRAMSize]{ 0 };
	byte WRAM[WRAMSize]{ 0 };
	byte OAM[OAMSize]{ 0 };
	byte IORegs[IORegisterCount]{ 0 };
	byte HRAM[HRAMSize]{ 0 };
	byte IntEnableReg{ 0 };

	ROMBank ROMBanks[maxROMBanks];
	RAMBank RAMBanks[maxRAMBanks];

	// Actual number of ROM and RAM banks is determined by the inserted cartridge
	int ROMBankCount{ 0 };
	int RAMBankCount{ 0 };

	// Have 2 active ROMBanks and 1 active RAM bank at any given time
	int ROMBank0Index{ 0 };
	int ROMBank1Index{ 1 };
	int RAMBankIndex{ 0 };

	// Value to be returned if attempting to read an inaccesible address
	byte garbageVal{ 0xFF };

	// Additional cartridge features are enabled dependant on the MBC
	MBC MBCType{ None };
	
	// MBC's come with built in registers, their functionalities differ between MBC's
	// Details found here: https://gbdev.io/pandocs/MBCs.html
	byte MBCRegs[maxCartRegs]{ 0 };

	// MBC's with timers built in need to keep track of their ticks
	int MBCTicks{ 0 };

	// Need to be linked to APU in order to write to its registers
	GBAPU* APU;

public:
	GBMemory(GBAPU* APU) : APU{ APU } {};

	// Current Mode of the PPU can lock certain parts of memory
	int PPUMode{ 0 }; // Mode is 0, 1, 2, or 3

	// Lot of timing depends on how the DIV register (address: FF04) changes
	byte prevDivVal{ 0 };

	// Flag to set whenever DIV register (0xFF04) is written to so that timer can be reset
	bool resetTimer{ false };

	// Keep track of current step in DMA transfer (if one is occuring)
	int currDMAStep{ 0xA0 };

	// Flag to set when a DMA Transfer is ongoing
	bool isDMATransfer{ false };

	// Resets all values in memory to their default state
	void init();

	// Sets initial values for IO registers (as specified by the boot rom)
	void initIO();

	// Loads a given ROM into memory
	void loadROM(std::string filePath);

	// Returns the value inside a given RAM Address (if it is currently accessible)
	byte read(address addr);

	// Returns the value inside a given RAM Address (no check for accessibility)
	// Returns a reference so the caller can freely change values stored in memory
	byte& PPURead(address addr);

	// Writes a value to a given address (if it is currently accessible)
	void write(address addr, byte newVal);

	// Writes a value to an IO register (many of these have bits which are read-only)
	void IOWrite(address addr, byte newVal);

	// Writes a value to the JOYP register (only called by the input controller)
	void JOYPWrite(byte newVal) { IORegs[0x00] = newVal; }

	// Update the current state of the Memory (step thru DMA, update timer on cartridge)
	void update();

	// Performs an OAM DMA Transfer based on the value stored in address 0xFF46
	void BeginDMATransfer();
	void DMATransferStep();

	// Attempting to read/write an address in the range 0x0000 - 0x7FFF or the range 0xA000 - 0xBFFF will behave differently depending on the MBC
	byte MBCRead(address addr);
	void MBCWrite(address addr, byte newVal);

	// Various functions to be used dependant on the current MBC
	byte noMBCRead(address addr);
	void noMBCWrite(address addr, byte newVal);

	byte MBC1Read(address addr);
	void MBC1Write(address addr, byte newVal);

	byte MBC3Read(address addr);
	void MBC3Write(address addr, byte newVal);
	void MBC3TimerTick();

	byte MBC5Read(address addr);
	void MBC5Write(address addr, byte newVal);
};