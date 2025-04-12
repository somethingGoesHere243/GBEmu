#pragma once

#include <SDL3/SDL.h>
#include "Memory/Memory.h"

// Inputs are mapped as follows:
// W -> DPad UP
// A -> DPad Left
// S -> DPad Down
// D -> DPad Right
// 
// O -> B button
// P -> A button
// Enter Key -> Start Button
// Right Shift -> Select Button

// TODO: Allow customisable controls

class Controller {
private:
	// Keep track of which buttons are currently pressed
	bool rightPressed = false;
	bool leftPressed = false;
	bool upPressed = false;
	bool downPressed = false;
	bool aPressed = false;
	bool bPressed = false;
	bool startPressed = false;
	bool selectPressed = false;

	// An interrupt is requested whenever a button is pressed
	byte& IF; // Address 0xFF0F in memory

public:
	Controller(GBMemory* mem) : IF{ mem->PPURead(0xFF0F) } {};

	// Checks if a button should be pressed
	void pressButton(SDL_Keycode keyCode);

	// Check if a button should be released
	void releaseButton(SDL_Keycode keyCode);

	// Update the JOYP register according to which buttons are currently pressed
	void update(GBMemory* mem);
};