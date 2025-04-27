#include "CPU.h"

#include <iostream>

void GBCPU::RLC(byte& reg) {
	// Set zero flag if register contains 0
	bool zeroFlag = (reg == 0);

	// Carry flag is set to most sig byte of reg
	bool carryFlag = (reg >> 7) & 1;

	// Rotate bits of reg
	reg = 2 * reg + carryFlag;

	// Update F register ( Z, N, H Flags all set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
}

void GBCPU::RRC(byte& reg) {
	// Set zero flag if register contains 0
	bool zeroFlag = (reg == 0);

	// Carry flag is set to least sig byte of reg
	bool carryFlag = reg & 1;

	// Rotate bits of reg
	reg = (carryFlag * (1 << 7)) + ((reg >> 1) & 127);

	// Update F register ( N, H Flags both set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
}

void GBCPU::RL(byte& reg) {
	// Carry flag is set to most sig byte of reg
	bool carryFlag = (reg >> 7) & 1;

	// Get current carry flag from F register
	bool currCarry = F & C_FLAG;

	// Rotate bits of reg
	reg = 2 * reg + currCarry;

	// Set zero flag if register contains 0
	bool zeroFlag = (reg == 0);

	// Update F register ( Z, N, H Flags all set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
}

void GBCPU::RR(byte& reg) {
	// Carry flag is set to least sig byte of reg
	bool carryFlag = reg & 1;

	// Get current carry flag from F register
	bool currCarry = F & C_FLAG;

	// Rotate bits of reg
	reg = (currCarry * (1 << 7)) + ((reg >> 1) & 127);

	// Set zero flag if register contains 0
	bool zeroFlag = (reg == 0);

	// Update F register ( N, H Flags both set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
}

void GBCPU::SLA(byte& reg) {
	// Most significant bit cycled into carry flag
	bool carryFlag = reg & 128;
	reg = (reg << 1);

	// Set zero flag
	bool zeroFlag = (reg == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
}

void GBCPU::SRA(byte& reg) {
	// Least significant bit cycled into carry flag
	bool carryFlag = reg & 1;

	// Most significant bit unchanged
	byte mostSigBit = reg & 128;
	reg = mostSigBit + ((reg >> 1) & 127);

	// Set zero flag
	bool zeroFlag = (reg == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
}

void GBCPU::SRL(byte& reg) {
	// Least significant bit cycled into carry flag
	bool carryFlag = reg & 1;

	// Shift other bits
	reg = ((reg >> 1) & 127);

	// Set zero flag
	bool zeroFlag = (reg == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
}

void GBCPU::swap(byte& reg) {
	byte fourLeastSigBits = reg & 15;
	byte fourMostSigBits = (reg >> 4) & 15;

	reg = (fourLeastSigBits << 4) + fourMostSigBits;

	bool zeroFlag = (reg == 0);
	// All other flags set to 0
	F = zeroFlag * Z_FLAG;
}

void GBCPU::testBit(byte& reg, int bitNum) {
	bool zeroFlag = !(reg & (1 << bitNum));

	F = (F & C_FLAG) + zeroFlag * Z_FLAG + H_FLAG;
}

void GBCPU::setBit(byte& reg, int bitNum, bool bitValue) {
	byte bitToRemove = reg & (1 << bitNum);
	byte bitToAdd = bitValue * (1 << bitNum);

	reg = reg - bitToRemove + bitToAdd;
}

void GBCPU::processPrefixedOPCode() {
	++cyclesRemaining;

	// Gather 16 bit combined registers
	address HL = (H << 8) + L;

	// 5 most sig. bits of OPCode determine operation to perform on reg
	byte fiveMostSigBits = (OPCode >> 3) & 31;

	// Register affected by OPCode is determined by 3 least sig. bits of OPCode
	byte threeLeastSigBits = OPCode & 7;
	byte* regPtr{ &tempByte1 };
	// If working with HL register OPCode must be split into 2 steps
	if (OPCodeStep == 0) {
		switch (threeLeastSigBits) {
		case 0:
			regPtr = &B;
			break;
		case 1:
			regPtr = &C;
			break;
		case 2:
			regPtr = &D;
			break;
		case 3:
			regPtr = &E;
			break;
		case 4:
			regPtr = &H;
			break;
		case 5:
			regPtr = &L;
			break;
		case 6:
			OPCodeStep = 1;
			return;
		case 7:
			regPtr = &A;
			break;
		}
	}
	else if (OPCodeStep == 1) {
		tempByte1 = mem->read(HL);

		// If executing a testBit OPCode then operation performed in 2 steps
		// Otherwise takes 3 steps
		if (!((fiveMostSigBits >= 8) && (fiveMostSigBits <= 15))) {
			OPCodeStep = 2;
			return;
		}
	}

	switch (fiveMostSigBits) {
	case 0:
		RLC(*regPtr);
		break;
	case 1:
		RRC(*regPtr);
		break;
	case 2:
		RL(*regPtr);
		break;
	case 3:
		RR(*regPtr);
		break;
	case 4:
		SLA(*regPtr);
		break;
	case 5:
		SRA(*regPtr);
		break;
	case 6:
		swap(*regPtr);
		break;
	case 7:
		SRL(*regPtr);
		break;
	case 8:
		testBit(*regPtr, 0);
		break;
	case 9:
		testBit(*regPtr, 1);
		break;
	case 10:
		testBit(*regPtr, 2);
		break;
	case 11:
		testBit(*regPtr, 3);
		break;
	case 12:
		testBit(*regPtr, 4);
		break;
	case 13:
		testBit(*regPtr, 5);
		break;
	case 14:
		testBit(*regPtr, 6);
		break;
	case 15:
		testBit(*regPtr, 7);
		break;
	case 16:
		setBit(*regPtr, 0, 0);
		break;
	case 17:
		setBit(*regPtr, 1, 0);
		break;
	case 18:
		setBit(*regPtr, 2, 0);
		break;
	case 19:
		setBit(*regPtr, 3, 0);
		break;
	case 20:
		setBit(*regPtr, 4, 0);
		break;
	case 21:
		setBit(*regPtr, 5, 0);
		break;
	case 22:
		setBit(*regPtr, 6, 0);
		break;
	case 23:
		setBit(*regPtr, 7, 0);
		break;
	case 24:
		setBit(*regPtr, 0, 1);
		break;
	case 25:
		setBit(*regPtr, 1, 1);
		break;
	case 26:
		setBit(*regPtr, 2, 1);
		break;
	case 27:
		setBit(*regPtr, 3, 1);
		break;
	case 28:
		setBit(*regPtr, 4, 1);
		break;
	case 29:
		setBit(*regPtr, 5, 1);
		break;
	case 30:
		setBit(*regPtr, 6, 1);
		break;
	case 31:
		setBit(*regPtr, 7, 1);
		break;
	}

	// If working with HL register OPCode must now write new value into memory
	if (threeLeastSigBits == 6) {
		mem->write(HL, tempByte1);
		OPCodeStep = 0;
	}

	nextInstructionPrefixed = false;
}