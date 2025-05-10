#pragma once
#include <stdint.h>

using byte = uint8_t;
using address = unsigned short;

enum FIFOStep {
	GET_TILE,
	GET_TILE_DATA_LOW,
	GET_TILE_DATA_HIGH,
	PUSH,
};

class FIFO {
public:
	// FIFO can store up to 16 pixels (each represented by 2 bits);
	int pixels[16];

	// Keep track of current number of pixels being stored
	int pixelCount{ 0 };

	// FIFO keeps track of its own x Position
	int xPos{ 0 };

	// ID of current tile which FIFO is pulling data from
	byte currTileID{ 0 };

	// Tile data to be pushed into FIFO
	byte currTileDataLow;
	byte currTileDataHigh;

	// Next action FIFO needs to perform when updated
	FIFOStep step{ GET_TILE };

	int popPixel();
	void reset();
};