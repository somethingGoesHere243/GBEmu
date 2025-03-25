#pragma once
#include "CPU/CPU.h"
#include "PPU/Screen.h"
#include "PPU/PPU.h"

class GB {
private:
	GBMemory Mem;

	Screen screen{ 3 };

	GBPPU PPU{ &Mem, &screen };

	GBCPU CPU{ &Mem };
public:
	void init() { Mem.init(); }

	void loadROM(std::string filePath) { Mem.loadROM(filePath); }

	void update();

	void runTests();
};