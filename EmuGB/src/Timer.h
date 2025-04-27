#pragma once
#include "Memory/Memory.h"
#include "CPU/CPU.h"

class Timer {
private:
	GBMemory* mem;

	// Internal clock of the timer (increments once every CPU cycle)
	byte ticks{ 204 };

	// Divider Register: Incremented once every 64 ticks
	byte& DIV; // Address FF04

	// Timer Counter: Increments at the rate given by TAC
	byte& TIMA; // Address FF05

	// Timer Modulo: Value to set TIMA to when it overflows
	byte& TMA; // Address FF06

	// Timer Control bits:
	// Bits 0 & 1 determine the frequency at which TIMA should increment
	// Bit 2 enables the incrementing of TIMA
	byte& TAC; // Address FF07
		
	// Store value of bit selected by TAC on previous timer update
	bool prevTACBit{false};

	// Store whether or not an overflow occured in the TIMA register on the previous cycle
	bool TIMAOverflowed{ false };
public:
	Timer(GBMemory* mem);

	void update();
};