#include "Debug/TileMap.h"

void TileMap::render() {
	address baseAddress = 0x8000;
	for (int tileID = 0; tileID < 384; ++tileID) {
		int row = tileID / 16;
		int col = tileID % 16;
		for (int tileRow = 0; tileRow < 8; ++tileRow) {
			byte tileDataLow = mem->PPURead(baseAddress + tileID * 0x0010 + tileRow * 0x0002);
			byte tileDataHigh = mem->PPURead(baseAddress + tileID * 0x0010 + tileRow * 0x0002 + 1);
			for (int i = 0; i < 8; ++i) {
				int pixelColor = 2 * ((tileDataHigh >> i) & 1) + ((tileDataLow >> i) & 1);

				int r{ 155 };
				int g{ 188 };
				int b{ 15 };
				switch (pixelColor) {
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
				int pixelIndex = row * 1024 + tileRow * 128 + col * 8 + 7 - i;
				screen.editPixel(pixelIndex, r, g, b);
			}
		}
	}

	screen.loadFromSurface();
	screen.render();
}