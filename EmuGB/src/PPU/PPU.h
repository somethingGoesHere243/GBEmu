#pragma once
#include "../Memory.h"
#include "Screen.h"
#include "FIFO.h"

using byte = uint8_t;
using address = unsigned short;

class GBPPU {
private:
	// Memory connected to PPU
	GBMemory* mem;

	// Screen connected to PPU
	Screen* screen;

	// Column of next pixel to be drawn
	int pixelColumn{ 0 };

	// Track number of dots (cycles) spent on the current row (new row starts after 456 dots)
	// If in VBlank mode takes 4560 dots to exit that mode
	int dotsOnCurrentRow{ 0 };

	// Number of dots for PPU to remain idle following certain actions
	int dotsToIdle{ 0 };

	// LCD Control Bits: address FF40 in memory
	byte& LCDC;

	// LCD Status Bits: address FF41
	byte& STAT;

	// Top Left coordinates of current viewport with the background map
	byte& SCY; // Address FF42
	byte& SCX; // Address FF43

	// Current line for LCD drawing: address FF44
	byte& LY;

	// Byte to be constantly compared to LY: address FF45
	byte& LYC;

	// 2 FIFOS linked to PPU
	FIFO backgroundFIFO;
	// TODO: FIFO objectFIFO;

public:	
	// Creates new PPU linked to the given screen and memory
	GBPPU(GBMemory* mem, Screen* screen);

	// Sets the current tile in FIFO's to push pixels from
	void setTile();

	// Sets tile data in FIFO's from current tile
	void setTileData();

	// Push 8 pixels from tile data into FIFO (returns false if pixels failed to be pushed)
	bool pushPixels();

	// Draws pixel (popped from FIFO) to screen
	void drawPixel();

	void update();

	GBMemory* getMem() { return mem; }
};