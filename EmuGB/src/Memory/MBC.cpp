#include "Memory.h"

byte GBMemory::noMBCRead(address addr) {
	// No additional ROM Banks
	if (addr < 0x4000) {
		return ROMBanks[0].read(addr);
	} 
	else if (addr < 0x8000) {
		return ROMBanks[1].read(addr - 0x4000);
	}
	else {
		// Check if we have external RAM (can only have 0 or 1 banks)
		if (RAMBankCount == 1) {
			return RAMBanks[0].read(addr - 0xA000);
		}
		// No external RAM so return garbage
		return 0xFF;
	}
}

void GBMemory::noMBCWrite(address addr, byte newVal) {
	if (addr < 0x8000) {
		// Cant overwrite ROM so return early
		return;
	}
	else {
		// Check if we have external RAM (can only have 0 or 1 banks)
		if (RAMBankCount == 1) {
			RAMBanks[0].write(addr - 0xA000, newVal);
		}

		// No external RAM so return early
		return;
	}
}

byte GBMemory::MBC1Read(address addr) {
	if (addr < 0x4000) {
		// Get current ROM Bank 0

		// Check if ROM bank 0 switching enabled
		if ((int)MBCReg4 == 1) {
			ROMBank0Index = MBCReg3 * 0x20;
		}
		else {
			// ROM Bank 0 hard coded to 0
			ROMBank0Index = 0;
		}

		// ROM Bank Index cant exceed the total number of ROM Banks
		ROMBank0Index = ROMBank0Index % ROMBankCount;

		return ROMBanks[ROMBank0Index].read(addr);
	}
	else if (addr < 0x8000) {
		// Get current ROM Bank 1

		ROMBank1Index = MBCReg3 * 0x20 + MBCReg2;

		// ROM Bank Index cant exceed the total number of ROM Banks
		ROMBank1Index = ROMBank1Index % ROMBankCount;

		return ROMBanks[ROMBank1Index].read(addr - 0x4000);
	}
	else {
		// Check cartridge contains External Ram and its enabled (MBCReg1)
		if (RAMBankCount == 0 || (int)MBCReg1 == 0) {
			//Return garbage
			return 0xFF;
		}

		// Get current RAM Bank

		// Check if RAM bank switching enabled
		if ((int)MBCReg4 == 1) {
			// RAM Bank index must be less than the number of RAM banks in the cartridge
			RAMBankIndex = MBCReg3 % RAMBankCount;
		}
		else {
			// RAM Bank hard coded to 0
			RAMBankIndex = 0;
		}

		// Write new value into RAM
		return RAMBanks[RAMBankIndex].read(addr - 0xA000);
	}
}

void GBMemory::MBC1Write(address addr, byte newVal) {
	if (addr < 0x2000) {
		// Any attempt to write to the range 0x0000 - 0x1FFF will enable/disable cartridge RAM
		// A value with last 4 bits == 0xA enables RAM
		if ((int)newVal % 0x10 == 0x0A) {
			MBCReg1 = 1;
		}
		else {
			MBCReg1 = 0;
		}
		return;
	}
	else if (addr < 0x4000) {
		// Any attempt to write to range 0x2000 - 0x3FFF determines the lower 5 bits of the ROM bank we wish to use for ROMBank 1

		MBCReg2 = newVal & 31; // 5 bit register
		// ROMBank1 can not be given an index of 0
		if ((int)MBCReg2 == 0) {
			MBCReg2 = 1;
		}
		return;
	}
	else if (addr < 0x6000) {
		// Any attempt to write to range 0x4000 - 0x5FFF determines either the RAM Bank used or the next 2 bits of the ROM Bank being used
		MBCReg3 = newVal & 3; // 2 bit register
		return;
	}
	else if (addr < 0x8000) {
		// Any attempt to write to range 0x6000 - 0x7FFF determines the current banking mode
		MBCReg4 = newVal & 1; // 1 bit register
		return;
	}
	else {
		// Check cartridge contains External Ram and its enabled (MBCReg1)
		if (RAMBankCount == 0 || (int)MBCReg1 == 0) {
			//Return early
			return;
		}
	
		// Get current RAM Bank
		
		// Check if RAM bank switching enabled
		if ((int)MBCReg4 == 1) {
			// RAM Bank index must be less than the number of RAM banks in the cartridge
			RAMBankIndex = MBCReg3 % RAMBankCount;
		}
		else {
			// RAM Bank hard coded to 0
			RAMBankIndex = 0;
		}

		// Write new value into RAM
		RAMBanks[RAMBankIndex].write(addr - 0xA000, newVal);
	}
}

byte GBMemory::MBCRead(address addr) {
	// Select the correct read function from above dependant on the current MBC
	switch (MBCType) {
	case None:
		return noMBCRead(addr);
	case MBC1:
		return MBC1Read(addr);
	default:
		std::cout << "MBC Type Not Yet Implemented\n";
		return 0xFF;
	}
}

void GBMemory::MBCWrite(address addr, byte newVal) {
	// Select the correct write function from above dependant on the current MBC
	switch (MBCType) {
	case None:
		noMBCWrite(addr, newVal);
		break;
	case MBC1:
		MBC1Write(addr, newVal);
		break;
	default:
		std::cout << "MBC Type Not Yet Implemented\n";
	}
}