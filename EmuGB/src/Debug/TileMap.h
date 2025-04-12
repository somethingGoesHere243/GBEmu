#pragma once
#include "../Memory/Memory.h"
#include"../PPU/Screen.h"

class TileMap {
	GBMemory* mem;

	Screen screen{ 128, 192,  3, "Debug TileMap"};

public:
	TileMap(GBMemory* mem) :mem{ mem } {};

	void render();
};