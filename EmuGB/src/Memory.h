#pragma once
#include <stdint.h>
#include <iostream>

// GB Memory consists of memory addressed from 0000 to FFFF (2^16-1)
using address = unsigned short;
constexpr unsigned int addressCount = 65536; // 2^16

// Each address points to 8 bits (1 byte) of data
using byte = uint8_t;

class GBMemory {
private:
	byte data[addressCount]{ 0 };
	// Memory mapped in the following way
	// 0000 - 3FFF: 16KiB ROM Bank 0          (From Cartridge)
	// 4000 - 7FFF: 16Kib ROM Bank 1          (From Cartridge) 
	// 8000 - 9FFF: 8 KiB Video RAM           (CGB Mode have switchable banks)
	// A000 - BFFF: 8 KiB External RAM	      (From Cartridge)
	// C000 - CFFF: 4 KiB Work RAM
	// D000 - DFFF: 4 KiB Work RAM            (CGB Mode have switchable banks)
	// E000 - FDFF: Mirror of C000 - DDFF     (Use Prohibited)
	// FE00 - FE9F: Object-Attribute-Memory 
	// FEA0 - FEFF: Unused                    (Use Prohibited)
	// FF00 - FF7F: I/O Registers
	// FF80 - FFFE: High RAM
	// FFFF - FFFF: Interrupt Enable Register

	// Value to be returned if attempting to read an inaccesible address
	byte garbageVal{ 0xFF };

public:
	// Current Mode of the PPU can lock certain parts of memory
	int PPUMode{ 0 }; // Mode is 0, 1, 2, or 3

	// Sets initial values for some hardware registers (as specified in the CGB boot rom)
	void init();

	// Loads a given ROM into memory
	void loadROM(std::string filePath);

	// Checks if a given address is currently accessible
	bool isAccessible(address addr);

	// Returns the value inside a given RAM Address (if it is currently accessible)
	byte& read(address addr);

	// Returns the value inside a given RAM Address (no check for accessibility)
	byte& PPURead(address addr);

	// Writes a value to a given address (if it is currently accessible)
	void write(address addr, byte newVal);

	// Performs an OAM DMA Transfer based on the value stored in address 0xFF46
	void DMATransfer();
};