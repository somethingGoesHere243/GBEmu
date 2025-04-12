#include "Input.h"

void Controller::pressButton(SDL_Keycode keyCode) {
	switch (keyCode) {
	case SDLK_D:
		rightPressed = true;
		// Request a joypad interrupt (set bit 4 of IF)
		IF = IF | 16;
		break;
	case SDLK_A:
		leftPressed = true;
		IF = IF | 16;
		break;
	case SDLK_W:
		upPressed = true;
		IF = IF | 16;
		break;
	case SDLK_S:
		downPressed = true;
		IF = IF | 16;
		break;
	case SDLK_O:
		bPressed = true;
		IF = IF | 16;
		break;
	case SDLK_P:
		aPressed = true;
		IF = IF | 16;
		break;
	case SDLK_RETURN:
		startPressed = true;
		IF = IF | 16;
		break;
	case SDLK_RSHIFT:
		selectPressed = true;
		IF = IF | 16;
		break;
	}
}

void Controller::releaseButton(SDL_Keycode keyCode) {
	switch (keyCode) {
	case SDLK_D:
		rightPressed = false;
		break;
	case SDLK_A:
		leftPressed = false;
		break;
	case SDLK_W:
		upPressed = false;
		break;
	case SDLK_S:
		downPressed = false;
		break;
	case SDLK_O:
		bPressed = false;
		break;
	case SDLK_P:
		aPressed = false;
		break;
	case SDLK_RETURN:
		startPressed = false;
		break;
	case SDLK_RSHIFT:
		selectPressed = false;
		break;
	}
}

// The following conditions determine which bits of the JOYP register are unset:
// Bit 0 unset if: A button or DPad Right pressed
// Bit 1 unset if: B button or DPad Left pressed
// Bit 2 unset if: Select button or DPad Up pressed
// Bit 3 unset if: Start button or DPad Down pressed

void Controller::update(GBMemory* mem) {
	// Current state of joypad / controls is stored in address 0xFF00 of memory
	constexpr address JOYP = 0xFF00;
	byte currJOYPVal = mem->read(JOYP);

	// Don't want to change bits 4 - 7 of the JOYP register
	// Initially bits 0, 1, 2, 3 are all set
	byte newJOYPVal = (currJOYPVal & 0b11110000) + 15;

	// If bit 4 is unset read current state of DPad buttons
	if (!(newJOYPVal & 16)) {
		if (rightPressed) {
			newJOYPVal = newJOYPVal - (newJOYPVal & 1);
		}
		if (leftPressed) {
			newJOYPVal = newJOYPVal - (newJOYPVal & 2);
		}
		if (upPressed) {
			newJOYPVal = newJOYPVal - (newJOYPVal & 4);
		}
		if (downPressed) {
			newJOYPVal = newJOYPVal - (newJOYPVal & 8);
		}
	}

	// If bit 5 is unset read current state of non-DPad buttons
	if (!(newJOYPVal & 32)) {
		if (aPressed) {
			newJOYPVal = newJOYPVal - (newJOYPVal & 1);
		}
		if (bPressed) {
			newJOYPVal = newJOYPVal - (newJOYPVal & 2);
		}
		if (selectPressed) {
			newJOYPVal = newJOYPVal - (newJOYPVal & 4);
		}
		if (startPressed) {
			newJOYPVal = newJOYPVal - (newJOYPVal & 8);
		}
	}
	mem->write(JOYP, newJOYPVal);
}