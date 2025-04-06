#include "Memory.h"

#include <fstream>

void GBMemory::init() {
	// All Addresses written to here are of the form $FF00 + some byte
	address baseAddress = 0xFF00; // $FF00

	data[baseAddress] = 0x3F;
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
	data[baseAddress + 0x50] = 0xFF;
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

byte& GBMemory::read(address addr) {
	if (isAccessible(addr)) {
		// Memory is accessible

		// If reading an address which shouldnt be overwritten dont return reference to the register
		if (addr < 0x8000 || addr == 0xFF44) {
			garbageVal = data[addr];
			return garbageVal;
		}

		return data[addr];
	}
	// Else return garbage value
	return garbageVal;
}

byte& GBMemory::PPURead(address addr) {
	return data[addr];
}

void GBMemory::write(address addr, byte newVal) {
	// Attempting to write to LY register should be ignored
	if (addr == 0xFF44) { return; }

	// Attempting to overwrite ROM from the cartridge should be ignored
	if (addr < 0x8000) { return; }

	// Attempting to write to address 0xFF46 triggers a DMA Transfer
	if (addr == 0xFF46) {
		data[0xFF46] = newVal;
		DMATransfer();
		return;
	}

	if (isAccessible(addr)) {
		// Memory is accessible
		data[addr] = newVal;

		// Any attempt to write to the DIV register resets its value to 0
		if (addr == 0xFF04) {
			data[addr] = 0;
		}
	}
}

void GBMemory::DMATransfer() {
	// TODO: Lock most of memory during the transfer

	// Value in 0xFF46 multiplied by 0x0100 specifies the source of the transfer
	int source = data[0xFF46] * 0x0100;
	for (int i = 0; i < 0x00A0; ++i) {
		data[0xFE00 + i] = data[source + i];
	}

	return;
}