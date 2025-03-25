#include "CPU.h"

#include <iostream>

void GBCPU::EI() { 
	needToSetIME = 1;
	++cyclesRemaining;
}

void GBCPU::DI() { 
	IME = 0;
	++cyclesRemaining;
}

void GBCPU::incReg16(byte& reg1, byte& reg2) {
	++reg2;
	// Check for carry into first register
	if (reg2 == 0) {
		++reg1;
	}
}

void GBCPU::decReg16(byte& reg1, byte& reg2) {
	// Check for carry into first register
	if (reg2 == 0) {
		--reg1;
	}
	--reg2;
}

void GBCPU::decReg8(byte& reg) {
	// Check half carry flag (are 4 least sig. bits 0's)
	bool halfCarryFlag{ !(reg & 1) && !(reg & 2) && !(reg & 4) && !(reg & 8) };

	--reg;
	// Check zero flag
	bool zeroFlag{ reg == 0 };
	// Negative flag set to 0
	bool negFlag = 1;

	// Update flag (F) register (note we want carry flag unchanged)
	F = (F & C_FLAG) + halfCarryFlag * H_FLAG + zeroFlag * Z_FLAG + negFlag * N_FLAG;

	++cyclesRemaining;
}

void GBCPU::incReg8(byte& reg) {
	// Check half carry flag (are 4 least sig. bits 1's)
	bool halfCarryFlag{ (reg & 1) && (reg & 2) && (reg & 4) && (reg & 8) };

	++reg;
	// Check zero flag
	bool zeroFlag{ reg == 0 };
	// Negative flag set to 0
	bool negFlag = 0;

	// Update flag (F) register (note we want carry flag unchanged)
	F = (F & C_FLAG) + halfCarryFlag * H_FLAG + zeroFlag * Z_FLAG + negFlag * N_FLAG;

	++cyclesRemaining;
}

byte& GBCPU::getBCMemory() {
	// Combine B and C register values
	address BC = (B << 8) + C;
	++cyclesRemaining;

	return mem->read(BC);
}

byte& GBCPU::getDEMemory() {
	// Combine H and L register values
	address DE = (D << 8) + E;
	++cyclesRemaining;

	return mem->read(DE);
}

byte& GBCPU::getHLMemory() {
	// Combine H and L register values
	address HL = (H << 8) + L;
	++cyclesRemaining;

	return mem->read(HL);
}

byte& GBCPU::getHighMemory(byte& reg) {
	// Most significant bits are $FF00
	constexpr address FF = 65280;
	address target = FF + reg;

	++cyclesRemaining;

	return mem->read(target);
}

void GBCPU::copyReg8(byte& destReg, byte& sourceReg) {
	destReg = sourceReg;
	++cyclesRemaining;
}

void GBCPU::loadReg8(byte& destReg) {
	destReg = mem->read(PC);

	// Increment PC and increase cycle count
	++PC;
	cyclesRemaining += 2;
}

void GBCPU::loadReg16(address& destReg) {
	// Retrieve first value from the program counter
	byte val1 = mem->read(PC);
	++PC;

	// Retrieve second value from program counter
	byte val2 = mem->read(PC);
	++PC;

	// Combine 2 values into destReg
	destReg = val1 + (val2 << 8);

	cyclesRemaining += 3;
}

void GBCPU::addToHL(address& sourceReg) {
	address HL = (H << 8) + L;

	bool negativeFlag = 0;
	bool halfCarryFlag = 0;
	bool carryFlag = 0;
	
	// Need to add bitwise to set flags
	bool carry{ 0 };
	address res{ 0 };
	for (int i = 0; i < 16; ++i) {
		bool HLBit = (HL >> i) & 1;
		bool sourceBit = (sourceReg >> i) & 1;

		bool HLPlusSource = (HLBit ^ sourceBit);
		bool HLPlusSourceCarry = HLBit && sourceBit;

		res += (HLPlusSource ^ carry) * (1 << i);
		carry = HLPlusSourceCarry || (HLPlusSource && carry);

		if (carry && (i == 11)) {
			halfCarryFlag = 1;
		}
		else if (carry && (i == 15)) {
			carryFlag = 1;
		}
	}

	L = (byte)(res);
	H = (byte)(res >> 8);

	F = (F & Z_FLAG) + (negativeFlag * N_FLAG) + (halfCarryFlag * H_FLAG) + (carryFlag * C_FLAG);

	cyclesRemaining += 2;
}

