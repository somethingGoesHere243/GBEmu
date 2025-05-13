#include "Memory/Memory.h"

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
		if ((int)MBCRegs[3] == 1) {
			ROMBank0Index = MBCRegs[2] * 0x20;
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

		ROMBank1Index = MBCRegs[2] * 0x20 + MBCRegs[1];

		// ROM Bank Index cant exceed the total number of ROM Banks
		ROMBank1Index = ROMBank1Index % ROMBankCount;

		return ROMBanks[ROMBank1Index].read(addr - 0x4000);
	}
	else {
		// Check cartridge contains External Ram and its enabled (MBCRegs[0])
		if (RAMBankCount == 0 || (int)MBCRegs[0] == 0) {
			//Return garbage
			return 0xFF;
		}

		// Get current RAM Bank

		// Check if RAM bank switching enabled
		if ((int)MBCRegs[3] == 1) {
			// RAM Bank index must be less than the number of RAM banks in the cartridge
			RAMBankIndex = MBCRegs[2] % RAMBankCount;
		}
		else {
			// RAM Bank hard coded to 0
			RAMBankIndex = 0;
		}

		// Read new value from RAM
		return RAMBanks[RAMBankIndex].read(addr - 0xA000);
	}
}

void GBMemory::MBC1Write(address addr, byte newVal) {
	if (addr < 0x2000) {
		// Any attempt to write to the range 0x0000 - 0x1FFF will enable/disable cartridge RAM
		// A value with last 4 bits == 0xA enables RAM
		if (((int)newVal & 0xF ) == 0xA) {
			MBCRegs[0] = 1;
		}
		else {
			MBCRegs[0] = 0;
		}
		return;
	}
	else if (addr < 0x4000) {
		// Any attempt to write to range 0x2000 - 0x3FFF determines the lower 5 bits of the ROM bank we wish to use for ROMBank 1
		MBCRegs[1] = newVal & 0b00011111; // 5 bit register
		// ROMBank1 can not be given an index of 0
		if ((int)MBCRegs[1] == 0) {
			MBCRegs[1] = 1;
		}
		return;
	}
	else if (addr < 0x6000) {
		// Any attempt to write to range 0x4000 - 0x5FFF determines either the RAM Bank used or the next 2 bits of the ROM Bank being used
		MBCRegs[2] = newVal & 3; // 2 bit register
		return;
	}
	else if (addr < 0x8000) {
		// Any attempt to write to range 0x6000 - 0x7FFF determines the current banking mode
		MBCRegs[3] = newVal & 1; // 1 bit register
		return;
	}
	else {
		// Check cartridge contains External Ram and its enabled (MBCReg1)
		if (RAMBankCount == 0 || (int)MBCRegs[0] == 0) {
			//Return early
			return;
		}
	
		// Get current RAM Bank
		
		// Check if RAM bank switching enabled
		if ((int)MBCRegs[3] == 1) {
			// RAM Bank index must be less than the number of RAM banks in the cartridge
			RAMBankIndex = MBCRegs[2] % RAMBankCount;
		}
		else {
			// RAM Bank hard coded to 0
			RAMBankIndex = 0;
		}

		// Write new value into RAM
		RAMBanks[RAMBankIndex].write(addr - 0xA000, newVal);
	}
}

byte GBMemory::MBC3Read(address addr) {
	if (addr < 0x4000) {
		return ROMBanks[0].read(addr);
	}
	else if (addr < 0x8000) {
		// ROM Bank Index cant exceed the total number of ROM Banks
		ROMBank1Index = ROMBank1Index % ROMBankCount;

		return ROMBanks[ROMBank1Index].read(addr - 0x4000);
	}
	else {
		// Values of MBCRegs[1] between 0x0 and 0x7 access the corresponding RAM Banks
		if (MBCRegs[1] >= 0x0 && MBCRegs[1] <= 0x7) {
			// Write new value into RAM
			return RAMBanks[MBCRegs[1]].read(addr - 0xA000);
		}
		else if (MBCRegs[1] >= 0x0 && MBCRegs[1] <= 0xC) {
			// Check if clock data is latched
			if (MBCRegs[3] == 1) {
				// Latched
				return MBCRegs[MBCRegs[1] + 5];
			}
			// Unlatched
			return MBCRegs[MBCRegs[1]];
		}
	}
}

