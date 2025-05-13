#include "Timer.h"

Timer::Timer(GBMemory* mem) : mem {mem},
							  DIV{ mem->PPURead(0xFF04) },
							  TIMA{ mem->PPURead(0xFF05) },
							  TMA{ mem->PPURead(0xFF06) },
							  TAC{ mem->PPURead(0xFF07) } {
}

void Timer::reset() {
	ticks = 204;
	prevTACBit = false;
	TIMAOverflowed = false;
}

void Timer::update() {
	// Check if timer needs to be reset
	if (mem->resetTimer) {
		ticks = 0;
		mem->resetTimer = false;
	}

	++ticks;

	// Check if TIMA overflowed on previous cycle
	if (TIMAOverflowed) {
		// Request timer interrupt (set bit 2 of IF)
		byte currentIF = mem->read(0xFF0F);
		mem->write(0xFF0F, currentIF | 4);

		// Reset to the value stored in TMA register
		TIMA = TMA;

		TIMAOverflowed = false;
	}

	// DIV equal to the ticks value Right-Shifted by 6
	if (ticks % 256 == 0) {
		++DIV;
	}

	// Frequency of incrementing TIMA is determined by bits 0 and 1 of TAC
	// TIMA is incremented when the chosen bit goes from a 1 to a 0
	int incTIMABit;
	switch (TAC & 3) {
	case 0:
		incTIMABit = 1 << 9;
		break;
	case 1:
		incTIMABit = 1 << 3;
		break;
	case 2:
		incTIMABit = 1 << 5;
		break;
	default:
		incTIMABit = 1 << 7;
		break;
	}

	// TIMA incremented only if bit 2 of TAC is set
	if (TAC & 4) {
		// TIMA incremented if chosen bit goes from 1 to 0
		if (prevTACBit && !(ticks & incTIMABit)) {
			++TIMA;
			// Check for overflow of TIMA
			if (TIMA == 0) {
				TIMAOverflowed = true;
			}
		}
	}
	prevTACBit = ticks & incTIMABit;
}