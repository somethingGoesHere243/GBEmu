#pragma once
#include "CPU/CPU.h"
#include "PPU/Screen.h"
#include "PPU/PPU.h"
#include "InterruptHandler.h"
#include "Timer.h"
#include "Input.h"

#include "Debug/TileMap.h"

class GB {
private:
	Screen screen{ 160, 144, 3, "GBEmu"};

	GBPPU PPU{ &Mem, &screen };

	GBCPU CPU{ &Mem };

	InterruptHandler interruptHandler{ &CPU, &PPU, &Mem };

	Timer timer{ &Mem };
public:
	Controller controller{ &Mem };

	GBMemory Mem;

	void init() { Mem.init(); }

	void loadROM(std::string filePath) { Mem.loadROM(filePath); }

	void update(TileMap* tileMap);

	void runTests();
};