void GBCPU::addToSP() {
	int change = mem->read(PC);
	++PC;

	// Change needs to be a signed value (i.e its negative if most sig. bit is 1)
	if (change & 128) {
		change -= 256;
	}

	// Check for overflow from bit 3
	bool halfCarryFlag = ((SP & 15) + (change & 15)) > 15;

	byte oldSPValue = SP;
	SP += change;

	// Check for overflow from bit 7
	bool carryFlag = ((byte)oldSPValue > (byte)SP);

	// Set flags (Z & N flags set to 0)
	F = carryFlag * C_FLAG + halfCarryFlag * H_FLAG;

	cyclesRemaining += 4;
}

void GBCPU::loadHLWithEditedSP() {
	int change = mem->read(PC);
	++PC;

	// Change needs to be a signed value (i.e its negative if most sig. bit is 1)
	if (change & 128) {
		change -= 256;
	}

	// Check for overflow from bit 3
	bool halfCarryFlag = ((SP & 15) + (change & 15)) > 15;

	address editedSPValue = SP + change;

	// Check for overflow from bit 7
	bool carryFlag = ((byte)SP > (byte)editedSPValue);

	// Set flags (Z & N flags set to 0)
	F = carryFlag * C_FLAG + halfCarryFlag * H_FLAG;

	// Write new SP value into HL register
	H = editedSPValue >> 8;
	L = editedSPValue;

	cyclesRemaining += 3;
}

void GBCPU::relJump(bool condition) {
	// Terminate early if flag not set
	if (!condition) {
		cyclesRemaining += 2;
		++PC;
		return;
	}
	// Get offset which needs to be applied to PC
	byte offset = mem->read(PC);
	PC++;

	// offset should now be treated as a signed integer
	// If most significant bit is set offset is negative
	if (offset & (1 << 7)) {
		// offset is negative
		PC += (offset - 256);
	}
	else {
		// offset is positive
		PC += offset;
	}
	cyclesRemaining += 3;
}

void GBCPU::jump(address dest, bool condition) {
	// Terminate early if flag not set
	if (!condition) {
		return;
	}
	PC = dest;
	++cyclesRemaining;
}

void GBCPU::RLC(byte& reg) {
	// Set zero flag if register contains 0
	bool zeroFlag = (reg == 0);

	// Carry flag is set to most sig byte of reg
	bool carryFlag = (reg >> 7) & 1;

	// Rotate bits of reg
	reg = 2 * reg + carryFlag;

	// Update F register ( Z, N, H Flags all set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;

	++cyclesRemaining;
}

void GBCPU::RRC(byte& reg) {
	// Set zero flag if register contains 0
	bool zeroFlag = (reg == 0);

	// Carry flag is set to least sig byte of reg
	bool carryFlag = reg & 1;

	// Rotate bits of reg
	reg = (carryFlag * (1 << 7)) + ((reg >> 1) & 127);

	// Update F register ( N, H Flags both set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;

	++cyclesRemaining;
}

void GBCPU::RL(byte& reg) {
	// Carry flag is set to most sig byte of reg
	bool carryFlag = (reg >> 7) & 1;

	// Get current carry flag from F register
	bool currCarry = F & C_FLAG;

	// Rotate bits of reg
	reg = 2 * reg + currCarry;

	// Set zero flag if register contains 0
	bool zeroFlag = (reg == 0);

	// Update F register ( Z, N, H Flags all set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;

	++cyclesRemaining;
}

void GBCPU::RR(byte& reg) {
	// Carry flag is set to least sig byte of reg
	bool carryFlag = reg & 1;

	// Get current carry flag from F register
	bool currCarry = F & C_FLAG;

	// Rotate bits of reg
	reg = (currCarry * (1 << 7)) + ((reg >> 1) & 127);

	// Set zero flag if register contains 0
	bool zeroFlag = (reg == 0);

	// Update F register ( N, H Flags both set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;

	++cyclesRemaining;
}

