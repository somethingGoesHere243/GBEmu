#pragma once
#include "../Memory/Memory.h"
#include "../APU/APU.h"
#include "Screen.h"
#include "FIFO.h"

#include "../Debug/TileMap.h"

using byte = uint8_t;
using address = unsigned short;

// Each of the 40 entries in the OAM (0xFE00 - 0xFE9F) take the below form
struct OAMEntry {
	byte yPos;
	byte xPos;
	byte tileIndex;

	// The bits of Attributes hold the following meanings:
	// Bits 0, 1, 2: CGB Palette
	// Bit 3: CGB Bank
	// Bit 4: DMG Palette
	// Bit 5: Flip X
	// Bit 6: Flip Y
	// Bit 7: Priority (If set to 1 BG/Window will be drawn over this unless colour is 0)

	byte Attributes;

	// Flag set to true once this OAM Entry has been fetched/drawn on the current line
	bool beenFetched;
};

class GBPPU {
private:
	// Memory connected to PPU
	GBMemory* mem;

	// Screen connected to PPU
	Screen* screen;

	// APU connect to PPU
	GBAPU* APU;

	// Column of next pixel to be drawn
	int pixelColumn{ 0 };

	// Store next line of window to be drawn
	int currWindowY{ 0 };

	// At the start of each scanline check if part of the window intersects it
	bool windowActive{ false };

	// When PPU reaches the first pixel of a window row it needs to throw out the current background tile data
	bool nextPixelIsWindow{ false };

	// At the start of each scanline need to discard number of pixels equal to SCX (see below)
	int discardedPixelsThisRow{ 0 };

	// Track number of dots (cycles) spent on the current row (new row starts after 456 dots)
	// If in VBlank mode takes 4560 dots to exit that mode
	int dotsOnCurrentRow{ 0 };

	// Number of dots for PPU to remain idle following certain actions
	int dotsToIdle{ 0 };

	// Keep track of all currently active STAT Interrupt sources
	// bit 6 set if LYC == LY
	// bit 5 set if PPUMode == 2
	// bit 4 set if PPUMode == 1
	// bit 3 set if PPUMode == 0
	byte activeSTATSources{ 0 };

	// Store whether a STAT interrupt is currently being requested
	bool isSTATInterrupt{ false };

	// Check if PPU was just turned back on
	bool justTurnedOn{ false };

	// During PPUMode 2 the PPU retrieves 10 entries from the OAM which lie on the current scanline
	OAMEntry currLineObjects[10];

	// Keep track of number of OAM entries retrieved on the current scanline
	int currLineObjectsCount{ 0 };

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

	// Background Palette Data: address FF47
	byte& BGP;

	// Object Palette Data
	byte& OBP0; // Address FF48
	byte& OBP1; // Address FF49

	// Top Left coordinates of current window on the screen
	byte& WY; // Address FF4A
	byte& WX; // Address FF4B

	// 2 FIFOS linked to PPU
	FIFO backgroundFIFO;
	FIFO objectFIFO;

	// Flag to activate when objectFIFO is fetching a sprite
	bool objectFIFOActive = false;

	// Object currently being processed in the objectFIFO
	OAMEntry* activeObj;

public:	
	// Creates new PPU linked to the given screen and memory
	GBPPU(GBMemory* mem, Screen* screen, GBAPU* APU);

	// Resets the PPU to its default state
	void reset();

	// Sets the current tile in FIFO's to push pixels from
	void setTile();

	// Sets tile data in FIFO's from current tile
	void setTileDataLow();
	void setTileDataHigh();

	// Push 8 pixels from tile data into FIFO (returns false if pixels failed to be pushed)
	bool pushPixels();

	// Same as the above 4 functions but for the objectFIFO
	void objSetTile();
	void objSetTileDataLow();
	void objSetTileDataHigh();
	bool objPushPixels();

	// Draws pixel (popped from FIFO) to screen
	void drawPixel();

	// Checks if a STAT Interrupt should be triggered
	void checkForSTATInterrupt(bool vblankStarted);

	void update();

	GBMemory* getMem() { return mem; }
};