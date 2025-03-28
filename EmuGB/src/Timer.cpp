#include "Timer.h"

Timer::Timer(GBMemory* mem) : mem {mem},
							  DIV{ mem->read(0xFF04) },
							  TIMA{ mem->read(0xFF05) },
							  TMA{ mem->read(0xFF06) },
							  TAC{ mem->read(0xFF07) }{
}

void Timer::update() {
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

	// DIV incremented every 256 ticks
	if (ticks % 256 == 0) {
		++DIV;
	}

	// Frequency of incrementing TIMA is determined by bits 0 and 1 of TAC
	int cyclesPerIncrement;
	switch (TAC & 3) {
	case 0:
		cyclesPerIncrement = 1024;
		break;
	case 1:
		cyclesPerIncrement = 16;
		break;
	case 2:
		cyclesPerIncrement = 64;
		break;
	default:
		cyclesPerIncrement = 256;
		break;
	}

	// TIMA incremented only if bit 2 of TAC is set
	if ((TAC & 4) && (ticks % cyclesPerIncrement == 0)) {
		++TIMA;
		// Check for overflow of TIMA
		if (TIMA == 0) {
			TIMAOverflowed = true;	
		}
	}
}