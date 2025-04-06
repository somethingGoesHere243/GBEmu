#include "Memory.h"
#include "CPU/CPU.h"
#include "CPU/CPUTests.h"
#include "GB.h"

#include "Debug/TileMap.h"

#include <iostream>
#include <vector>
#include <Windows.h>

int main() {
	GB* testGB = new GB;
	TileMap debugTileMap{ &(testGB->Mem) };

	// testGB->runTests();

	testGB->init();


	// Keep Window open until closed
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		// Check if program closed
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
				quit = true;
			}
			else if (e.type == SDL_EVENT_KEY_DOWN) {
				testGB->controller.pressButton(e.key.key);
			}
			else if (e.type == SDL_EVENT_KEY_UP) {
				testGB->controller.releaseButton(e.key.key);
			}
		}

		// Gameboy goes thru 17556 cycles per frame
		for (int i = 0; i < 17556; ++i) {
			testGB->update(&debugTileMap);
		}
		Sleep(16);
	}
}