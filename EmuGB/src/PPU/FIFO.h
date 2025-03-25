#pragma once
#include <stdint.h>

using byte = uint8_t;
using address = unsigned short;

// Pixels to be pushed into FIFO
struct Tile {
	// Tile Map containing the desired tile
	int tileMap;

	// Coordinates of the tile within the tile map
	int xCoord;
	int yCoord;
};

enum FIFOStep {
	GET_TILE,
	GET_TILE_DATA,
	SLEEP,
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

	// Current tile which FIFO is pulling data from
	Tile currTile{ 0,0,0 };

	// Tile data to be pushed into FIFO
	byte currTileDataLow;
	byte currTileDataHigh;

	// Next action FIFO needs to perform when updated
	FIFOStep step{ GET_TILE };

	int popPixel();
	void reset();
};