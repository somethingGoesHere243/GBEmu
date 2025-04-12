#include "Memory.h"

#include <fstream>

void GBMemory::init() {
	// All Addresses written to here are of the form $FF00 + some byte
	// Initialise all IORegs to 0xFF
	for (int i = 0; i < IORegisterCount; ++i) {
		IORegs[i] = 0xFF;
	}
	// Some Registers need specific initialisation values
	IORegs[0x00] = 0xCF;
	IORegs[0x01] = 0x00;
	IORegs[0x02] = 0x7E;
	IORegs[0x04] = 0xAB;
	IORegs[0x05] = 0x00;
	IORegs[0x06] = 0x00;
	IORegs[0x07] = 0xF8;
	IORegs[0x0F] = 0xE1;
	IORegs[0x10] = 0x80;
	IORegs[0x11] = 0xBF;
	IORegs[0x12] = 0xF3;
	IORegs[0x14] = 0xBF;
	IORegs[0x16] = 0x3F;
	IORegs[0x17] = 0x00;
	IORegs[0x19] = 0xBF;
	IORegs[0x1A] = 0x7F;
	IORegs[0x1C] = 0x9F;
	IORegs[0x1E] = 0xBF;
	IORegs[0x21] = 0x00;
	IORegs[0x22] = 0x00;
	IORegs[0x23] = 0xBF;
	IORegs[0x24] = 0x77;
	IORegs[0x25] = 0xF3;
	IORegs[0x26] = 0xF1;
	IORegs[0x40] = 0x91;
	IORegs[0x41] = 0x85;
	IORegs[0x42] = 0x00;
	IORegs[0x43] = 0x00;
	IORegs[0x44] = 0x91;
	IORegs[0x45] = 0x00;
	IORegs[0x47] = 0xFC;
	IORegs[0x4A] = 0x00;
	IORegs[0x4B] = 0x00;

	IntEnableReg = 0x00;
}

void GBMemory::loadROM(std::string filePath) {
	// Load ROM/text file into a file stream
	std::ifstream fileStream;
	fileStream.open(filePath, std::ios::in | std::ios::binary);

	if (!fileStream) {
		std::cerr << "Failed to open the given ROM\n";
		return;
	}

	// Read 1 character at a time from ROM and write to memory
	char c;
	int currAddress = 0x0000;

	while (fileStream.get(c)) {
		int ROMBankIndex = currAddress / 0x4000;
		address ROMAddr = currAddress % 0x4000;
		ROMBanks[ROMBankIndex].write(ROMAddr, c);
		++currAddress;
	}
	fileStream.close();

	// Address 0x0147 in the cartridge determines the MBC which the cartridge uses
	switch (ROMBanks[0].read(0x0147)) {
		// TODO: This code also states if cartridge has a battery or timer etc.
	case 0x00:
		MBCType = None;
		break;
	case 0x01:
	case 0x02:
	case 0x03:
		MBCType = MBC1;
		// Initialise any MBC registers which don't default to 0
		MBCReg2 = 1;
		break;
	case 0x05:
	case 0x06:
		MBCType = MBC2;
		break;
	case 0x0B:
	case 0x0C:
	case 0x0D:
		MBCType = MMM01;
		break;
	case 0x0F:
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
		MBCType = MBC3;
		break;
	case 0x19:
	case 0x1A:
	case 0x1B:
	case 0x1C:
	case 0x1D:
	case 0x1E:
		MBCType = MBC5;
		break;
	case 0x20:
		MBCType = MBC6;
		break;
	case 0x22:
		MBCType = MBC7;
		break;
	case 0xFE:
		MBCType = HuC1;
		break;
	case 0xFF:
		MBCType = HuC3;
		break;
	default:
		std::cout << "Unsupported MBC Type Provided\n";
		return;
	}

	// Address 0x0148 in the cartridge determines the number of ROM Banks in the cartridge
	switch (ROMBanks[0].read(0x0148)) {
	case 0x00:
		ROMBankCount = 2;
		break;
	case 0x01:
		ROMBankCount = 4;
		break;
	case 0x02:
		ROMBankCount = 8;
		break;
	case 0x03:
		ROMBankCount = 16;
		break;
	case 0x04:
		ROMBankCount = 32;
		break;
	case 0x05:
		ROMBankCount = 64;
		break;
	case 0x06:
		ROMBankCount = 128;
		break;
	case 0x07:
		ROMBankCount = 256;
		break;
	case 0x08:
		ROMBankCount = 512;
		break;
	}
	
	// Address 0x0149 in the cartridge determines the number of RAM Banks in the cartridge
	switch (ROMBanks[0].read(0x0149)) {
	case 0x00:
		RAMBankCount = 0;
		break;
	case 0x02:
		RAMBankCount = 1;
		break;
	case 0x03:
		RAMBankCount = 4;
		break;
	case 0x04:
		RAMBankCount = 16;
		break;
	case 0x05:
		RAMBankCount = 8;
		break;
	}
}

