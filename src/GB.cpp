#include <SDL3/SDL.h>
#include <Windows.h>

#include "GB.h"
#include "PPU/Menu.h"
#include "MenuHandler.h"

#include "CPU/CPUTests.h"

void GB::update() { 
	CPU.update();

	Mem.update();
	interruptHandler.update();

	// PPU updates 4 times for each CPU Update
	PPU.update();
	APU.update();
	PPU.update();
	APU.update();
	PPU.update();
	APU.update();
	PPU.update();
	APU.update();

	timer.update();

	// Update inputs
	controller.update(&Mem);
	
}

void GB::init() {
	// Setup win32 menubar
	SDL_PropertiesID windowProperties = SDL_GetWindowProperties(screen.getWindow());
	HWND handle = (HWND)SDL_GetPointerProperty(windowProperties, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
	HMENU menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(handle, menu);

	// Give window access to the GB object
	SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)this);

	// Replace WndProc with custom handler
	originalWndProc = (WNDPROC)SetWindowLongPtr(handle, GWLP_WNDPROC, (LONG_PTR)CustomWndProc);
}

void GB::reset() {
	Mem.init();

	CPU.reset();
	APU.reset();
	PPU.reset();
	timer.reset();
	screen.reset();
}

void GB::loadROM(std::string filePath) {
	ROMLoaded = true;
	reset();

	Mem.loadROM(filePath);
}

void GB::runTests() {
	int totalPassedTests = 0;

	totalPassedTests += testUnprefixedCodes(&CPU);
	totalPassedTests += testPrefixedCodes(&CPU);

	std::cout << "TOTAL TESTS PASSED: " << totalPassedTests << std::endl;
}

GB::~GB() {
	// Clean up win32
	// Restore original WndProc
	SDL_PropertiesID windowProperties = SDL_GetWindowProperties(screen.getWindow());
	HWND handle = (HWND)SDL_GetPointerProperty(windowProperties, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
	SetWindowLongPtr(handle, GWLP_WNDPROC, (LONG_PTR)originalWndProc);

	// Quit SDL subsystems
	SDL_Quit();
}