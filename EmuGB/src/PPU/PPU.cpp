#include "PPU.h"
#include "windows.h"

GBPPU::GBPPU(GBMemory* mem, Screen* screen) : mem{ mem }, 
											  screen{ screen }, 
											  LCDC{mem->PPURead(0xFF40)},
											  STAT{mem->PPURead(0xFF41)},
											  SCY{ mem->PPURead(0xFF42) },
											  SCX{ mem->PPURead(0xFF43) },
											  LY{mem->PPURead(0xFF44)},
											  LYC{mem->PPURead(0xFF45)} {}

void GBPPU::setTile() {
	// Tile map is determined by LCD Control bits
	int tileMap{ 0 };

	// Check bit 3 of LCDC
	if (LCDC & 8) {
		tileMap = 1;
	}
	// TODO: Add check if pixel is inside a window

	// Calculate coordinates of tile within map
	int x = (backgroundFIFO.xPos + (SCX / 8)) & 0x1F;

	int y = ((LY + SCY) & 0xFF) / 8;

	Tile tile{ tileMap, x, y };
	backgroundFIFO.currTile = tile;
}

void GBPPU::setTileDataLow() {
	// Get ID of tile of interest
	address IDAddress = 0x9800 + 0x0400 * (backgroundFIFO.currTile.tileMap) + 0x0020 * (backgroundFIFO.currTile.yCoord) + backgroundFIFO.currTile.xCoord;
	 byte tileID = mem->PPURead(IDAddress);


	// Specific byte we want to read within the Tile data
	byte offset = 2 * ((LY + SCY) % 8);

	// Determine which block of tiles we want to read data from
	address tileBlock{ 0x9000 };
	if (tileID & 128) {
		tileID -= 128;
		tileBlock = 0x8800;
	}
	// Check bit 4 of LCDC
	else if (LCDC & 16) {
		tileBlock = 0x8000;
	}
	backgroundFIFO.currTileDataLow = mem->PPURead(tileBlock + tileID * 0x0010 + offset);
}

void GBPPU::setTileDataHigh() {
	// Get ID of tile of interest
	address IDAddress = 0x9800 + 0x0400 * (backgroundFIFO.currTile.tileMap) + 0x0020 * (backgroundFIFO.currTile.yCoord) + backgroundFIFO.currTile.xCoord;
	byte tileID = mem->PPURead(IDAddress);


	// Specific byte we want to read within the Tile data
	byte offset = 2 * ((LY + SCY) % 8);

	// Determine which block of tiles we want to read data from
	address tileBlock{ 0x9000 };
	if (tileID & 128) {
		tileID -= 128;
		tileBlock = 0x8800;
	}
	// Check bit 4 of LCDC
	else if (LCDC & 16) {
		tileBlock = 0x8000;
	}
	backgroundFIFO.currTileDataHigh = mem->PPURead(tileBlock + tileID * 0x0010 + offset + 1);
}

bool GBPPU::pushPixels() {
	// If not enough space in FIFO to push 8 pixels return early
	if (backgroundFIFO.pixelCount > 8) {
		return false;
	}

	for (int i = 7; i >= 0; --i) {
		bool leastSigBit = backgroundFIFO.currTileDataLow & (1 << i);
		bool mostSigBit = backgroundFIFO.currTileDataHigh & (1 << i);

		backgroundFIFO.pixels[backgroundFIFO.pixelCount] = 2 * mostSigBit + leastSigBit;
		++backgroundFIFO.pixelCount;
	}
	++backgroundFIFO.xPos;
	return true;
}

void GBPPU::drawPixel() {
	// If there are at least 8 pixels in the FIFO we can draw pixels to the screen
	if (backgroundFIFO.pixelCount > 8) {
		int pixelToDraw = backgroundFIFO.popPixel();
		// Convert pixel (number 0, 1, 2, or 3) into an rgb value
		int r{ 155 };
		int g{ 188 };
		int b{ 15 };
		switch (pixelToDraw) {
		case 1:
			r = 139;
			g = 172;
			b = 15;
			break;
		case 2:
			r = 48;
			g = 98;
			b = 48;
			break;
		case 3:
			r = 15;
			g = 56;
			b = 15;
			break;
		}

		// Draw pixel if background is enabled (bit 0 of LCDC Register)
		if (LCDC & 1) {
			// Index of pixel we want to edit (LY gives row of pixel)
			int pixelIndex = 160 * LY + pixelColumn;
			screen->editPixel(pixelIndex, r, g, b);
		}

		// Update data for next pixel to be drawn
		++pixelColumn;
		if (pixelColumn == 160) {
			// Begin HBlank mode (PPUMode goes from 3 to 0)
			STAT -= 3;
		}
	}
}