byte GBMemory::read(address addr) {
	if (addr < 0x8000) {
		return MBCRead(addr);
	}
	else if (addr < 0xA000) {
		// VRAM disabled in PPUMode 3
		if (PPUMode == 3) {
			return 0xFF;
		}
		return VRAM[addr - 0x8000];
	}
	else if (addr < 0xC000) {
		return MBCRead(addr);
	}
	else if (addr < 0xE000) {
		return WRAM[addr - 0xC000];
	}
	else if (addr < 0xFE00) {
		// Unemulated Echo Ram
		return 0xFF;
	}
	else if (addr < 0xFEA0) {
		// OAM disabled in PPUModes 2 & 3
		if (PPUMode == 3 || PPUMode == 2) {
			return 0xFF;
		}
		return OAM[addr - 0xFE00];
	}
	else if (addr < 0xFF00) {
		// Unused Memory
		return 0xFF;
	}
	else if (addr < 0xFF80) {
		// Palettes disabled in PPUMode 3
		if (PPUMode == 3 && (addr == 0xFF47 || addr == 0xFF48 || addr == 0xFF49)) {
			return 0xFF;
		}
		return IORegs[addr - 0xFF00];
	}
	else if (addr < 0xFFFF) {
		return HRAM[addr - 0xFF80];
	}
	else {
		return IntEnableReg;
	}
}

byte& GBMemory::PPURead(address addr) {
	if (addr < 0x4000) {
		return ROMBanks[ROMBank0Index].read(addr);
	}
	else if (addr < 0x8000) {
		// TODO: Switchable ROMBanks dependant on MBC
		return ROMBanks[ROMBank1Index].read(addr - 0x4000);
	}
	else if (addr < 0xA000) {
		return VRAM[addr - 0x8000];
	}
	else if (addr < 0xC000) {
		// TODO: Switchable RAMBanks dependant on MBC
		return RAMBanks[RAMBankIndex].read(addr - 0xA000);
	}
	else if (addr < 0xE000) {
		return WRAM[addr - 0xC000];
	}
	else if (addr < 0xFE00) {
		// Unemulated Echo Ram
		return garbageVal;
	}
	else if (addr < 0xFEA0) {
		return OAM[addr - 0xFE00];
	}
	else if (addr < 0xFF00) {
		// Unused Memory
		return garbageVal;
	}
	else if (addr < 0xFF80) {
		return IORegs[addr - 0xFF00];
	}
	else if (addr < 0xFFFF) {
		return HRAM[addr - 0xFF80];
	}
	else {
		return IntEnableReg;
	}
}

void GBMemory::write(address addr, byte newVal) {		
	if (addr < 0x8000) {
		MBCWrite(addr, newVal);
	}
	else if (addr < 0xA000) {
		// VRAM disabled in PPUMode 3
		if (PPUMode == 3) {
			return;
		}
		VRAM[addr - 0x8000] = newVal;
	}
	else if (addr < 0xC000) {
		MBCWrite(addr, newVal);
	}
	else if (addr < 0xE000) {
		WRAM[addr - 0xC000] = newVal;
	}
	else if (addr < 0xFE00) {
		// Unemulated Echo Ram
		return;
	}
	else if (addr < 0xFEA0) {
		// OAM disabled in PPUModes 2 & 3
		if (PPUMode == 3 || PPUMode == 2) {
			return;
		}
		OAM[addr - 0xFE00] = newVal;
	}
	else if (addr < 0xFF00) {
		// Unused Memory
		return;
	}
	else if (addr < 0xFF80) {
		// Any attempt to write to the DIV register resets its value to 0
		if (addr == 0xFF04) {
			IORegs[0x0004] = 0;
			// Need to also reset the timer ticks to 0
			resetTimer = true;
			return;
		}

		// Attempting to write to LY register should be ignored
		if (addr == 0xFF44) { 
			return; 
		}

		// Palettes disabled in PPUMode 3
		if (PPUMode == 3 && (addr == 0xFF47 || addr == 0xFF48 || addr == 0xFF49)) {
			return;
		}

		// Attempting to write to address 0xFF46 triggers a DMA Transfer
		if (addr == 0xFF46) {
			DMATransfer();
		}

		IORegs[addr - 0xFF00] = newVal;
	}
	else if (addr < 0xFFFF) {
		HRAM[addr - 0xFF80] = newVal;
	}
	else {
		IntEnableReg = newVal;
	}
}

void GBMemory::DMATransfer() {
	// TODO: Lock most of memory during the transfer
	// Value in 0xFF46 multiplied by 0x0100 specifies the source of the transfer
	int source = IORegs[0x0046] * 0x0100;
	for (int i = 0; i < 0x00A0; ++i) {
		OAM[i] = read(source + i);
	}

	return;
}