#include "CPU.h"

#include <iostream>

void GBCPU::processPrefixedOPCode(byte OPCode) {
	// Increment program counter
	++PC;
	
	// Register affected by OPCode is determined by 3 least sig. bits of OPCode
	byte* regPtr{ &A };
	byte threeLeastSigBits = OPCode & 7;
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
		regPtr = &getHLMemory();
		++cyclesRemaining;
		break;
	case 7:
		regPtr = &A;
		break;
	}

	// 5 most sig. bits of OPCode determine operation to perform on reg
	byte fiveMostSigBits = (OPCode >> 3) & 31;

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
		// Need one less cycle for (HL) register here
		if (threeLeastSigBits == 6) { --cyclesRemaining; };
		break;
	case 9:
		testBit(*regPtr, 1);
		// Need one less cycle for (HL) register here
		if (threeLeastSigBits == 6) { --cyclesRemaining; };
		break;
	case 10:
		testBit(*regPtr, 2);
		// Need one less cycle for (HL) register here
		if (threeLeastSigBits == 6) { --cyclesRemaining; };
		break;
	case 11:
		testBit(*regPtr, 3);
		// Need one less cycle for (HL) register here
		if (threeLeastSigBits == 6) { --cyclesRemaining; };
		break;
	case 12:
		testBit(*regPtr, 4);
		// Need one less cycle for (HL) register here
		if (threeLeastSigBits == 6) { --cyclesRemaining; };
		break;
	case 13:
		testBit(*regPtr, 5);
		// Need one less cycle for (HL) register here
		if (threeLeastSigBits == 6) { --cyclesRemaining; };
		break;
	case 14:
		testBit(*regPtr, 6);
		// Need one less cycle for (HL) register here
		if (threeLeastSigBits == 6) { --cyclesRemaining; };
		break;
	case 15:
		testBit(*regPtr, 7);
		// Need one less cycle for (HL) register here
		if (threeLeastSigBits == 6) { --cyclesRemaining; };
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
}