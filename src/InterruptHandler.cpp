#include "InterruptHandler.h"

InterruptHandler::InterruptHandler(GBCPU* CPU, GBMemory* mem) : CPU{ CPU }, 
																IE{ mem->PPURead(0xFFFF) },
																IF{ mem->PPURead(0xFF0F) }
																{
};

void InterruptHandler::update() {
	// Interrupts can only occur if the IME CPU flag is set and CPU is ready for its next instruction
	if (CPU->IME && CPU->cyclesRemaining == 0 && !CPU->nextInstructionPrefixed) {
		// Only one interrupt can be called per update
		// Least significant bits in the IE / IF registers take higher priority
		if ((IE & 1) && (IF & 1)) {
			// VBlank interrupt
			// Reset IME and bit 0 of IF
			CPU->IME = 0;
			IF -= 1;

			// Perform an unconditional call to the interrupt handler address 
			CPU->interruptStart(0x0040);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;
		}
		else if ((IE & 2) && (IF & 2)) {
			// LCD Interrupt
			CPU->IME = 0;
			IF -= 2;

			CPU->interruptStart(0x0048);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;
		}
		else if ((IE & 4) && (IF & 4)) {
			// Timer Interrupt
			CPU->IME = 0;
			IF -= 4;

			CPU->interruptStart(0x0050);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;
		}
		else if ((IE & 8) && (IF & 8)) {
			// Serial Interrupt
			CPU->IME = 0;
			IF -= 8;

			CPU->interruptStart(0x0058);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;
		}
		else if ((IE & 16) && (IF & 16)) {
			// Joypad Interrupt
			CPU->IME = 0;
			IF -= 16;

			CPU->interruptStart(0x0060);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;
		}
	}

	if (CPU->instructionsBeforeIMESet > 0) {
		CPU->IME = 1;
		CPU->instructionsBeforeIMESet = 0;
	}
}