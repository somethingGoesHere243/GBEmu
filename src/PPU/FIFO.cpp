#include "PPU/FIFO.h"

int FIFO::popPixel() {
	int poppedPixel = pixels[0];

	for (int i = 0; i < 15; ++i) {
		pixels[i] = pixels[i + 1];
	}
	pixels[15] = 0;

	--pixelCount;
	return poppedPixel;
}

void FIFO::reset() {
	pixelCount = 0;
	xPos = 0;
	step = GET_TILE;
}