#include "Timer.h"

Timer::Timer(GBMemory* mem) : mem {mem},
							  DIV{ mem->PPURead(0xFF04) },
							  prevDivVal{ mem->prevDivVal },
							  TIMA{ mem->PPURead(0xFF05) },
							  TMA{ mem->PPURead(0xFF06) },
							  TAC{ mem->PPURead(0xFF07) } {
}

void Timer::reset() {
	ticks = 51;
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
		// Check a new value hasn't already been written to TIMA
		if (TIMA == 0) {
			// Request timer interrupt (set bit 2 of IF)
			byte currentIF = mem->read(0xFF0F);
			mem->write(0xFF0F, currentIF | 4);

			// Reset to the value stored in TMA register
			TIMA = TMA;
		}

		TIMAOverflowed = false;
	}

	// DIV equal to the ticks value Right-Shifted by 6
	if (ticks % 64 == 0) {
		++DIV;
	}

	// Frequency of incrementing TIMA is determined by bits 0 and 1 of TAC
	// TIMA is incremented when the chosen bit goes from a 1 to a 0
	int incTIMABit;
	switch (TAC & 3) {
	case 0:
		incTIMABit = 1 << 7;
		break;
	case 1:
		incTIMABit = 1 << 1;
		break;
	case 2:
		incTIMABit = 1 << 3;
		break;
	default:
		incTIMABit = 1 << 5;
		break;
	}

	bool timerEnabled = TAC & 4;

	// TIMA Incremented when the value of below bool goes from 1 to 0
	bool currTACBit = timerEnabled && (ticks & incTIMABit);
	if (prevTACBit && !currTACBit) {
		++TIMA;
		// Check for overflow of TIMA
		if (TIMA == 0) {
			TIMAOverflowed = true;
		}
	}
	prevTACBit = currTACBit;
}