void GBPPU::update(TileMap* debugTileMap) {
	// Check if PPU is enabled (bit 7 of LCDC)
	if (!(LCDC & 128)) {
		// PPU disabled so return early and set PPU to its inital state
		LY = 0;
		pixelColumn = 0;
		dotsOnCurrentRow = 4;
		dotsToIdle = 0;
		isSTATInterrupt = false;
		justTurnedOn = true;

		// PPUMode set to 0
		STAT = STAT - (STAT & 3);

		return;
	}

	// Check if PPU has just been enabled (Enters a HBlank for 76 dots)
	if (justTurnedOn) {
		++dotsOnCurrentRow;
		// Check if HBlank mode should end
		if (dotsOnCurrentRow == 80) {
			// PPUMode set to 3
			STAT = STAT - (STAT & 3) + 3;

			backgroundFIFO.reset();
			justTurnedOn = false;
		}
		return;
	}

	// Get current PPU Mode from the 2 least sig bits of STAT register
	byte PPUMode = STAT & 3;
	mem->PPUMode = PPUMode;

	// Set bit 2 of the STAT register if LYC matches LY
	if (LYC == LY) {
		STAT = STAT | 4;
	}
	else {
		STAT = STAT - (STAT & 4);
	}

	// Store old value of isSTATInterrupt
	bool prevInterrupt = isSTATInterrupt;
	isSTATInterrupt = false;

	// Check if a STAT interrupt should be requested this cycle
	// 4 conditions for an interrupt to be requested:
	
	// If bit 3 of the STAT register set and in mode 0
	isSTATInterrupt = (STAT & 8) && (PPUMode == 0);

	// If bit 4 of the STAT register set and in mode 1
	isSTATInterrupt = isSTATInterrupt || ((STAT & 16) && (PPUMode == 1));

	// If bit 5 of the STAT register set and in mode 2
	isSTATInterrupt = isSTATInterrupt || ((STAT & 32) && (PPUMode == 2));

	// If bits 2 and 6 of the STAT register set
	isSTATInterrupt = isSTATInterrupt || ((STAT & 64) && (STAT & 4));

	// If an interrupt is being requested set bit 1 of the IF register
	// (Only if an interrupt wasnt requested in the previous cycle)
	if (!prevInterrupt && isSTATInterrupt) {
		byte currentIF = mem->PPURead(0xFF0F);
		mem->write(0xFF0F, currentIF | 2);
	}

	// One pixel is drawn to the screen per dot when in mode 3
	if (PPUMode == 3 && LY < 144) {
		drawPixel();
	}

	// Check if PPU needs to wait before next update
	if (dotsToIdle > 0) {
		++dotsOnCurrentRow;
		--dotsToIdle;
		return;
	}

	// HBlank Mode
	if (PPUMode == 0) {
		++dotsOnCurrentRow;
		// Check if HBlank mode should end
		if (dotsOnCurrentRow == 456) {
			// Start a new row
			++LY;
			pixelColumn = 0;

			// Reset dots counter
			dotsOnCurrentRow = 0;

			// Check if new row is in a VBlank
			if (LY >= 144) {
				// PPUMode set to 1
				++STAT;

				// Request a VBlank interrupt (set bit 0 of the IF register)
				byte currentIF = mem->PPURead(0xFF0F);
				mem->write(0xFF0F, currentIF | 1);

				// Render image to screen
				screen->loadFromSurface();
				screen->render();

				// Render debug tilemap
				debugTileMap->render();
			}
			else {
				// PPUMode set to 2
				STAT += 2;
			}
		}
	}

	// VBlank Mode
	else if (PPUMode == 1) {
		++dotsOnCurrentRow;
		// Stop requesting VBlank interrupt (Only on first dot of the VBlank)
		
		// Check if a new row should have been started
		if (dotsOnCurrentRow == 456) {
			++LY;
			dotsOnCurrentRow = 0;
		}
		// Check if VBlank mode should end
		if (LY == 154 || LY == 1) {
			// Set PPUMode to 2
			++STAT;

			// Reset LY and pixel column
			LY = 0;
			pixelColumn = 0;

			// Reset dots counter
			dotsOnCurrentRow = 0;
		}
	}

	// OAM Scan Mode
	else if (PPUMode == 2) {
		++dotsOnCurrentRow;

		// TODO: Finish Implementation 

		// Mode lasts for 80 dots
		if (dotsOnCurrentRow == 80) {
			++STAT;
			// Clear Pixel FIFO's
			backgroundFIFO.reset();
		}
	}

	// Pixel Drawing Mode
	else if (PPUMode == 3) {
		// Check current step for the FIFO
		switch (backgroundFIFO.step) {
		case GET_TILE:
			setTile();
			++dotsOnCurrentRow;
			dotsToIdle = 1;
			backgroundFIFO.step = GET_TILE_DATA_LOW;
			break;
		case GET_TILE_DATA_LOW:
			setTileDataLow();
			++dotsOnCurrentRow;
			dotsToIdle = 1;
			backgroundFIFO.step = GET_TILE_DATA_HIGH;
			break;
		case GET_TILE_DATA_HIGH:
			setTileDataHigh();
			++dotsOnCurrentRow;
			dotsToIdle = 1;
			backgroundFIFO.step = SLEEP;
			break;
		case SLEEP:
			++dotsOnCurrentRow;
			dotsToIdle = 1;
			backgroundFIFO.step = PUSH;
			break;
		case PUSH:
			// Attempt to push pixels to FIFO 
			if (pushPixels()) {
				// Successfully pushed pixels so change FIFO step
				backgroundFIFO.step = GET_TILE;
			}

			++dotsOnCurrentRow;
			break;
		}
	}
}