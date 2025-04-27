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
	IORegs[0x44] = 0x90;
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
		MBCRegs[1] = 1;
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
		// Echo of the above WRAM
		return WRAM[addr - 0xE000];
	}
	else if (addr < 0xFEA0) {
		// OAM disabled in PPUModes 2 & 3
		if (PPUMode == 3 || PPUMode == 2) {
			return 0xFF;
		}
		// OAM also disabled during DMA Transfers
		if (isDMATransfer) {
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
		// Echo of the above WRAM
		return WRAM[addr - 0xE000];
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
		WRAM[addr - 0xE000] = newVal;
	}
	else if (addr < 0xFEA0) {
		// OAM disabled in PPUModes 2 & 3
		if (PPUMode == 3 || PPUMode == 2) {
			return;
		}
		// OAM also disabled during DMA Transfers
		if (isDMATransfer) {
			return;
		}

		OAM[addr - 0xFE00] = newVal;
	}
	else if (addr < 0xFF00) {
		// Unused Memory
		return;
	}
	else if (addr < 0xFF80) {
		IOWrite(addr - 0xFF00, newVal);
	}
	else if (addr < 0xFFFF) {
		HRAM[addr - 0xFF80] = newVal;
	}
	else {
		IntEnableReg = newVal;
	}
}

void GBMemory::IOWrite(address addr, byte newVal) {
	switch (addr) {
	case 0x00:
		// Only bits 4 & 5 of the JOYP register can be written to by the cpu
		IORegs[0x00] = (IORegs[0x00] & 0b11001111) + (newVal & 0b00110000);
		break;
	case 0x02:
		// Only bits 0, 1 & 7 of the SC register can be written to by the cpu
		IORegs[0x01] = (IORegs[0x01] & 0b01111100) + (newVal & 0b10000011);
		break;
	case 0x04:
		// Any attempt to write to the DIV register resets its value to 0
		IORegs[0x04] = 0;
		// Need to also reset the timer ticks to 0
		resetTimer = true;
		break;
	case 0x07:
		// Only bits 0, 1 & 2 of the TAC register can be written to by the cpu
		IORegs[0x07] = (IORegs[0x07] & 0b11111000) + (newVal & 0b00000111);
		break;
	case 0x0F:
		// 3 most sig. bits of IF register are hardcoded to 1
		IORegs[0x0F] = newVal | 0b11100000;
		break;
	case 0x10:
		// Only bits 0 - 6 of the NR10 register can be written to by the cpu
		IORegs[0x10] = (IORegs[0x10] & 0b10000000) + (newVal & 0b01111111);
		break;
	case 0x1A:
		// Only bit 7 of the NR30 register can be written to by the cpu
		IORegs[0x1A] = (IORegs[0x1A] & 0b01111111) + (newVal & 0b100000000);
		break;
	case 0x1C:
		// Only bit 5 & 6 of the NR32 register can be written to by the cpu
		IORegs[0x1C] = (IORegs[0x1C] & 0b10011111) + (newVal & 0b01100000);
		break;
	case 0x20:
		// Only bits 0 - 5 of the NR41 register can be written to by the cpu
		IORegs[0x20] = (IORegs[0x20] & 0b11000000) + (newVal & 0b00111111);
		break;
	case 0x23:
		// Only bits 6 & 7 of the NR44 register can be written to by the cpu
		IORegs[0x23] = (IORegs[0x23] & 0b00111111) + (newVal & 0b11000000);
		break;
	case 0x26:
		// Only bits 0-3 & 7 of the NR52 register can be written to by the cpu
		IORegs[0x26] = (IORegs[0x26] & 0b01110000) + (newVal & 0b10001111);
		break;
	case 0x41:
		// Only bits 3 - 6 of the STAT register can be written to by the cpu
		IORegs[0x41] = (IORegs[0x41] & 0b10000111) + (newVal & 0b01111000);
		break;
	case 0x44:
		// Attempting to write to LY register should be ignored
		break;
	case 0x46:
		BeginDMATransfer();
		IORegs[0x46] = newVal;
		break;
	case 0x47:
	case 0x48:
	case 0x49:
		// Palettes disabled in PPUMode 3
		if (PPUMode != 3) {
			IORegs[addr] = newVal;
		}
		break;
	case 0x01:
	case 0x05:
	case 0x06:
	case 0x11:
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1B:
	case 0x1D:
	case 0x1E:
	case 0x21:
	case 0x22:
	case 0x24:
	case 0x25:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x3A:
	case 0x3B:
	case 0x3C:
	case 0x3D:
	case 0x3E:
	case 0x3F:
	case 0x40:
	case 0x42:
	case 0x43:
	case 0x45:
	case 0x4A:
	case 0x4B:
		IORegs[addr] = newVal;
		break;
	// Otherwise have an unmapped registers
	}
}

void GBMemory::update() {
	// Check for DMA Transfers
	if (currDMAStep <= 0xA0) {
		DMATransferStep();
	}

	// Check for a timer in cartridge
	if (MBCType == 3) {
		MBC3TimerTick();
	}
}

// TODO: OAM DMA bus conflicts (https://github.com/Gekkio/mooneye-gb/issues/39)
void GBMemory::BeginDMATransfer() {
	currDMAStep = -1;
}

void GBMemory::DMATransferStep() {
	// Wait one cycle before memory transfer begins
	if (currDMAStep == -1) {
		++currDMAStep;
		return;
	}
	isDMATransfer = true;

	if (currDMAStep == 0xA0) {
		// DMA has been completed
		isDMATransfer = false;
		return;
	}

	// Value in 0xFF46 multiplied by 0x0100 specifies the source of the transfer
	int source = IORegs[0x0046] * 0x0100;

	OAM[currDMAStep] = PPURead(source + currDMAStep);
	++currDMAStep;
}