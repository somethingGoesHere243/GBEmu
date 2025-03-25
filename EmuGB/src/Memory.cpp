#include "Memory.h"

#include <fstream>

void GBMemory::init() {
	// All Addresses written to here are of the form $FF00 + some byte
	address baseAddress = 0xFF00; // $FF00

	data[baseAddress] = 0xCF;
	data[baseAddress + 0x02] = 0x7E;
	data[baseAddress + 0x04] = 0x18;
	data[baseAddress + 0x07] = 0xF8;
	data[baseAddress + 0x0F] = 0xE1;
	data[baseAddress + 0x10] = 0x80;
	data[baseAddress + 0x11] = 0xBF;
	data[baseAddress + 0x12] = 0xF3;
	data[baseAddress + 0x13] = 0xFF;
	data[baseAddress + 0x14] = 0xBF;
	data[baseAddress + 0x16] = 0x3F;
	data[baseAddress + 0x18] = 0xFF;
	data[baseAddress + 0x19] = 0xBF;
	data[baseAddress + 0x1A] = 0x7F;
	data[baseAddress + 0x1B] = 0xFF;
	data[baseAddress + 0x1C] = 0x9F;
	data[baseAddress + 0x1D] = 0xFF;
	data[baseAddress + 0x1E] = 0xBF;
	data[baseAddress + 0x20] = 0xFF;
	data[baseAddress + 0x23] = 0xBF;
	data[baseAddress + 0x24] = 0x77;
	data[baseAddress + 0x25] = 0xF3;
	data[baseAddress + 0x26] = 0xF1;
	data[baseAddress + 0x40] = 0x91;
	data[baseAddress + 0x41] = 0x81;
	data[baseAddress + 0x44] = 0x91;
	data[baseAddress + 0x46] = 0xFF;
	data[baseAddress + 0x47] = 0xFC;
	data[baseAddress + 0x4D] = 0x7E;
	data[baseAddress + 0x4F] = 0xFE;
	data[baseAddress + 0x51] = 0xFF;
	data[baseAddress + 0x52] = 0xFF;
	data[baseAddress + 0x53] = 0xFF;
	data[baseAddress + 0x54] = 0xFF;
	data[baseAddress + 0x55] = 0xFF;
	data[baseAddress + 0x56] = 0x3E;
	data[baseAddress + 0x70] = 0xF8;
}

void GBMemory::loadROM(std::string filePath) {
	// Load ROM/text file into a file stream
	std::ifstream fileStream;
	fileStream.open(filePath, std::ios::in | std::ios::binary);

	if (!fileStream) {
		std::cerr << "Failed to open the given ROM\n";
		return;
	}

	// Read 1 character at a time from ROM and write to memory
	char c;
	address currAddress = 0x0000;

	while (fileStream.get(c)) {
		data[currAddress] = c;
		++currAddress;
	}

	fileStream.close();

	// TODO Add MBC functionality
}

bool GBMemory::isAccessible(address addr) {
	// Check if memory is in OAM (disabled if PPU mode is 2 or 3)
	if ((PPUMode == 2 || PPUMode == 3) && addr <= 0xFE9F && addr >= 0xFE00) {
		// Memory disabled 
		return false;
	}
	// Check if memory is in VRAM (disabled in mode 3)
	if (PPUMode == 3 && addr <= 0x97FF && addr >= 0x8000) {
		// Memory disabled 
		return false;
	}
	// Check if memory is pointing to a palette (disabled in mode 3)
	if (PPUMode == 3 && addr <= 0xFF49 && addr >= 0xFF47) {
		// Memory disabled 
		return false;
	}

	// Otherwise memory is accessible
	return true;
}

// TODO: Work out correct CPU and PPU timings to allow for locking off of memory at certain times

byte& GBMemory::read(address addr) {
	if (true || isAccessible(addr)) {
		// Memory is accessible
		return data[addr];
	}
	// Else return garbage value
	return garbageVal;
}

byte& GBMemory::PPURead(address addr) {
	return data[addr];
}

void GBMemory::write(address addr, byte newVal) {
	if (true || isAccessible(addr)) {
		// Memory is accessible
		data[addr] = newVal;
	}
}