#include "CPU.h"

void GBCPU::processUnprefixedOPCode(byte OPCode) {
	// Increment Program Counter
	++PC;

	// Gather individual flags from F register
	bool zeroFlag = F & Z_FLAG;
	bool carryFlag = F & C_FLAG;

	// Gather 16 bit combined registers
	address BC = (B << 8) + C;
	address DE = (D << 8) + E;
	address HL = (H << 8) + L;

	// Temporary address variable
	address addressToWriteTo{ 0 };

	switch (OPCode) {
	case 0:
		// No operation
		++cyclesRemaining;
		break;
	case 1:
		loadReg8(C);
		loadReg8(B);
		--cyclesRemaining;
		break;
	case 2:
		copyReg8(getBCMemory(), A);
		break;
	case 3:
		incReg16(B, C);
		cyclesRemaining += 2;
		break;
	case 4:
		incReg8(B);
		break;
	case 5:
		decReg8(B);
		break;
	case 6:
		loadReg8(B);
		break;
	case 7:
		RLC(A);
		// Set zero flag to 0
		F = F & (N_FLAG | H_FLAG | C_FLAG); 
		break;
	case 8:
		loadReg16(addressToWriteTo);

		// Write 8 least significant bits of SP to given address
		mem->write(addressToWriteTo, (byte)SP);
		// Write 8 most significant bits of SP to next consecutive address
		mem->write(addressToWriteTo + 1, (byte)(SP >> 8));
		cyclesRemaining += 2;

		break;
	case 9:
		addToHL(BC);
		break;
	case 10:
		copyReg8(A, getBCMemory());
		break;
	case 11:
		decReg16(B, C);
		cyclesRemaining += 2;
		break;
	case 12:
		incReg8(C);
		break;
	case 13:
		decReg8(C);
		break;
	case 14:
		loadReg8(C);
		break;
	case 15:
		RRC(A);
		// Set zero flag to 0
		F = F & (N_FLAG | H_FLAG | C_FLAG);
		break;
	case 16:
		// TODO: STOP OPCode
		cyclesRemaining += 3;
		break;
	case 17:
		loadReg8(E);
		loadReg8(D);
		--cyclesRemaining;
		break;
	case 18:
		copyReg8(getDEMemory(), A);
		break;
	case 19:
		incReg16(D, E);
		cyclesRemaining += 2;
		break;
	case 20:
		incReg8(D);
		break;
	case 21:
		decReg8(D);
		break;
	case 22:
		loadReg8(D);
		break;
	case 23:
		RL(A);
		// Set zero flag to 0
		F = F & (N_FLAG | H_FLAG | C_FLAG);
		break;
	case 24:
		relJump(true);
		break;
	case 25:
		addToHL(DE);
		break;
	case 26:
		copyReg8(A, getDEMemory());
		break;
	case 27:
		decReg16(D, E);
		cyclesRemaining += 2;
		break;
	case 28:
		incReg8(E);
		break;
	case 29:
		decReg8(E);
		break;
	case 30:
		loadReg8(E);
		break;
	case 31:
		RR(A);
		// Set zero flag to 0
		F = F & (N_FLAG | H_FLAG | C_FLAG);
		break;
	case 32:
		relJump(!zeroFlag);
		break;
	case 33:
		loadReg8(L);
		loadReg8(H);
		--cyclesRemaining;
		break;
	case 34:
		copyReg8(getHLMemory(), A);
		incReg16(H, L);
		break;
	case 35:
		incReg16(H, L);
		cyclesRemaining += 2;
		break;
	case 36:
		incReg8(H);
		break;
	case 37:
		decReg8(H);
		break;
	case 38:
		loadReg8(H);
		break;
	case 39:
		DAA();
		break;
	case 40:
		relJump(zeroFlag);
		break;
	case 41:
		addToHL(HL);
		break;
	case 42:
		copyReg8(A, getHLMemory());
		incReg16(H, L);
		break;
	case 43:
		decReg16(H, L);
		cyclesRemaining += 2;
		break;
	case 44:
		incReg8(L);
		break;
	case 45:
		decReg8(L);
		break;
	case 46:
		loadReg8(L);
		break;
	case 47:
		CPL();
		break;
	case 48:
		relJump(!carryFlag);
		break;
	case 49:
		loadReg16(SP);
		break;
	case 50:
		copyReg8(getHLMemory(), A);
		decReg16(H, L);
		break;
	case 51:
		++SP;
		cyclesRemaining += 2;
		break;
	case 52:
		incReg8(getHLMemory());
		++cyclesRemaining;
		break;
	case 53:
		decReg8(getHLMemory());
		++cyclesRemaining;
		break;
	case 54:
		loadReg8(getHLMemory());
		break;
	case 55:
		setCarry();
		break;
	case 56:
		relJump(carryFlag);
		break;
	case 57:
		addToHL(SP);
		break;
	case 58:
		copyReg8(A, getHLMemory());
		decReg16(H, L);
		break;
	case 59:
		--SP;
		cyclesRemaining += 2;
		break;
	case 60:
		incReg8(A);
		break;
	case 61:
		decReg8(A);
		break;
	case 62:
		loadReg8(A);
		break;
	case 63:
		invertCarry();
		break;
	case 64:
		copyReg8(B, B);
		break;
	case 65:
		copyReg8(B, C);
		break;
	case 66:
		copyReg8(B, D);
		break;
	case 67:
		copyReg8(B, E);
		break;
	case 68:
		copyReg8(B, H);
		break;
	case 69:
		copyReg8(B, L);
		break;
	case 70:
		copyReg8(B, getHLMemory());
		break;
	case 71:
		copyReg8(B, A);
		break;
	case 72:
		copyReg8(C, B);
		break;
	case 73:
		copyReg8(C, C);
		break;
	case 74:
		copyReg8(C, D);
		break;
	case 75:
		copyReg8(C, E);
		break;
	case 76:
		copyReg8(C, H);
		break;
	case 77:
		copyReg8(C, L);
		break;
	case 78:
		copyReg8(C, getHLMemory());
		break;
	case 79:
		copyReg8(C, A);
		break;
	case 80:
		copyReg8(D, B);
		break;
	case 81:
		copyReg8(D, C);
		break;
	case 82:
		copyReg8(D, D);
		break;
	case 83:
		copyReg8(D, E);
		break;
	case 84:
		copyReg8(D, H);
		break;
	case 85:
		copyReg8(D, L);
		break;
	case 86:
		copyReg8(D, getHLMemory());
		break;
	case 87:
		copyReg8(D, A);
		break;
	case 88:
		copyReg8(E, B);
		break;
	case 89:
		copyReg8(E, C);
		break;
	case 90:
		copyReg8(E, D);
		break;
	case 91:
		copyReg8(E, E);
		break;
	case 92:
		copyReg8(E, H);
		break;
	case 93:
		copyReg8(E, L);
		break;
	case 94:
		copyReg8(E, getHLMemory());
		break;
	case 95:
		copyReg8(E, A);
		break;
	case 96:
		copyReg8(H, B);
		break;
	case 97:
		copyReg8(H, C);
		break;
	case 98:
		copyReg8(H, D);
		break;
	case 99:
		copyReg8(H, E);
		break;
	case 100:
		copyReg8(H, H);
		break;
	case 101:
		copyReg8(H, L);
		break;
	case 102:
		copyReg8(H, getHLMemory());
		break;
	case 103:
		copyReg8(H, A);
		break;
	case 104:
		copyReg8(L, B);
		break;
	case 105:
		copyReg8(L, C);
		break;
	case 106:
		copyReg8(L, D);
		break;
	case 107:
		copyReg8(L, E);
		break;
	case 108:
		copyReg8(L, H);
		break;
	case 109:
		copyReg8(L, L);
		break;
	case 110:
		copyReg8(L, getHLMemory());
		break;
	case 111:
		copyReg8(L, A);
		break;
	case 112:
		copyReg8(getHLMemory(), B);
		break;
	case 113:
		copyReg8(getHLMemory(), C);
		break;
	case 114:
		copyReg8(getHLMemory(), D);
		break;
	case 115:
		copyReg8(getHLMemory(), E);
		break;
	case 116:
		copyReg8(getHLMemory(), H);
		break;
	case 117:
		copyReg8(getHLMemory(), L);
		break;
	case 118:
		// TODO: HALT OPCode
		cyclesRemaining += 3;
		break;
	case 119:
		copyReg8(getHLMemory(), A);
		break;
	case 120:
		copyReg8(A, B);
		break;
	case 121:
		copyReg8(A, C);
		break;
	case 122:
		copyReg8(A, D);
		break;
	case 123:
		copyReg8(A, E);
		break;
	case 124:
		copyReg8(A, H);
		break;
	case 125:
		copyReg8(A, L);
		break;
	case 126:
		copyReg8(A, getHLMemory());
		break;
	case 127:
		copyReg8(A, A);
		break;
	case 128:
		addToA(B);
		break;
	case 129:
		addToA(C);
		break;
	case 130:
		addToA(D);
		break;
	case 131:
		addToA(E);
		break;
	case 132:
		addToA(H);
		break;
	case 133:
		addToA(L);
		break;
	case 134:
		addToA(getHLMemory());
		break;
	case 135:
		addToA(A);
		break;
	case 136:
		addToAWithCarry(B);
		break;
	case 137:
		addToAWithCarry(C);
		break;
	case 138:
		addToAWithCarry(D);
		break;
	case 139:
		addToAWithCarry(E);
		break;
	case 140:
		addToAWithCarry(H);
		break;
	case 141:
		addToAWithCarry(L);
		break;
	case 142:
		addToAWithCarry(getHLMemory());
		break;
	case 143:
		addToAWithCarry(A);
		break;
	case 144:
		subtractFromA(B);
		break;
	case 145:
		subtractFromA(C);
		break;
	case 146:
		subtractFromA(D);
		break;
	case 147:
		subtractFromA(E);
		break;
	case 148:
		subtractFromA(H);
		break;
	case 149:
		subtractFromA(L);
		break;
	case 150:
		subtractFromA(getHLMemory());
		break;
	case 151:
		subtractFromA(A);
		break;
	case 152:
		subtractFromAWithCarry(B);
		break;
	case 153:
		subtractFromAWithCarry(C);
		break;
	case 154:
		subtractFromAWithCarry(D);
		break;
	case 155:
		subtractFromAWithCarry(E);
		break;
	case 156:
		subtractFromAWithCarry(H);
		break;
	case 157:
		subtractFromAWithCarry(L);
		break;
	case 158:
		subtractFromAWithCarry(getHLMemory());
		break;
	case 159:
		subtractFromAWithCarry(A);
		break;
	case 160:
		andA(B);
		break;
	case 161:
		andA(C);
		break;
	case 162:
		andA(D);
		break;
	case 163:
		andA(E);
		break;
	case 164:
		andA(H);
		break;
	case 165:
		andA(L);
		break;
	case 166:
		andA(getHLMemory());
		break;
	case 167:
		andA(A);
		break;
	case 168:
		xorA(B);
		break;
	case 169:
		xorA(C);
		break;
	case 170:
		xorA(D);
		break;
	case 171:
		xorA(E);
		break;
	case 172:
		xorA(H);
		break;
	case 173:
		xorA(L);
		break;
	case 174:
		xorA(getHLMemory());
		break;
	case 175:
		xorA(A);
		break;
	case 176:
		orA(B);
		break;
	case 177:
		orA(C);
		break;
	case 178:
		orA(D);
		break;
	case 179:
		orA(E);
		break;
	case 180:
		orA(H);
		break;
	case 181:
		orA(L);
		break;
	case 182:
		orA(getHLMemory());
		break;
	case 183:
		orA(A);
		break;
	case 184:
		compareA(B);
		break;
	case 185:
		compareA(C);
		break;
	case 186:
		compareA(D);
		break;
	case 187:
		compareA(E);
		break;
	case 188:
		compareA(H);
		break;
	case 189:
		compareA(L);
		break;
	case 190:
		compareA(getHLMemory());
		break;
	case 191:
		compareA(A);
		break;
	case 192:
		conditionalRet(!zeroFlag);
		break;
	case 193:
		fillFromStack(B, C);
		break;
	case 194:
		loadReg16(addressToWriteTo);
		jump(addressToWriteTo, !zeroFlag);
		break;
	case 195:
		loadReg16(addressToWriteTo);
		jump(addressToWriteTo, 1);
		break;
	case 196:
		loadReg16(addressToWriteTo);
		conditionalCall(addressToWriteTo, !zeroFlag);
		break;
	case 197:
		pushToStack(B, C);
		break;
	case 198:
		addToA(mem->read(PC));
		++PC;
		++cyclesRemaining;
		break;
	case 199:
		conditionalCall(0, true);
		++cyclesRemaining;
		break;
	case 200:
		conditionalRet(zeroFlag);
		break;
	case 201:
		ret();
		break;
	case 202:
		loadReg16(addressToWriteTo);
		jump(addressToWriteTo, zeroFlag);
		break;
	case 203:
		nextInstructionPrefixed = true;
		++cyclesRemaining;
		break;
	case 204:
		loadReg16(addressToWriteTo);
		conditionalCall(addressToWriteTo, zeroFlag);
		break;
	case 205:
		loadReg16(addressToWriteTo);
		conditionalCall(addressToWriteTo, true);
		break;
	case 206:
		addToAWithCarry(mem->read(PC));
		++PC;
		++cyclesRemaining;
		break;
	case 207:
		conditionalCall(8, true);
		++cyclesRemaining;
		break;
	case 208:
		conditionalRet(!carryFlag);
		break;
	case 209:
		fillFromStack(D, E);
		break;
	case 210:
		loadReg16(addressToWriteTo);
		jump(addressToWriteTo, !carryFlag);
		break;
	case 212:
		loadReg16(addressToWriteTo);
		conditionalCall(addressToWriteTo, !carryFlag);
		break;
	case 213:
		pushToStack(D, E);
		break;
	case 214:
		subtractFromA(mem->read(PC));
		++PC;
		++cyclesRemaining;
		break;
	case 215:
		conditionalCall(16, true);
		++cyclesRemaining;
		break;
	case 216:
		conditionalRet(carryFlag);
		break;
	case 217:
		ret();
		IME = 1;
		break;
	case 218:
		loadReg16(addressToWriteTo);
		jump(addressToWriteTo, carryFlag);
		break;
	case 220:
		loadReg16(addressToWriteTo);
		conditionalCall(addressToWriteTo, carryFlag);
		break;
	case 222:
		subtractFromAWithCarry(mem->read(PC));
		++PC;
		++cyclesRemaining;
		break;
	case 223:
		conditionalCall(24, true);
		++cyclesRemaining;
		break;
	case 224:
		copyReg8(getHighMemory(mem->read(PC)), A);
		++PC;
		++cyclesRemaining;
		break;
	case 225:
		fillFromStack(H, L);
		break;
	case 226:
		copyReg8(getHighMemory(C), A);
		break;
	case 229:
		pushToStack(H, L);
		break;
	case 230:
		andA(mem->read(PC));
		++PC;
		++cyclesRemaining;
		break;
	case 231:
		conditionalCall(32, true);
		++cyclesRemaining;
		break;
	case 232:
		addToSP();
		break;
	case 233:
		jump(HL, 1);
		break;
	case 234:
		loadReg16(addressToWriteTo);
		copyReg8(mem->read(addressToWriteTo), A);
		break;
	case 238:
		xorA(mem->read(PC));
		++PC;
		++cyclesRemaining;
		break;
	case 239:
		conditionalCall(40, true);
		++cyclesRemaining;
		break;
	case 240:
		copyReg8(A, getHighMemory(mem->read(PC)));
		++PC;
		++cyclesRemaining;
		break;
	case 241:
		fillFromStack(A, F);
		// Sets bits 0, 1, 2, and 3 of the F register back to 0 (These bits should be unused)
		F = F & (Z_FLAG | N_FLAG | H_FLAG | C_FLAG);
		break;
	case 242:
		copyReg8(A, getHighMemory(C));
		break;
	case 243:
		DI();
		break;
	case 245:
		pushToStack(A, F);
		break;
	case 246:
		orA(mem->read(PC));
		++PC;
		++cyclesRemaining;
		break;
	case 247:
		conditionalCall(48, true);
		++cyclesRemaining;
		break;
	case 248:
		loadHLWithEditedSP();
		break;
	case 249:
		SP = HL;
		cyclesRemaining += 2;
		break;
	case 250:
		loadReg16(addressToWriteTo);
		copyReg8(A, mem->read(addressToWriteTo));
		break;
	case 251:
		EI();
		break;
	case 254:
		compareA(mem->read(PC));
		++PC;
		++cyclesRemaining;
		break;
	case 255:
		conditionalCall(56, true);
		++cyclesRemaining;
		break;
	}
}