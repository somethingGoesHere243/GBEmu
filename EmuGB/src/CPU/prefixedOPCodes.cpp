#include "CPU.h"

#include <iostream>

void GBCPU::processPrefixedOPCode() {
	// 5 most sig. bits of OPCode determine operation to perform on reg
	byte fiveMostSigBits = (OPCode >> 3) & 31;

	// Register affected by OPCode is determined by 3 least sig. bits of OPCode
	byte threeLeastSigBits = OPCode & 7;
	byte* regPtr{ &A };
	// If working with HL register OPCode must be split into 2 steps
	if (OPCodeStep == 0) {
		// Increment program counter
		++PC;

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
			// If executing a testBit OPCode then operation still performed in 1 step
			if ((fiveMostSigBits >= 8) && (fiveMostSigBits <= 15)) {
				regPtr = &(getHLMemory());
			}
			else {
				// Need 2 steps for OPCode
				OPCodeStep = 1;
				++cyclesRemaining;
				// Return early so that OPCode can be performed in 2 steps
				return;
			}
			break;
		case 7:
			regPtr = &A;
			break;
		}
	}
	else {
		regPtr = &(getHLMemory());
		OPCodeStep = 0;
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

	nextInstructionPrefixed = false;
}