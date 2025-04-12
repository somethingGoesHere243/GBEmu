#pragma once
#include "Memory/Memory.h"
#include "CPU/CPU.h"
#include "PPU/PPU.h"

class InterruptHandler {
private:
	GBCPU* CPU;

	GBPPU* PPU;

	// Interrupt Enable register
	// Controls which interrupt handler functions can be called:
	// bit 0 set -> VBlank interrupt handler enabled 
	// bit 1 set -> LCD interrupt handler enabled 
	// bit 2 set -> Timer interrupt handler enabled 
	// bit 3 set -> Serial interrupt handler enabled 
	// bit 4 set -> Joypad interrupt handler enabled 
	byte& IE; // Address FFFF

	// Interrupt Flag register
	// Controls which interrupt handlers are attempted to be called: (same bit -> interrupt correspondance as above)
	byte& IF; // Address FF0F
public:
	InterruptHandler(GBCPU* CPU, GBPPU* PPU, GBMemory* mem);

	// Handle interrupts
	void update();
};