void GBCPU::SLA(byte& reg) {
	// Most significant bit cycled into carry flag
	bool carryFlag = reg & 128;
	reg = (reg << 1);

	// Set zero flag
	bool zeroFlag = (reg == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
	++cyclesRemaining;
}

void GBCPU::SRA(byte& reg) {
	// Least significant bit cycled into carry flag
	bool carryFlag = reg & 1;

	// Most significant bit unchanged
	byte mostSigBit = reg & 128;
	reg = mostSigBit + ((reg >> 1) & 127);

	// Set zero flag
	bool zeroFlag = (reg == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
	++cyclesRemaining;
}

void GBCPU::SRL(byte& reg) {
	// Least significant bit cycled into carry flag
	bool carryFlag = reg & 1;

	// Shift other bits
	reg = ((reg >> 1) & 127);

	// Set zero flag
	bool zeroFlag = (reg == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG;
	++cyclesRemaining;
}

void GBCPU::swap(byte& reg) {
	byte fourLeastSigBits = reg & 15;
	byte fourMostSigBits = (reg >> 4) & 15;

	reg = (fourLeastSigBits << 4) + fourMostSigBits;

	bool zeroFlag = (reg == 0);
	// All other flags set to 0
	F = zeroFlag * Z_FLAG;

	++cyclesRemaining;
}

void GBCPU::DAA() {
	byte adjustment = 0;
	bool carryFlag = F & C_FLAG;
	// Different adjustments used depending on which flags are set
	if (F & N_FLAG) {
		if (F & H_FLAG) {
			adjustment += 6;
		}
		if (carryFlag) {
			adjustment += 96;
		}
		A -= adjustment;
	}
	else {
		if ((F & H_FLAG) || ((A & 15) > 9)) {
			adjustment += 6;
		}
		if (carryFlag || (A > 153)) {
			adjustment += 96;

			// Set carry flag in this case
			carryFlag = 1;
		}
		A += adjustment;
	}
	bool zeroFlag = (A == 0);
	// Update flags (H flag set to 0, N flag unchanged)
	F = (F & N_FLAG) + zeroFlag * Z_FLAG + carryFlag * C_FLAG;

	++cyclesRemaining;
}

void GBCPU::CPL() {
	A = ~A;

	// Set H and N flags (Z and C unaffected)
	F = (F & (Z_FLAG | C_FLAG)) + H_FLAG + N_FLAG;

	++cyclesRemaining;
}

void GBCPU::setCarry() {
	// Z unchanged, N and H set to 0
	F = (F & Z_FLAG) + C_FLAG;

	++cyclesRemaining;
}

void GBCPU::invertCarry() {

	bool currentCarry = F & C_FLAG;

	// Z unchanged, N and H set to 0
	F = (F & Z_FLAG) + (!currentCarry) * C_FLAG;

	++cyclesRemaining;
}

void GBCPU::addToA(byte& reg) {
	// Check for overflow from bit 3
	bool halfCarryFlag = ((A & 15) + (reg & 15)) > 15;

	byte oldAValue = A;
	A += reg;

	// Check for overflow from bit 7
	bool carryFlag = (oldAValue > A);

	bool zeroFlag = (A == 0);

	// Set flags (N flag set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;

	++cyclesRemaining;
}

void GBCPU::addToAWithCarry(byte& reg) {
	// Retrieve current carry flag
	bool carryFlag = F & C_FLAG;

	// Check for overflow from bit 3
	bool halfCarryFlag = ((A & 15) + (reg & 15)) + carryFlag > 15;

	byte oldAValue = A;
	int increase = reg + carryFlag;
	A += increase;

	// Check for overflow from bit 7
	carryFlag = (oldAValue > A) || (increase == 256);

	bool zeroFlag = (A == 0);

	// Set flags (N flag set to 0)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;

	++cyclesRemaining;
}

void GBCPU::subtractFromA(byte& reg) {
	// Check if need to borrow from bit 4
	bool halfCarryFlag = (reg & 15) > (A & 15);

	byte oldAValue = A;
	A -= reg;

	// Check if need to borrow from bit 8
	bool carryFlag = (oldAValue < A);

	bool zeroFlag = (A == 0);

	// Set flags (N flag set to 1)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG + N_FLAG;

	++cyclesRemaining;
}

void GBCPU::subtractFromAWithCarry(byte& reg) {
	// Retrieve current carry flag
	bool carryFlag = F & C_FLAG;

	// Check if need to borrow from bit 4
	bool halfCarryFlag = (reg & 15) + carryFlag > (A & 15);

	byte oldAValue = A;
	int decrease = reg + carryFlag;
	A -= decrease;

	// Check if need to borrow from bit 8
	carryFlag = (oldAValue < A) || (decrease == 256);

	bool zeroFlag = (A == 0);

	// Set flags (N flag set to 1)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG + N_FLAG;

	++cyclesRemaining;
}

void GBCPU::andA(byte& reg) {
	A = A & reg;

	bool zeroFlag = (A == 0);
	// N and C flags set to 0, H flag set to 1
	F = zeroFlag * Z_FLAG + H_FLAG;

	++cyclesRemaining;
}

void GBCPU::xorA(byte& reg) {
	A = A ^ reg;

	bool zeroFlag = (A == 0);
	// N, H and C flags set to 0
	F = zeroFlag * Z_FLAG;

	++cyclesRemaining;
}

void GBCPU::orA(byte& reg) {
	A = A | reg;

	bool zeroFlag = (A == 0);
	// N, H and C flags set to 0
	F = zeroFlag * Z_FLAG;

	++cyclesRemaining;
}

void GBCPU::compareA(byte& reg) {
	// Check if needed to borrow from bit 4
	bool halfCarryFlag = (reg & 15) > (A & 15);

	// Check if needed to borrow from bit 8
	bool carryFlag = (reg > A);

	bool zeroFlag = (reg == A);

	// Set flags (N flag set to 1)
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG + N_FLAG;

	++cyclesRemaining;
}

void GBCPU::fillFromStack(byte& reg1, byte& reg2) {
	reg2 = mem->read(SP);
	++SP;
	reg1 = mem->read(SP);
	++SP;

	cyclesRemaining += 3;
}

void GBCPU::pushToStack(byte& reg1, byte& reg2) {
	// Decrement stack pointer before pushing new register into its new location
	--SP;
	mem->write(SP, reg1);

	--SP;
	mem->write(SP, reg2);

	cyclesRemaining += 4;
}

void GBCPU::conditionalCall(address addr, bool condition) {
	// Return early if condition not met
	if (!condition) {
		return;
	}
	// Split PC into 2 bytes to be pushed onto stack
	byte mostSigBitsPC = (PC >> 8);
	byte leastSigBitsPC = PC;

	pushToStack(mostSigBitsPC, leastSigBitsPC);
	
	PC = addr;
	cyclesRemaining -= 1;
}

void GBCPU::ret() {
	// Get least sig 8 bits of PC from the stack
	byte leastSigBits = mem->read(SP);
	++SP;

	// Combine with next byte from stack to get new PC value
	PC = (mem->read(SP) << 8) + leastSigBits;
	++SP;

	cyclesRemaining += 4;
}

void GBCPU::conditionalRet(bool condition) {
	if (condition) {
		ret();
	}
	else {
		++cyclesRemaining;
	}
	++cyclesRemaining;
}

void GBCPU::testBit(byte& reg, int bitNum) {
	bool zeroFlag = !(reg & (1 << bitNum));

	F = (F & C_FLAG) + zeroFlag * Z_FLAG + H_FLAG;

	++cyclesRemaining;
}

void GBCPU::setBit(byte& reg, int bitNum, bool bitValue) {
	byte bitToRemove = reg & (1 << bitNum);
	byte bitToAdd = bitValue * (1 << bitNum);

	reg = reg - bitToRemove + bitToAdd;

	++cyclesRemaining;
}

void GBCPU::update() {
	// Check if enough cycles have passes to begin next instruction
	if (cyclesRemaining == 0) {
		// Check if IME flag needs to be set
		if (needToSetIME) {
			IME = 1;
			needToSetIME = 0;
		}

		byte opCode = mem->read(PC);

		// Check if need to process a prefixed OPCode
		if (nextInstructionPrefixed) {
			nextInstructionPrefixed = false;
			processPrefixedOPCode(opCode);
		}
		else {
			// Process an unprefixed OPCode
			processUnprefixedOPCode(opCode);
		}
	}

	// One cycle passes on each update
	--cyclesRemaining;
}
