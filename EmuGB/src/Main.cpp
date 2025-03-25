#include "Memory.h"
#include "CPU/CPU.h"
#include "CPU/CPUTests.h"
#include "GB.h"

#include <iostream>
#include <vector>
#include <windows.h>

int main() {
	GB* testGB = new GB;

	// testGB->runTests();
	
	testGB->init();

	// Keep Window open until closed
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		// Check if program closed
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}

		for (int i = 0; i < 17556; ++i) {
			testGB->update();
		}
		Sleep(50);
	}

	
}