#include "CPU.h"

void GBCPU::processLaterStep() {
	// Gather individual flags from F register
	bool zeroFlag = F & Z_FLAG;
	bool carryFlag = F & C_FLAG;

	switch (OPCode) {
	case 52:
		incReg8(getHLMemory());
		break;
	case 53:
		break;
	case 54:
		loadReg8(*tempBytePtr);
		break;
	case 224:
		copyReg8(getHighMemory(tempByte), A);
		break;
	case 234:
		copyReg8(mem->read(tempAddress), A);
		++cyclesRemaining;
		break;
	case 240:
		copyReg8(A, getHighMemory(tempByte));
		break;
	case 250:
		copyReg8(A, mem->read(tempAddress));
		++cyclesRemaining;
		break;
	}

	OPCodeStep = 0;
}