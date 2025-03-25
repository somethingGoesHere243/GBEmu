#pragma once
#include "../Memory.h"

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

	// Flag to be set if the last processed OPCode was CB (the prefix code)
	bool nextInstructionPrefixed = false;

	// Interrupt Master Enable (IME) Flag
	bool IME = 0;

	// IME should be set one instruction after EI is called
	bool needToSetIME = 0;

	// 8 8-bit registers (Initial values given by CGB Boot ROM)
	
	// A and F form a pair
	byte A = 17; // Accumulator
	byte F = Z_FLAG; // Flags

	// B and C form a pair
	byte B = 0;
	byte C = 0;

	// D and E form a pair
	byte D = 255;
	byte E = 86;

	// H and L form a pair
	byte H = 0;
	byte L = 13;

	// 2 16-bit registers

	address SP = 65534; // Stack Pointer

	address PC = 0x100; // Program Counter

	// Store how many CPU cycles should pass before next instruction is called
	short cyclesRemaining = 0;

	// Creates new CPU linked to the given memory
	GBCPU(GBMemory* memory) :mem{ memory } {};

	// Runs one CPU cycle
	void update();

	// Process OPCode obtained from memory via PC
	// Also updates cyclesRemaining with expected number of cycles to run specific OPCode
	void processUnprefixedOPCode(byte OPCode);

	void processPrefixedOPCode(byte OPCode); // Process codes which were preceded by the CB OPCode

	// Enables interrupt flag upon next instruction call
	void EI();

	// Disables interrupt flag
	void DI();

	// Increments the 16 bit register formed from combining reg1 and reg2
	void incReg16(byte& reg1, byte& reg2);

	// Decrements the 16 bit register formed from combining reg1 and reg2
	void decReg16(byte& reg1, byte& reg2);

	// Increment an 8 bit register (sets flags as needed)
	void incReg8(byte& reg);

	// Decrement an 8 bit register (no flags changed)
	void decReg8(byte& reg);

	// Retrieves data from the memory address given by the BC (combined) register
	byte& getBCMemory();

	// Retrieves data from the memory address given by the DE (combined) register
	byte& getDEMemory();

	// Retrieves data from the memory address given by the HL (combined) register
	byte& getHLMemory();

	// Retrieves data from the memory address given by $FF00 + reg
	byte& getHighMemory(byte& reg);

	// Copy data between 2 8-bit registers
	void copyReg8(byte& destReg, byte& SourceReg); 

	// Load an 8 bit register with 8 bit value pointed to by the PC
	void loadReg8(byte& destReg);

	// Load a 16 bit register with 2 consecutive 8 bit value pointed to by the PC
	void loadReg16(address& destReg);

	// Adds the given 16 bit sourceReg to the HL register
	void addToHL(address& sourceReg);

	// Adds the 8 bit value pointed to by the PC to the SP
	void addToSP();

	// Copys the value of SP + e8 into HL register (e8 is value pointed to by the PC)
	void loadHLWithEditedSP();

	// Performs a relative jump if the given condition is met
	void relJump(bool condition);

	// Jump to the given address if the given condition is met
	void jump(address dest, bool condition);

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

	// Performs the decimal adjust of the accumulator (A register)
	void DAA();

	// Sets the value of A to its bitwise complement
	void CPL();

	// Sets the carry flag to 1
	void setCarry();

	// Sets the carry flag to its compliment
	void invertCarry();

	// Adds the value in the given 8 bit register to the accumulator (A register)
	void addToA(byte& reg);

	// Adds the value in the given 8 bit register plus the carry flag to the accumulator (A register)
	void addToAWithCarry(byte& reg);

	// Subtracts the value in the given 8 bit register from the accumulator (A register)
	void subtractFromA(byte& reg);

	// Subtracts (the value in the given 8 bit register plus the carry flag) from the accumulator (A register)
	void subtractFromAWithCarry(byte& reg);

	// Set A to the bitwise AND of itself with a given 8 bit register
	void andA(byte& reg);

	// Set A to the bitwise XOR of itself with a given 8 bit register
	void xorA(byte& reg);

	// Set A to the bitwise OR of itself with a given 8 bit register
	void orA(byte& reg);

	// Compares the value of A with the value of another 8 bit register setting flags accordingly
	void compareA(byte& reg);

	// Fills a given 2 8-bit registers with 2 values popped from the stack (note: reg2 is filled first)
	void fillFromStack(byte& reg1, byte& reg2);

	// Push 2 given 8-bit registers onto the stack (note: reg1 is pushed first)
	void pushToStack(byte& reg1, byte& reg2);

	// Push the PC onto the stack then sets the PC to the given address. If the given condition is met
	void conditionalCall(address addr, bool condition);

	// Fills the PC using 2 8-bit registers popped from the stack (first popped register makes up least sig. 8 bits of PC)
	void ret();

	// Performs the above ret operation if a given condition is met
	void conditionalRet(bool condition);

	// Sets the zero flag to the compliment of the given bit in the given register (Also sets half carry flag to 1, and N flag to 0)
	void testBit(byte& reg, int bitNum);

	// Sets the given bit of the given register to the given value
	void setBit(byte& reg, int bitNum, bool bitValue);
};