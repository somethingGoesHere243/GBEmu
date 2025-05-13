#include "InterruptHandler.h"

InterruptHandler::InterruptHandler(GBCPU* CPU, GBPPU* PPU, GBMemory* mem) : CPU{ CPU }, 
																			PPU{ PPU }, 
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
			CPU->conditionalCall(0x0040, 1);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;

			// An additional 2 cycles are spent in a wait state
			CPU->cyclesRemaining += 2;
		}
		else if ((IE & 2) && (IF & 2)) {
			// LCD Interrupt
			CPU->IME = 0;
			IF -= 2;

			CPU->conditionalCall(0x0048, 1);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;

			CPU->cyclesRemaining += 2;
		}
		else if ((IE & 4) && (IF & 4)) {
			// Timer Interrupt
			CPU->IME = 0;
			IF -= 4;

			CPU->conditionalCall(0x0050, 1);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;

			CPU->cyclesRemaining += 2;
		}
		else if ((IE & 8) && (IF & 8)) {
			// Serial Interrupt
			CPU->IME = 0;
			IF -= 8;

			CPU->conditionalCall(0x0058, 1);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;

			CPU->cyclesRemaining += 2;
		}
		else if ((IE & 16) && (IF & 16)) {
			// Joypad Interrupt
			CPU->IME = 0;
			IF -= 16;

			CPU->conditionalCall(0x0060, 1);
			CPU->OPCode = 0;
			CPU->OPCodeStep = 0;

			CPU->cyclesRemaining += 2;
		}
	}
}