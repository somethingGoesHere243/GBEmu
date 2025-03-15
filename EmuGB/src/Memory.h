#pragma once
#include <stdint.h>

// GB Memory consists of memory addressed from 0000 to FFFF (2^16-1)
using address = unsigned short;
constexpr unsigned int addressCount = 65536; // 2^16

// Each address points to 8 bits (1 byte) of data
using byte = uint8_t;

class GBMemory {
public:
	byte data[addressCount] { 0 };
	// Memory mapped in the following way
	// 0000 - 3FFF: 16KiB ROM Bank 0          (From Cartridge)
	// 4000 - 7FFF: 16Kib ROM Bank 1          (From Cartridge) 
	// 8000 - 9FFF: 8 KiB Video RAM           (CGB Mode)
	// A000 - BFFF: 8 KiB External RAM	      (From Cartridge)
	// C000 - CFFF: 4 KiB Work RAM
	// D000 - DFFF: 4 KiB Work RAM            (CGB Mode)
	// E000 - FDFF: Mirror of C000 - DDFF     (Use Prohibited)
	// FE00 - FE9F: Object-Attribute-Memory 
	// FEA0 - FEFF: Unused                    (Use Prohibited)
	// FF00 - FF7F: I/O Registers
	// FF80 - FFFE: High RAM
	// FFFF - FFFF: Interrupt Enable Register
};