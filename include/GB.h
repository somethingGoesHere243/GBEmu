#pragma once
#include <Windows.h>
#include <SDL3/SDL.h>

#include "APU/APU.h"
#include "CPU/CPU.h"
#include "PPU/Screen.h"
#include "PPU/PPU.h"
#include "InterruptHandler.h"
#include "Timer.h"
#include "Input.h"

#include "Debug/TileMap.h"

class GB {
private:
	Screen screen{ 160, 144, 2, "GBEmu", true};

	GBAPU APU{};

	GBPPU PPU{ &Mem, &screen, &APU };

	GBCPU CPU{ &Mem };

	InterruptHandler interruptHandler{ &CPU, &Mem };

	Timer timer{ &Mem };

	// Store the original windows procedure for win32 menu handling
	WNDPROC originalWndProc = nullptr;
public:
	Controller controller{ &Mem };

	GBMemory Mem{ &APU };

	bool ROMLoaded{ false };

	~GB();

	void init();

	void reset();

	void loadROM(std::string filePath);

	void update();

	void runTests();

	void setRenderScale(int scale) { screen.setRenderScale(scale); }

	SDL_Window* getWindow() { return screen.getWindow(); }

	WNDPROC getWindProc() { return originalWndProc; }
};