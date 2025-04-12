#include "CPU.h"

void GBCPU::processOPCodeSecondStep() {
	// Gather individual flags from F register
	bool zeroFlag = F & Z_FLAG;
	bool carryFlag = F & C_FLAG;

	// Gather 16 bit combined registers
	address BC = (B << 8) + C;
	address DE = (D << 8) + E;
	address HL = (H << 8) + L;

	switch (OPCode) {
	case 1:
		loadReg8(C);
		OPCodeStep = 3;
		--cyclesRemaining;
		break;
	case 10:
		copyReg8(A, mem->read(BC));
		break;
	case 17:
		loadReg8(E);
		OPCodeStep = 3;
		--cyclesRemaining;
		break;
	case 26:
		copyReg8(A, mem->read(DE));
		break;
	case 33:
		loadReg8(L);
		OPCodeStep = 3;
		--cyclesRemaining;
		break;
	case 42:
		copyReg8(A, mem->read(HL));
		incReg16(H, L);
		--cyclesRemaining;
		break;
	case 52:
		tempByte = mem->read(HL);
		incReg8(tempByte);
		mem->write(HL, tempByte);
		++cyclesRemaining;
		break;
	case 53:
		tempByte = mem->read(HL);
		decReg8(tempByte);
		mem->write(HL, tempByte);
		++cyclesRemaining;
		break;
	case 54:
		loadReg8(tempByte);
		mem->write(HL, tempByte);
		break;
	case 58:
		copyReg8(A, mem->read(HL));
		decReg16(H, L);
		--cyclesRemaining;
		break;
	case 70:
		copyReg8(B, mem->read(HL));
		break;
	case 78:
		copyReg8(C, mem->read(HL));
		break;
	case 86:
		copyReg8(D, mem->read(HL));
		break;
	case 94:
		copyReg8(E, mem->read(HL));
		break;
	case 102:
		copyReg8(H, mem->read(HL));
		break;
	case 110:
		copyReg8(L, mem->read(HL));
		break;
	case 112:
		mem->write(HL, B);
		++cyclesRemaining;
		break;
	case 113:
		mem->write(HL, C);
		++cyclesRemaining;
		break;
	case 114:
		mem->write(HL, D);
		++cyclesRemaining;
		break;
	case 115:
		mem->write(HL, E);
		++cyclesRemaining;
		break;
	case 116:
		mem->write(HL, H);
		++cyclesRemaining;
		break;
	case 117:
		mem->write(HL, L);
		++cyclesRemaining;
		break;
	case 119:
		mem->write(HL, A);
		++cyclesRemaining;
		break;
	case 126:
		copyReg8(A, mem->read(HL));
		break;
	case 224:
		mem->write(0xFF00 + tempByte, A);
		cyclesRemaining += 2;
		break;
	case 232:
		addToSP();
		break;
	case 234:
		mem->write(tempAddress, A);
		cyclesRemaining += 2;
		break;
	case 240:
		copyReg8(A, mem->read(0xFF00 + tempByte));
		++cyclesRemaining;
		break;
	case 250:
		copyReg8(A, mem->read(tempAddress));
		++cyclesRemaining;
		break;
	}

	OPCodeStep -= 1;
}

void GBCPU::processOPCodeThirdStep() {
	// Gather individual flags from F register
	bool zeroFlag = F & Z_FLAG;
	bool carryFlag = F & C_FLAG;

	// Gather 16 bit combined registers
	address BC = (B << 8) + C;
	address DE = (D << 8) + E;
	address HL = (H << 8) + L;

	switch (OPCode) {
	case 1:
		loadReg8(B);
		--cyclesRemaining;
		break;
	case 17:
		loadReg8(D);
		--cyclesRemaining;
		break;
	case 33:
		loadReg8(H);
		--cyclesRemaining;
		break;
	}

	OPCodeStep = 0;
}