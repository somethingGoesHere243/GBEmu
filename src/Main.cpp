#include "Memory/Memory.h"
#include "CPU/CPU.h"
#include "CPU/CPUTests.h"
#include "GB.h"

#include "Debug/TileMap.h"

#include <SDL3/SDL.h>

#include <iostream>
#include <vector>
#include <Windows.h>

int main() {
	GB* mainGB = new GB;

	mainGB->init();

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
				mainGB->controller.pressButton(e.key.key);
			}
			else if (e.type == SDL_EVENT_KEY_UP) {
				mainGB->controller.releaseButton(e.key.key);
			}
		}
		// Check if a ROM is loaded
		if (mainGB->ROMLoaded) {
			// Gameboy goes thru 17556 cycles per frame
			for (int i = 0; i < 17556; ++i) {
				mainGB->update();
			}
		}
	}
}