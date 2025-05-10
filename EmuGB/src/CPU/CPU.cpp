#include "CPU.h"

#include <iostream>

void GBCPU::conditionalCall(address addr, bool condition) {
	// Return early if condition not met
	if (!condition) {
		return;
	}
	// Split PC into 2 bytes to be pushed onto stack
	byte mostSigBitsPC = (PC >> 8);
	byte leastSigBitsPC = PC;

	// Decrement stack pointer before pushing new register into its new location
	--SP;
	mem->write(SP, mostSigBitsPC);

	--SP;
	mem->write(SP, leastSigBitsPC);

	PC = addr;
	cyclesRemaining += 3;
}

void GBCPU::reset() {
	nextInstructionPrefixed = false;
	OPCodeStep = 0;
	isHalted = false;
	IME = 0;
	instructionsBeforeIMESet = 0;
	
	A = 0x01;
	F = Z_FLAG | H_FLAG | C_FLAG;
	B = 0;
	C = 0x13;
	D = 0;
	E = 0xD8;
	H = 0x01;
	L = 0x4D;
	SP = 0xFFFE;
	PC = 0x0100;

	cyclesRemaining = 0;
}

void GBCPU::update() {
	// Check if an instruction is running
	if (cyclesRemaining == 0) {
		// Check if CPU is halted
		if (isHalted) {
			// Resume execution if an interrupt is pending
			byte IF = mem->read(0xFF0F);
			byte IE = mem->read(0xFFFF);
			if ((IF & IE) != 0) {
				// Interrupt is pending so resume CPU on next cycle
				isHalted = false;
			}
			return;
		}

		// Check if IME flag needs to be set
		if (instructionsBeforeIMESet > 0) {
			--instructionsBeforeIMESet;
			if (instructionsBeforeIMESet == 0) {
				IME = 1;
			}
		}

		if (OPCodeStep == 0) {
			// Retrieve new OPCode
			OPCode = mem->read(PC);
			++PC;
		}
	}

	// Check if current OPCode is prefixed
	if (nextInstructionPrefixed) {
		processPrefixedOPCode();
	}
	else {
		processUnprefixedOPCode();
	}
	--cyclesRemaining;
}