void GBMemory::MBC3Write(address addr, byte newVal) {
	if (addr < 0x2000) {
		// Any attempt to write to the range 0x0000 - 0x1FFF will enable/disable cartridge RAM/Timer
		// A value with last 4 bits == 0xA enables RAM
		if ((int)newVal == 0x0A) {
			MBCRegs[0] = 1;
		}
		else if ((int)newVal == 0) {
			MBCRegs[0] = 0;
		}
		return;
	}
	else if (addr < 0x4000) {
		// Any attempt to write to range 0x2000 - 0x3FFF determines the ROM bank we wish to use for ROMBank 1
		ROMBank1Index = newVal & 0b01111111; // 7 bit register;
		return;
	}
	else if (addr < 0x6000) {
		// Any attempt to write to range 0x4000 - 0x5FFF determines either the RAM Bank used or the selected RTC register
		MBCRegs[1] = newVal & 15; // 4 bit register
		return;
	}
	else if (addr < 0x8000) {
		// Any attempt to write to range 0x6000 - 0x7FFF attempts to latch the current clock data
		// If write a 1 after writing a 0 clock data is latched
		if (MBCRegs[2] == 0 && newVal == 1) {
			// Set MBCRegs[3] to 1 if clock data is latched and 0 when unlatched
			MBCRegs[3] = (MBCRegs[3] == 0) ? 1 : 0;

			if (MBCRegs[3] == 1) {
				// Save latched clock data
				MBCRegs[0xD] = MBCRegs[0x8];
				MBCRegs[0xE] = MBCRegs[0x9];
				MBCRegs[0xF] = MBCRegs[0xA];
				MBCRegs[0x10] = MBCRegs[0xB];
				MBCRegs[0x11] = MBCRegs[0xC];
			}
		}
		MBCRegs[2] = newVal;
		return;
	}
	else {
		switch (MBCRegs[1]) {
		// Values of MBCRegs[1] between 0x0 and 0x7 access the corresponding RAM Banks
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			// Write new value into RAM
			RAMBanks[MBCRegs[1]].write(addr - 0xA000, newVal);
			break;
		// Other values lead to writes to the RTC (timer) Registers
		case 8:
		case 9:
			// 6 bit registers
			MBCRegs[MBCRegs[1]] = newVal & 0b00111111;
			break;
		case 10:
			// 5 bit register
			MBCRegs[MBCRegs[1]] = newVal & 0b00011111;
			break;
		case 11:
			MBCRegs[MBCRegs[1]] = newVal;
			break;
		case 12:
			// Only bits 0, 6, and 7 can be set
			MBCRegs[MBCRegs[1]] = newVal & 0b11000001;
			break;
		}
	}
}

void GBMemory::MBC3TimerTick() {
	constexpr int CPUFreq = 1048576;
	MBCTicks = (MBCTicks + 1) % CPUFreq;

	// Check if halt bit (bit 6 of MBCRegs[0xC]) or if clock is latched (MBCRegs[3])
	if ((MBCRegs[0xC] & 0b01000000) ) {
		// Timer not incremented
		return;
	}

	// Check if a second has passed
	
	if (MBCTicks != 0) { return; }

	// Increment the seconds register
	++MBCRegs[0x8];
	if (MBCRegs[0x8] == 60) {
		MBCRegs[0x8] = 0;

		// Increment minutes register
		++MBCRegs[0x9];
		if (MBCRegs[0x9] == 60) {
			MBCRegs[0x9] = 0;

			// Increment Hours register
			++MBCRegs[0xA];
			if (MBCRegs[0xA] == 24) {
				MBCRegs[0xA] = 0;

				//Increment Days register
				++MBCRegs[0xB];

				// Check for overflow
				if (MBCRegs[0xB] == 0) {
					// Bit 0 of MBCRegs[0xC] represents the 9th bit of the days register
					// Bit 7 of MBCRegs[0xC] is set if the days register overflows the 9th bit
					if (MBCRegs[0xC] & 1) {
						// Set bit 7 and reset the days register
						MBCRegs[0xC] = (MBCRegs[0xC] | 0b10000000) & ~0b00000001;
						MBCRegs[0xB] = 0;
					}
					else {
						MBCRegs[0xC] = MBCRegs[0xC] | 1;
					}
				}
			}
		}
	}

	// Check for invalid rollovers
	if (MBCRegs[0x8] >= 64) { MBCRegs[0x8] = 0; }
	if (MBCRegs[0x9] >= 64) { MBCRegs[0x9] = 0; }
	if (MBCRegs[0xA] >= 32) { MBCRegs[0xA] = 0; }
}

byte GBMemory::MBC5Read(address addr) {
	if (addr < 0x4000) {
		return ROMBanks[0].read(addr);
	}
	else if (addr < 0x8000) {
		ROMBank1Index = MBCRegs[1] + 256 * MBCRegs[2];

		// ROM Bank Index cant exceed the total number of ROM Banks
		ROMBank1Index = ROMBank1Index % ROMBankCount;

		return ROMBanks[ROMBank1Index].read(addr - 0x4000);
	}
	else {
		// Check cartridge contains External Ram and its enabled (MBCRegs[0])
		if (RAMBankCount == 0 || (int)MBCRegs[0] == 0) {
			//Return garbage
			return 0xFF;
		}
		// Read new value from RAM
		return RAMBanks[RAMBankIndex].read(addr - 0xA000);
	}
}

void GBMemory::MBC5Write(address addr, byte newVal) {
	if (addr < 0x2000) {
		// Enable/disable cartridge RAM
		// A value with last 4 bits == 0xA enables RAM
		if (((int)newVal & 0xF) == 0xA) {
			MBCRegs[0] = 1;
		}
		else if ((int)newVal == 0) {
			MBCRegs[0] = 0;
		}
	}
	else if (addr < 0x3000) {
		// Set least significant 8 bits of ROMBank1Index
		MBCRegs[1] = newVal;
	}
	else if (addr < 0x4000) {
		// Set most significant bit (bit 8) of ROMBank1Index
		MBCRegs[2] = newVal & 1; // 1 bit register;
	}
	else if (addr < 0x6000) {
		// Sets RAMBankIndex
		RAMBankIndex = newVal % RAMBankCount;
	}
}

byte GBMemory::MBCRead(address addr) {
	// Select the correct read function from above dependant on the current MBC
	switch (MBCType) {
	case None:
		return noMBCRead(addr);
	case MBC1:
		return MBC1Read(addr);
	case MBC3:
		return MBC3Read(addr);
	case MBC5:
		return MBC5Read(addr);
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
	case MBC3:
		MBC3Write(addr, newVal);
		break;
	case MBC5:
		MBC5Write(addr, newVal);
		break;
	default:
		std::cout << "MBC Type Not Yet Implemented\n";
	}
}