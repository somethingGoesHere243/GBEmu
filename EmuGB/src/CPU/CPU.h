#pragma once
#include "../Memory/Memory.h"

using byte = uint8_t;
using address = unsigned short;

// CPU Flags to be used in F register
constexpr byte Z_FLAG = 1 << 7; // zero flag
constexpr byte N_FLAG = 1 << 6; // subtraction flag
constexpr byte H_FLAG = 1 << 5; // half-carry flag
constexpr byte C_FLAG = 1 << 4; // carry flag

class GBCPU {
public:
	// Memory connected to CPU
	GBMemory* mem;

	// Current OPCode being processed
	int OPCode = 0;

	// Flag to be set if the last processed OPCode was CB (the prefix code)
	bool nextInstructionPrefixed = false;

	// To be used by prefixed opcodes to have their implementation split over multiple cycles/steps
	int OPCodeStep = 0;

	// Temp variables to store byte/address between OPCode steps
	byte tempByte1 = 0;
	byte tempByte2 = 0;
	address tempAddress = 0;

	byte* tempBytePtr{ nullptr };
	byte tempByte{ 0 };

	// Flag set when HALT OPCode is processed. Unset when an interrupt is pending
	bool isHalted = 0;

	// Interrupt Master Enable (IME) Flag
	bool IME = 0;

	// IME should be set one instruction after EI is called
	int instructionsBeforeIMESet = 0;

	// 8 8-bit registers (Initial values given by CGB Boot ROM)
	
	// A and F form a pair
	byte A = 0x01; // Accumulator
	byte F = Z_FLAG | H_FLAG | C_FLAG; // Flags

	// B and C form a pair
	byte B = 0;
	byte C = 0x13;

	// D and E form a pair
	byte D = 0;
	byte E = 0xD8;

	// H and L form a pair
	byte H = 0x01;
	byte L = 0x4D;

	// 2 16-bit registers

	address SP = 0xFFFE; // Stack Pointer

	address PC = 0x0100; // Program Counter

	// Store how many CPU cycles should pass before next instruction is called
	short cyclesRemaining = 0;

	// Creates new CPU linked to the given memory
	GBCPU(GBMemory* memory) :mem{ memory } {};

	// Resets the CPU and all its registers to their default state
	void reset();

	// Runs one CPU cycle
	void update();

	// Process OPCode obtained from memory via PC
	// Also updates cyclesRemaining with expected number of cycles to run specific OPCode
	void processUnprefixedOPCode();

	void processPrefixedOPCode(); // Process codes which were preceded by the CB OPCode

	// Push the PC onto the stack then sets the PC to the given address. If the given condition is met
	void conditionalCall(address addr, bool condition);

	// Rotates the bits of an 8 bit register to the left not passing through the carry
	void RLC(byte& reg);

	// Rotates the bits of an 8 bit register to the right not passing through the carry
	void RRC(byte& reg);

	// Rotates the bits of an 8 bit register to the left passing through the carry
	void RL(byte& reg);

	// Rotates the bits of an 8 bit register to the right passing through the carry
	void RR(byte& reg);

	// Shift the bits of an 8 bit register to the left (least sig. bit filled with 0)
	void SLA(byte& reg);

	// Shift the bits of an 8 bit register to the right (most sig. bit unchanged)
	void SRA(byte& reg);

	// Shift the bits of an 8 bit register to the right (most sig. bit filled with 0)
	void SRL(byte& reg);

	// Swaps the 4 most sig. bits with the 4 least sig bits of the given register
	void swap(byte& reg);

	// Sets the zero flag to the compliment of the given bit in the given register (Also sets half carry flag to 1, and N flag to 0)
	void testBit(byte& reg, int bitNum);

	// Sets the given bit of the given register to the given value
	void setBit(byte& reg, int bitNum, bool bitValue);

	// Declare functions for all OPCodes (Prefixed and Unprefixed)
	            void x01(); void x02(); void x03(); void x04(); void x05(); void x06(); void x07(); void x08(); void x09(); void x0A(); void x0B(); void x0C(); void x0D(); void x0E(); void x0F();
	void x10(); void x11(); void x12(); void x13(); void x14(); void x15(); void x16(); void x17(); void x18(); void x19(); void x1A(); void x1B(); void x1C(); void x1D(); void x1E(); void x1F();
	void x20(); void x21(); void x22(); void x23(); void x24(); void x25(); void x26(); void x27(); void x28(); void x29(); void x2A(); void x2B(); void x2C(); void x2D(); void x2E(); void x2F();
	void x30(); void x31(); void x32(); void x33(); void x34(); void x35(); void x36(); void x37(); void x38(); void x39(); void x3A(); void x3B(); void x3C(); void x3D(); void x3E(); void x3F();
	void x40(); void x41(); void x42(); void x43(); void x44(); void x45(); void x46(); void x47(); void x48(); void x49(); void x4A(); void x4B(); void x4C(); void x4D(); void x4E(); void x4F();
	void x50(); void x51(); void x52(); void x53(); void x54(); void x55(); void x56(); void x57(); void x58(); void x59(); void x5A(); void x5B(); void x5C(); void x5D(); void x5E(); void x5F();
	void x60(); void x61(); void x62(); void x63(); void x64(); void x65(); void x66(); void x67(); void x68(); void x69(); void x6A(); void x6B(); void x6C(); void x6D(); void x6E(); void x6F();
	void x70(); void x71(); void x72(); void x73(); void x74(); void x75(); void x76(); void x77(); void x78(); void x79(); void x7A(); void x7B(); void x7C(); void x7D(); void x7E(); void x7F();
	void x80(); void x81(); void x82(); void x83(); void x84(); void x85(); void x86(); void x87(); void x88(); void x89(); void x8A(); void x8B(); void x8C(); void x8D(); void x8E(); void x8F();
	void x90(); void x91(); void x92(); void x93(); void x94(); void x95(); void x96(); void x97(); void x98(); void x99(); void x9A(); void x9B(); void x9C(); void x9D(); void x9E(); void x9F();
	void xA0(); void xA1(); void xA2(); void xA3(); void xA4(); void xA5(); void xA6(); void xA7(); void xA8(); void xA9(); void xAA(); void xAB(); void xAC(); void xAD(); void xAE(); void xAF();
	void xB0(); void xB1(); void xB2(); void xB3(); void xB4(); void xB5(); void xB6(); void xB7(); void xB8(); void xB9(); void xBA(); void xBB(); void xBC(); void xBD(); void xBE(); void xBF();
	void xC0(); void xC1(); void xC2(); void xC3(); void xC4(); void xC5(); void xC6(); void xC7(); void xC8(); void xC9(); void xCA(); void xCB(); void xCC(); void xCD(); void xCE(); void xCF();
	void xD0(); void xD1(); void xD2();             void xD4(); void xD5(); void xD6(); void xD7(); void xD8(); void xD9(); void xDA();             void xDC();             void xDE(); void xDF();
	void xE0(); void xE1(); void xE2();                         void xE5(); void xE6(); void xE7(); void xE8(); void xE9(); void xEA();                                     void xEE(); void xEF();
	void xF0(); void xF1(); void xF2(); void xF3();             void xF5(); void xF6(); void xF7(); void xF8(); void xF9(); void xFA(); void xFB();                         void xFE(); void xFF();
};