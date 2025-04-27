#include "CPU.h"

void GBCPU::processUnprefixedOPCode() {
	switch (OPCode) {
	case 0x00:
		// NO OP
		if (cyclesRemaining == 0) {
			cyclesRemaining = 1;
		}
		break;
	case 0x01:
		x01();
		break;
	case 0x02:
		x02();
		break;
	case 0x03:
		x03();
		break;
	case 0x04:
		x04();
		break;
	case 0x05:
		x05();
		break;
	case 0x06:
		x06();
		break;
	case 0x07:
		x07();
		break;
	case 0x08:
		x08();
		break;
	case 0x09:
		x09();
		break;
	case 0x0A:
		x0A();
		break;
	case 0x0B:
		x0B();
		break;
	case 0x0C:
		x0C();
		break;
	case 0x0D:
		x0D();
		break;
	case 0x0E:
		x0E();
		break;
	case 0x0F:
		x0F();
		break;
	case 0x10:
		x10();
		break;
	case 0x11:
		x11();
		break;
	case 0x12:
		x12();
		break;
	case 0x13:
		x13();
		break;
	case 0x14:
		x14();
		break;
	case 0x15:
		x15();
		break;
	case 0x16:
		x16();
		break;
	case 0x17:
		x17();
		break;
	case 0x18:
		x18();
		break;
	case 0x19:
		x19();
		break;
	case 0x1A:
		x1A();
		break;
	case 0x1B:
		x1B();
		break;
	case 0x1C:
		x1C();
		break;
	case 0x1D:
		x1D();
		break;
	case 0x1E:
		x1E();
		break;
	case 0x1F:
		x1F();
		break;
	case 0x20:
		x20();
		break;
	case 0x21:
		x21();
		break;
	case 0x22:
		x22();
		break;
	case 0x23:
		x23();
		break;
	case 0x24:
		x24();
		break;
	case 0x25:
		x25();
		break;
	case 0x26:
		x26();
		break;
	case 0x27:
		x27();
		break;
	case 0x28:
		x28();
		break;
	case 0x29:
		x29();
		break;
	case 0x2A:
		x2A();
		break;
	case 0x2B:
		x2B();
		break;
	case 0x2C:
		x2C();
		break;
	case 0x2D:
		x2D();
		break;
	case 0x2E:
		x2E();
		break;
	case 0x2F:
		x2F();
		break;
	case 0x30:
		x30();
		break;
	case 0x31:
		x31();
		break;
	case 0x32:
		x32();
		break;
	case 0x33:
		x33();
		break;
	case 0x34:
		x34();
		break;
	case 0x35:
		x35();
		break;
	case 0x36:
		x36();
		break;
	case 0x37:
		x37();
		break;
	case 0x38:
		x38();
		break;
	case 0x39:
		x39();
		break;
	case 0x3A:
		x3A();
		break;
	case 0x3B:
		x3B();
		break;
	case 0x3C:
		x3C();
		break;
	case 0x3D:
		x3D();
		break;
	case 0x3E:
		x3E();
		break;
	case 0x3F:
		x3F();
		break;
	case 0x40:
		x40();
		break;
	case 0x41:
		x41();
		break;
	case 0x42:
		x42();
		break;
	case 0x43:
		x43();
		break;
	case 0x44:
		x44();
		break;
	case 0x45:
		x45();
		break;
	case 0x46:
		x46();
		break;
	case 0x47:
		x47();
		break;
	case 0x48:
		x48();
		break;
	case 0x49:
		x49();
		break;
	case 0x4A:
		x4A();
		break;
	case 0x4B:
		x4B();
		break;
	case 0x4C:
		x4C();
		break;
	case 0x4D:
		x4D();
		break;
	case 0x4E:
		x4E();
		break;
	case 0x4F:
		x4F();
		break;
	case 0x50:
		x50();
		break;
	case 0x51:
		x51();
		break;
	case 0x52:
		x52();
		break;
	case 0x53:
		x53();
		break;
	case 0x54:
		x54();
		break;
	case 0x55:
		x55();
		break;
	case 0x56:
		x56();
		break;
	case 0x57:
		x57();
		break;
	case 0x58:
		x58();
		break;
	case 0x59:
		x59();
		break;
	case 0x5A:
		x5A();
		break;
	case 0x5B:
		x5B();
		break;
	case 0x5C:
		x5C();
		break;
	case 0x5D:
		x5D();
		break;
	case 0x5E:
		x5E();
		break;
	case 0x5F:
		x5F();
		break;
	case 0x60:
		x60();
		break;
	case 0x61:
		x61();
		break;
	case 0x62:
		x62();
		break;
	case 0x63:
		x63();
		break;
	case 0x64:
		x64();
		break;
	case 0x65:
		x65();
		break;
	case 0x66:
		x66();
		break;
	case 0x67:
		x67();
		break;
	case 0x68:
		x68();
		break;
	case 0x69:
		x69();
		break;
	case 0x6A:
		x6A();
		break;
	case 0x6B:
		x6B();
		break;
	case 0x6C:
		x6C();
		break;
	case 0x6D:
		x6D();
		break;
	case 0x6E:
		x6E();
		break;
	case 0x6F:
		x6F();
		break;
	case 0x70:
		x70();
		break;
	case 0x71:
		x71();
		break;
	case 0x72:
		x72();
		break;
	case 0x73:
		x73();
		break;
	case 0x74:
		x74();
		break;
	case 0x75:
		x75();
		break;
	case 0x76:
		x76();
		break;
	case 0x77:
		x77();
		break;
	case 0x78:
		x78();
		break;
	case 0x79:
		x79();
		break;
	case 0x7A:
		x7A();
		break;
	case 0x7B:
		x7B();
		break;
	case 0x7C:
		x7C();
		break;
	case 0x7D:
		x7D();
		break;
	case 0x7E:
		x7E();
		break;
	case 0x7F:
		x7F();
		break;
	case 0x80:
		x80();
		break;
	case 0x81:
		x81();
		break;
	case 0x82:
		x82();
		break;
	case 0x83:
		x83();
		break;
	case 0x84:
		x84();
		break;
	case 0x85:
		x85();
		break;
	case 0x86:
		x86();
		break;
	case 0x87:
		x87();
		break;
	case 0x88:
		x88();
		break;
	case 0x89:
		x89();
		break;
	case 0x8A:
		x8A();
		break;
	case 0x8B:
		x8B();
		break;
	case 0x8C:
		x8C();
		break;
	case 0x8D:
		x8D();
		break;
	case 0x8E:
		x8E();
		break;
	case 0x8F:
		x8F();
		break;
	case 0x90:
		x90();
		break;
	case 0x91:
		x91();
		break;
	case 0x92:
		x92();
		break;
	case 0x93:
		x93();
		break;
	case 0x94:
		x94();
		break;
	case 0x95:
		x95();
		break;
	case 0x96:
		x96();
		break;
	case 0x97:
		x97();
		break;
	case 0x98:
		x98();
		break;
	case 0x99:
		x99();
		break;
	case 0x9A:
		x9A();
		break;
	case 0x9B:
		x9B();
		break;
	case 0x9C:
		x9C();
		break;
	case 0x9D:
		x9D();
		break;
	case 0x9E:
		x9E();
		break;
	case 0x9F:
		x9F();
		break;
	case 0xA0:
		xA0();
		break;
	case 0xA1:
		xA1();
		break;
	case 0xA2:
		xA2();
		break;
	case 0xA3:
		xA3();
		break;
	case 0xA4:
		xA4();
		break;
	case 0xA5:
		xA5();
		break;
	case 0xA6:
		xA6();
		break;
	case 0xA7:
		xA7();
		break;
	case 0xA8:
		xA8();
		break;
	case 0xA9:
		xA9();
		break;
	case 0xAA:
		xAA();
		break;
	case 0xAB:
		xAB();
		break;
	case 0xAC:
		xAC();
		break;
	case 0xAD:
		xAD();
		break;
	case 0xAE:
		xAE();
		break;
	case 0xAF:
		xAF();
		break;
	case 0xB0:
		xB0();
		break;
	case 0xB1:
		xB1();
		break;
	case 0xB2:
		xB2();
		break;
	case 0xB3:
		xB3();
		break;
	case 0xB4:
		xB4();
		break;
	case 0xB5:
		xB5();
		break;
	case 0xB6:
		xB6();
		break;
	case 0xB7:
		xB7();
		break;
	case 0xB8:
		xB8();
		break;
	case 0xB9:
		xB9();
		break;
	case 0xBA:
		xBA();
		break;
	case 0xBB:
		xBB();
		break;
	case 0xBC:
		xBC();
		break;
	case 0xBD:
		xBD();
		break;
	case 0xBE:
		xBE();
		break;
	case 0xBF:
		xBF();
		break;
	case 0xC0:
		xC0();
		break;
	case 0xC1:
		xC1();
		break;
	case 0xC2:
		xC2();
		break;
	case 0xC3:
		xC3();
		break;
	case 0xC4:
		xC4();
		break;
	case 0xC5:
		xC5();
		break;
	case 0xC6:
		xC6();
		break;
	case 0xC7:
		xC7();
		break;
	case 0xC8:
		xC8();
		break;
	case 0xC9:
		xC9();
		break;
	case 0xCA:
		xCA();
		break;
	case 0xCB:
		xCB();
		break;
	case 0xCC:
		xCC();
		break;
	case 0xCD:
		xCD();
		break;
	case 0xCE:
		xCE();
		break;
	case 0xCF:
		xCF();
		break;
	case 0xD0:
		xD0();
		break;
	case 0xD1:
		xD1();
		break;
	case 0xD2:
		xD2();
		break;
	case 0xD4:
		xD4();
		break;
	case 0xD5:
		xD5();
		break;
	case 0xD6:
		xD6();
		break;
	case 0xD7:
		xD7();
		break;
	case 0xD8:
		xD8();
		break;
	case 0xD9:
		xD9();
		break;
	case 0xDA:
		xDA();
		break;
	case 0xDC:
		xDC();
		break;
	case 0xDE:
		xDE();
		break;
	case 0xDF:
		xDF();
		break;
	case 0xE0:
		xE0();
		break;
	case 0xE1:
		xE1();
		break;
	case 0xE2:
		xE2();
		break;
	case 0xE5:
		xE5();
		break;
	case 0xE6:
		xE6();
		break;
	case 0xE7:
		xE7();
		break;
	case 0xE8:
		xE8();
		break;
	case 0xE9:
		xE9();
		break;
	case 0xEA:
		xEA();
		break;
	case 0xEE:
		xEE();
		break;
	case 0xEF:
		xEF();
		break;
	case 0xF0:
		xF0();
		break;
	case 0xF1:
		xF1();
		break;
	case 0xF2:
		xF2();
		break;
	case 0xF3:
		xF3();
		break;
	case 0xF5:
		xF5();
		break;
	case 0xF6:
		xF6();
		break;
	case 0xF7:
		xF7();
		break;
	case 0xF8:
		xF8();
		break;
	case 0xF9:
		xF9();
		break;
	case 0xFA:
		xFA();
		break;
	case 0xFB:
		xFB();
		break;
	case 0xFE:
		xFE();
		break;
	case 0xFF:
		xFF();
		break;
	default:
		cyclesRemaining = 1;
		std::cout << "UNDEFINED OPCODES: " << OPCode << std::endl;
	}
}

void GBCPU::x01() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		C = mem->read(PC);
		++PC;
		break;
	case 1:
		B = mem->read(PC);
		++PC;
		break;
	}
}

void GBCPU::x02() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address BC = (B << 8) + C;
		mem->write(BC, A);
		break;
	}
}

void GBCPU::x03() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		++C;
		// Check for overflow into register B
		if (C == 0) {
			++B;
		}
		break;
	}
}

void GBCPU::x04() {
	cyclesRemaining = 1;
	++B;
	bool zeroFlag = (B == 0);
	bool halfCarryFlag = ((B & 0b00001111) == 0);

	F = (F & C_FLAG) + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x05() {
	cyclesRemaining = 1;
	--B;
	bool zeroFlag = (B == 0);
	bool halfCarryFlag = ((B & 0b00001111) == 0b00001111);

	F = (F & C_FLAG) + N_FLAG + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x06() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		B = mem->read(PC);
		++PC;
	}
}

void GBCPU::x07() {
	cyclesRemaining = 1;
	bool carryFlag = A & 0b10000000;

	A = (A << 1) | carryFlag;
	F = carryFlag * C_FLAG;
}

void GBCPU::x08() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 5;
		break;
	case 4:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 3:
		tempByte2 = mem->read(PC);
		tempAddress = (tempByte2 << 8) + tempByte1;
		++PC;
		break;
	case 2:
		mem->write(tempAddress, SP & 0xFF);
		break;
	case 1:
		mem->write(tempAddress + 1, SP >> 8);
		break;
	}
}

void GBCPU::x09() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address BC = (B << 8) + C;
		address HL = (H << 8) + L;

		address sum = BC + HL;
		H = sum >> 8;
		L = sum & 0xFF;

		bool carryFlag = (sum < BC);

		int leastSigTwelveBitsBC = BC & 0b0000111111111111;
		int leastSigTwelveBitsHL = HL & 0b0000111111111111;
		bool halfCarryFlag = (leastSigTwelveBitsBC + leastSigTwelveBitsHL >= (1 << 12));

		F = (F & Z_FLAG) + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
		
		break;
	}
}

void GBCPU::x0A() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address BC = (B << 8) + C;
		A = mem->read(BC);
		break;
	}
}

void GBCPU::x0B() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		--C;
		// Check for carry from register B
		if (C == 0xFF) {
			--B;
		}
		break;
	}
}

void GBCPU::x0C() {
	cyclesRemaining = 1;
	++C;
	bool zeroFlag = (C == 0);
	bool halfCarryFlag = ((C & 0b00001111) == 0);

	F = (F & C_FLAG) + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x0D() {
	cyclesRemaining = 1;
	--C;
	bool zeroFlag = (C == 0);
	bool halfCarryFlag = ((C & 0b00001111) == 0b00001111);

	F = (F & C_FLAG) + N_FLAG + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x0E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		C = mem->read(PC);
		++PC;
	}
}

void GBCPU::x0F() {
	cyclesRemaining = 1;
	bool carryFlag = A & 0b00000001;

	A = (carryFlag * 0b10000000) | (A >> 1);
	F = carryFlag * C_FLAG;
}

void GBCPU::x10() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	}
}

void GBCPU::x11() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		E = mem->read(PC);
		++PC;
		break;
	case 1:
		D = mem->read(PC);
		++PC;
		break;
	}
}

void GBCPU::x12() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address DE= (D << 8) + E;
		mem->write(DE, A);
		break;
	}
}

void GBCPU::x13() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		++E;
		if (E == 0) {
			++D;
		}
		break;
	}
}

void GBCPU::x14() {
	cyclesRemaining = 1;
	++D;
	bool zeroFlag = (D == 0);
	bool halfCarryFlag = ((D & 0b00001111) == 0);

	F = (F & C_FLAG) + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x15() {
	cyclesRemaining = 1;
	--D;
	bool zeroFlag = (D == 0);
	bool halfCarryFlag = ((D & 0b00001111) == 0b00001111);

	F = (F & C_FLAG) + N_FLAG + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x16() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		D = mem->read(PC);
		++PC;
	}
}

void GBCPU::x17() {
	cyclesRemaining = 1;
	bool oldCarryFlag = F & C_FLAG;
	bool carryFlag = A & 0b10000000;

	A = (A << 1) | oldCarryFlag;
	F = carryFlag * C_FLAG;
}

void GBCPU::x18() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte = mem->read(PC);
		++PC;
		break;
	case 1:
		int offset = tempByte;
		if (tempByte & 0b10000000) {
			offset -= 256;
		}
		PC = PC + offset;
		break;
	}
}

void GBCPU::x19() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address DE = (D << 8) + E;
		address HL = (H << 8) + L;

		address sum = DE + HL;
		H = sum >> 8;
		L = sum & 0xFF;

		bool carryFlag = (sum < DE);

		int leastSigTwelveBitsBC = DE & 0b0000111111111111;
		int leastSigTwelveBitsHL = HL & 0b0000111111111111;
		bool halfCarryFlag = (leastSigTwelveBitsBC + leastSigTwelveBitsHL >= (1 << 12));

		F = (F & Z_FLAG) + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;

		break;
	}
}

void GBCPU::x1A() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address DE = (D << 8) + E;
		A = mem->read(DE);
		break;
	}
}

void GBCPU::x1B() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		--E;
		if (E == 0xFF) {
			--D;
		}
		break;
	}
}

void GBCPU::x1C() {
	cyclesRemaining = 1;
	++E;
	bool zeroFlag = (E == 0);
	bool halfCarryFlag = ((E & 0b00001111) == 0);

	F = (F & C_FLAG) + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x1D() {
	cyclesRemaining = 1;
	--E;
	bool zeroFlag = (E == 0);
	bool halfCarryFlag = ((E & 0b00001111) == 0b00001111);

	F = (F & C_FLAG) + N_FLAG + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x1E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		E = mem->read(PC);
		++PC;
	}
}

void GBCPU::x1F() {
	cyclesRemaining = 1;
	bool oldCarryFlag = F & C_FLAG;
	bool carryFlag = A & 0b00000001;

	A = (oldCarryFlag * 0b10000000) | (A >> 1);
	F = carryFlag * C_FLAG;
}

void GBCPU::x20() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte = mem->read(PC);
		++PC;
		if (F & Z_FLAG) {
			--cyclesRemaining;
		}
		break;
	case 1:
		int offset = tempByte;
		if (tempByte & 0b10000000) {
			offset -= 256;
		}
		PC = PC + offset;
		break;
	}
}

void GBCPU::x21() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		L = mem->read(PC);
		++PC;
		break;
	case 1:
		H = mem->read(PC);
		++PC;
		break;
	}
}

void GBCPU::x22() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, A);

		++L;
		if (L == 0) {
			++H;
		}
		break;
	}
}

void GBCPU::x23() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		++L;
		if (L == 0) {
			++H;
		}
		break;
	}
}

void GBCPU::x24() {
	cyclesRemaining = 1;
	++H;
	bool zeroFlag = (H == 0);
	bool halfCarryFlag = ((H & 0b00001111) == 0);

	F = (F & C_FLAG) + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x25() {
	cyclesRemaining = 1;
	--H;
	bool zeroFlag = (H == 0);
	bool halfCarryFlag = ((H & 0b00001111) == 0b00001111);

	F = (F & C_FLAG) + N_FLAG + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x26() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		H = mem->read(PC);
		++PC;
	}
}

void GBCPU::x27() {
	cyclesRemaining = 1;
	
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
}

void GBCPU::x28() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte = mem->read(PC);
		++PC;
		if (!(F & Z_FLAG)) {
			--cyclesRemaining;
		}
		break;
	case 1:
		int offset = tempByte;
		if (tempByte & 0b10000000) {
			offset -= 256;
		}
		PC = PC + offset;
		break;
	}
}

void GBCPU::x29() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;

		address sum = HL + HL;
		H = sum >> 8;
		L = sum & 0xFF;

		bool carryFlag = (sum < HL);

		int leastSigTwelveBitsHL = HL & 0b0000111111111111;
		bool halfCarryFlag = (leastSigTwelveBitsHL + leastSigTwelveBitsHL >= (1 << 12));

		F = (F & Z_FLAG) + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;

		break;
	}
}

void GBCPU::x2A() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		A = mem->read(HL);

		++L;
		if (L == 0) {
			++H;
		}
		break;
	}
}

void GBCPU::x2B() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		--L;
		if (L == 0xFF) {
			--H;
		}
		break;
	}
}

void GBCPU::x2C() {
	cyclesRemaining = 1;
	++L;
	bool zeroFlag = (L == 0);
	bool halfCarryFlag = ((L & 0b00001111) == 0);

	F = (F & C_FLAG) + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x2D() {
	cyclesRemaining = 1;
	--L;
	bool zeroFlag = (L == 0);
	bool halfCarryFlag = ((L & 0b00001111) == 0b00001111);

	F = (F & C_FLAG) + N_FLAG + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x2E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		L = mem->read(PC);
		++PC;
	}
}

void GBCPU::x2F() {
	cyclesRemaining = 1;
	A = ~A;

	F = (F & (Z_FLAG + C_FLAG)) + N_FLAG + H_FLAG;
}

void GBCPU::x30() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte = mem->read(PC);
		++PC;
		if (F & C_FLAG) {
			--cyclesRemaining;
		}
		break;
	case 1:
		int offset = tempByte;
		if (tempByte & 0b10000000) {
			offset -= 256;
		}
		PC = PC + offset;
		break;
	}
}

void GBCPU::x31() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 1:
		tempByte2 = mem->read(PC);
		SP = tempByte1 + (tempByte2 << 8);
		++PC;
		break;
	}
}

void GBCPU::x32() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, A);

		--L;
		if (L == 0xFF) {
			--H;
		}
		break;
	}
}

void GBCPU::x33() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		++SP;
		break;
	}
}

void GBCPU::x34() {
	address HL = (H << 8) + L;

	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte1 = mem->read(HL);
		break;
	case 1:
		++tempByte1;
		bool zeroFlag = (tempByte1 == 0);
		bool halfCarryFlag = ((tempByte1 & 0b00001111) == 0);

		mem->write(HL, tempByte1);

		F = (F & C_FLAG) + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
		break;
	}
}

void GBCPU::x35() {
	address HL = (H << 8) + L;

	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte1 = mem->read(HL);
		break;
	case 1:
		--tempByte1;
		bool zeroFlag = (tempByte1 == 0);
		bool halfCarryFlag = ((tempByte1 & 0b00001111) == 0b00001111);

		mem->write(HL, tempByte1);

		F = (F & C_FLAG) + N_FLAG + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
		break;
	}
}

void GBCPU::x36() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte = mem->read(PC);
		++PC;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, tempByte);
	}
}

void GBCPU::x37() {
	cyclesRemaining = 1;
	
	F = (F & Z_FLAG) + C_FLAG;
}

void GBCPU::x38() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte = mem->read(PC);
		++PC;
		if (!(F & C_FLAG)) {
			--cyclesRemaining;
		}
		break;
	case 1:
		int offset = tempByte;
		if (tempByte & 0b10000000) {
			offset -= 256;
		}
		PC = PC + offset;
		break;
	}
}

void GBCPU::x39() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;

		address sum = SP + HL;
		H = sum >> 8;
		L = sum & 0xFF;

		bool carryFlag = (sum < HL);

		int leastSigTwelveBitsSP = SP & 0b0000111111111111;
		int leastSigTwelveBitsHL = HL & 0b0000111111111111;
		bool halfCarryFlag = (leastSigTwelveBitsSP + leastSigTwelveBitsHL >= (1 << 12));

		F = (F & Z_FLAG) + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;

		break;
	}
}

void GBCPU::x3A() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		A = mem->read(HL);

		--L;
		if (L == 0xFF) {
			--H;
		}
		break;
	}
}

void GBCPU::x3B() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		--SP;
		break;
	}
}

void GBCPU::x3C() {
	cyclesRemaining = 1;
	++A;
	bool zeroFlag = (A == 0);
	bool halfCarryFlag = ((A & 0b00001111) == 0);

	F = (F & C_FLAG) + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x3D() {
	cyclesRemaining = 1;
	--A;
	bool zeroFlag = (A == 0);
	bool halfCarryFlag = ((A & 0b00001111) == 0b00001111);

	F = (F & C_FLAG) + N_FLAG + (zeroFlag * Z_FLAG) + (halfCarryFlag * H_FLAG);
}

void GBCPU::x3E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		A = mem->read(PC);
		++PC;
	}
}

void GBCPU::x3F() {
	cyclesRemaining = 1;

	bool oldCarryFlag = F & C_FLAG;
	F = (F & Z_FLAG) + (!oldCarryFlag) * C_FLAG;
}

void GBCPU::x40() {
	cyclesRemaining = 1;
	B = B;
}

void GBCPU::x41() {
	cyclesRemaining = 1;
	B = C;
}

void GBCPU::x42() {
	cyclesRemaining = 1;
	B = D;
}

void GBCPU::x43() {
	cyclesRemaining = 1;
	B = E;
}

void GBCPU::x44() {
	cyclesRemaining = 1;
	B = H;
}

void GBCPU::x45() {
	cyclesRemaining = 1;
	B = L;
}

void GBCPU::x46() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		B = mem->read(HL);
		break;
	}
}

void GBCPU::x47() {
	cyclesRemaining = 1;
	B = A;
}

void GBCPU::x48() {
	cyclesRemaining = 1;
	C = B;
}

void GBCPU::x49() {
	cyclesRemaining = 1;
	C = C;
}

void GBCPU::x4A() {
	cyclesRemaining = 1;
	C = D;
}

void GBCPU::x4B() {
	cyclesRemaining = 1;
	C = E;
}

void GBCPU::x4C() {
	cyclesRemaining = 1;
	C = H;
}

void GBCPU::x4D() {
	cyclesRemaining = 1;
	C = L;
}

void GBCPU::x4E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		C = mem->read(HL);
		break;
	}
}

void GBCPU::x4F() {
	cyclesRemaining = 1;
	C = A;
}

void GBCPU::x50() {
	cyclesRemaining = 1;
	D = B;
}

void GBCPU::x51() {
	cyclesRemaining = 1;
	D = C;
}

void GBCPU::x52() {
	cyclesRemaining = 1;
	D = D;
}

void GBCPU::x53() {
	cyclesRemaining = 1;
	D = E;
}

void GBCPU::x54() {
	cyclesRemaining = 1;
	D = H;
}

void GBCPU::x55() {
	cyclesRemaining = 1;
	D = L;
}

void GBCPU::x56() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		D = mem->read(HL);
		break;
	}
}

void GBCPU::x57() {
	cyclesRemaining = 1;
	D = A;
}

void GBCPU::x58() {
	cyclesRemaining = 1;
	E = B;
}

void GBCPU::x59() {
	cyclesRemaining = 1;
	E = C;
}

void GBCPU::x5A() {
	cyclesRemaining = 1;
	E = D;
}

void GBCPU::x5B() {
	cyclesRemaining = 1;
	E = E;
}

void GBCPU::x5C() {
	cyclesRemaining = 1;
	E = H;
}

void GBCPU::x5D() {
	cyclesRemaining = 1;
	E = L;
}

void GBCPU::x5E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		E = mem->read(HL);
		break;
	}
}

void GBCPU::x5F() {
	cyclesRemaining = 1;
	E = A;
}

void GBCPU::x60() {
	cyclesRemaining = 1;
	H = B;
}

void GBCPU::x61() {
	cyclesRemaining = 1;
	H = C;
}

void GBCPU::x62() {
	cyclesRemaining = 1;
	H = D;
}

void GBCPU::x63() {
	cyclesRemaining = 1;
	H = E;
}

void GBCPU::x64() {
	cyclesRemaining = 1;
	H = H;
}

void GBCPU::x65() {
	cyclesRemaining = 1;
	H = L;
}

void GBCPU::x66() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		H = mem->read(HL);
		break;
	}
}

void GBCPU::x67() {
	cyclesRemaining = 1;
	H = A;
}

void GBCPU::x68() {
	cyclesRemaining = 1;
	L = B;
}

void GBCPU::x69() {
	cyclesRemaining = 1;
	L = C;
}

void GBCPU::x6A() {
	cyclesRemaining = 1;
	L = D;
}

void GBCPU::x6B() {
	cyclesRemaining = 1;
	L = E;
}

void GBCPU::x6C() {
	cyclesRemaining = 1;
	L = H;
}

void GBCPU::x6D() {
	cyclesRemaining = 1;
	L = L;
}

void GBCPU::x6E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		L = mem->read(HL);
		break;
	}
}

void GBCPU::x6F() {
	cyclesRemaining = 1;
	L = A;
}

void GBCPU::x70() {
	switch (cyclesRemaining) {
	case 0: 
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, B);
		break;
	}
}

void GBCPU::x71() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, C);
		break;
	}
}

void GBCPU::x72() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, D);
		break;
	}
}

void GBCPU::x73() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, E);
		break;
	}
}

void GBCPU::x74() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, H);
		break;
	}
}

void GBCPU::x75() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, L);
		break;
	}
}

void GBCPU::x76() {
	cyclesRemaining = 1;

	byte IF = mem->read(0xFF0F);
	byte IE = mem->read(0xFFFF);

	// Halt CPU if an interrupt is not pending
	if ((IF & IE) == 0) {
		// Interrupt not pending
		isHalted = true;
	}
}

void GBCPU::x77() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		mem->write(HL, A);
		break;
	}
}

void GBCPU::x78() {
	cyclesRemaining = 1;
	A = B;
}

void GBCPU::x79() {
	cyclesRemaining = 1;
	A = C;
}

void GBCPU::x7A() {
	cyclesRemaining = 1;
	A = D;
}

void GBCPU::x7B() {
	cyclesRemaining = 1;
	A = E;
}

void GBCPU::x7C() {
	cyclesRemaining = 1;
	A = H;
}

void GBCPU::x7D() {
	cyclesRemaining = 1;
	A = L;
}

void GBCPU::x7E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		A = mem->read(HL);
		break;
	}
}

void GBCPU::x7F() {
	cyclesRemaining = 1;
	A = A;
}

void GBCPU::x80() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) + (B & 0b01111) >= 0b10000);

	A = A + B;
	bool carryFlag = (A < B);
	bool zeroFlag = (A == 0);
	
	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x81() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) + (C & 0b01111) >= 0b10000);

	A = A + C;
	bool carryFlag = (A < C);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x82() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) + (D & 0b01111) >= 0b10000);

	A = A + D;
	bool carryFlag = (A < D);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x83() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) + (E & 0b01111) >= 0b10000);

	A = A + E;
	bool carryFlag = (A < E);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x84() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) + (H & 0b01111) >= 0b10000);

	A = A + H;
	bool carryFlag = (A < H);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x85() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) + (L & 0b01111) >= 0b10000);

	A = A + L;
	bool carryFlag = (A < L);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x86() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		tempByte1 = mem->read(HL);

		bool halfCarryFlag = ((A & 0b01111) + (tempByte1 & 0b01111) >= 0b10000);

		A = A + tempByte1;
		bool carryFlag = (A < tempByte1);
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::x87() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ( 2 * (A & 0b01111) >= 0b10000);

	byte oldAValue = A;
	A = A + A;
	bool carryFlag = (A < oldAValue);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x88() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) + (B & 0b01111) + oldCarry >= 0b10000);

	A = A + B + oldCarry;
	bool carryFlag = (A < B + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x89() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) + (C & 0b01111) + oldCarry >= 0b10000);

	A = A + C + oldCarry;
	bool carryFlag = (A < C + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x8A() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) + (D & 0b01111) + oldCarry >= 0b10000);

	A = A + D + oldCarry;
	bool carryFlag = (A < D + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x8B() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) + (E & 0b01111) + oldCarry >= 0b10000);

	A = A + E + oldCarry;
	bool carryFlag = (A < E + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x8C() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) + (H & 0b01111) + oldCarry >= 0b10000);

	A = A + H + oldCarry;
	bool carryFlag = (A < H + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x8D() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) + (L & 0b01111) + oldCarry >= 0b10000);

	A = A + L + oldCarry;
	bool carryFlag = (A < L + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x8E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		tempByte1 = mem->read(HL);

		bool oldCarry = F & C_FLAG;

		bool halfCarryFlag = ((A & 0b01111) + (tempByte1 & 0b01111) + oldCarry >= 0b10000);

		A = A + tempByte1 + oldCarry;
		bool carryFlag = (A < tempByte1 + oldCarry);
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::x8F() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = (2 * (A & 0b01111) + oldCarry >= 0b10000);

	byte oldAValue = A;
	A = A + A + oldCarry;
	bool carryFlag = (A < oldAValue + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x90() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (B & 0b01111));
	bool carryFlag = (A < B);

	A = A - B;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x91() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (C & 0b01111));
	bool carryFlag = (A < C);

	A = A - C;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x92() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (D & 0b01111));
	bool carryFlag = (A < D);

	A = A - D;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x93() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (E & 0b01111));
	bool carryFlag = (A < E);

	A = A - E;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x94() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (H & 0b01111));
	bool carryFlag = (A < H);

	A = A - H;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x95() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (L & 0b01111));
	bool carryFlag = (A < L);

	A = A - L;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x96() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		tempByte1 = mem->read(HL);

		bool halfCarryFlag = ((A & 0b01111) < (tempByte1 & 0b01111));
		bool carryFlag = (A < tempByte1);

		A = A - tempByte1;
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::x97() {
	cyclesRemaining = 1;
	A = 0;

	F = Z_FLAG + N_FLAG;
}

void GBCPU::x98() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) < (B & 0b01111) + oldCarry);
	bool carryFlag = (A < B + oldCarry);

	A = A - (B + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x99() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) < (C & 0b01111) + oldCarry);
	bool carryFlag = (A < C + oldCarry);

	A = A - (C + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x9A() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) < (D & 0b01111) + oldCarry);
	bool carryFlag = (A < D + oldCarry);

	A = A - (D + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x9B() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) < (E & 0b01111) + oldCarry);
	bool carryFlag = (A < E + oldCarry);

	A = A - (E + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x9C() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) < (H & 0b01111) + oldCarry);
	bool carryFlag = (A < H + oldCarry);

	A = A - (H + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x9D() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = ((A & 0b01111) < (L & 0b01111) + oldCarry);
	bool carryFlag = (A < L + oldCarry);

	A = A - (L + oldCarry);
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::x9E() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		tempByte1 = mem->read(HL);

		bool oldCarry = F & C_FLAG;

		bool halfCarryFlag = ((A & 0b01111) < (tempByte1 & 0b01111) + oldCarry);
		bool carryFlag = (A < tempByte1 + oldCarry);

		A = A - (tempByte1 + oldCarry);
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::x9F() {
	cyclesRemaining = 1;
	bool oldCarry = F & C_FLAG;

	bool halfCarryFlag = oldCarry;
	bool carryFlag = oldCarry;

	A = -oldCarry;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::xA0() {
	cyclesRemaining = 1;

	A = A & B;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + H_FLAG;
}

void GBCPU::xA1() {
	cyclesRemaining = 1;

	A = A & C;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + H_FLAG;
}

void GBCPU::xA2() {
	cyclesRemaining = 1;

	A = A & D;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + H_FLAG;
}

void GBCPU::xA3() {
	cyclesRemaining = 1;

	A = A & E;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + H_FLAG;
}

void GBCPU::xA4() {
	cyclesRemaining = 1;

	A = A & H;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + H_FLAG;
}

void GBCPU::xA5() {
	cyclesRemaining = 1;

	A = A & L;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + H_FLAG;
}

void GBCPU::xA6() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		tempByte1 = mem->read(HL);

		A = A & tempByte1;
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + H_FLAG;
	}
}

void GBCPU::xA7() {
	cyclesRemaining = 1;
	
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG + H_FLAG;
}

void GBCPU::xA8() {
	cyclesRemaining = 1;

	A = A ^ B;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xA9() {
	cyclesRemaining = 1;

	A = A ^ C;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xAA() {
	cyclesRemaining = 1;

	A = A ^ D;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xAB() {
	cyclesRemaining = 1;

	A = A ^ E;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xAC() {
	cyclesRemaining = 1;

	A = A ^ H;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xAD() {
	cyclesRemaining = 1;

	A = A ^ L;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xAE() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		tempByte1 = mem->read(HL);

		A = A ^ tempByte1;
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG;
	}
}

void GBCPU::xAF() {
	cyclesRemaining = 1;

	A = 0;

	F = Z_FLAG;
}

void GBCPU::xB0() {
	cyclesRemaining = 1;

	A = A | B;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xB1() {
	cyclesRemaining = 1;

	A = A | C;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xB2() {
	cyclesRemaining = 1;

	A = A | D;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xB3() {
	cyclesRemaining = 1;

	A = A | E;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xB4() {
	cyclesRemaining = 1;

	A = A | H;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xB5() {
	cyclesRemaining = 1;

	A = A | L;
	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xB6() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		tempByte1 = mem->read(HL);

		A = A | tempByte1;
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG;
	}
}

void GBCPU::xB7() {
	cyclesRemaining = 1;

	bool zeroFlag = (A == 0);

	F = zeroFlag * Z_FLAG;
}

void GBCPU::xB8() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (B & 0b01111));
	bool carryFlag = (A < B);
	bool zeroFlag = (A == B);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::xB9() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (C & 0b01111));
	bool carryFlag = (A < C);
	bool zeroFlag = (A == C);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::xBA() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (D & 0b01111));
	bool carryFlag = (A < D);
	bool zeroFlag = (A == D);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::xBB() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (E & 0b01111));
	bool carryFlag = (A < E);
	bool zeroFlag = (A == E);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::xBC() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (H & 0b01111));
	bool carryFlag = (A < H);
	bool zeroFlag = (A == H);
	 
	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::xBD() {
	cyclesRemaining = 1;

	bool halfCarryFlag = ((A & 0b01111) < (L & 0b01111));
	bool carryFlag = (A < L);
	bool zeroFlag = (A == L);

	F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
}

void GBCPU::xBE() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		address HL = (H << 8) + L;
		tempByte1 = mem->read(HL);

		bool halfCarryFlag = ((A & 0b01111) < (tempByte1 & 0b01111));
		bool carryFlag = (A < tempByte1);
		bool zeroFlag = (A == tempByte1);

		F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::xBF() {
	cyclesRemaining = 1;

	F = Z_FLAG + N_FLAG;
}

void GBCPU::xC0() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 5;
		break;
	case 4:
		if (F & Z_FLAG) {
			cyclesRemaining = 1;
		}
		break;
	case 3:
		tempByte1 = mem->read(SP);
		++SP;
		break;
	case 2:
		tempByte2 = mem->read(SP);
		++SP;
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xC1() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		C = mem->read(SP);
		++SP;
		break;
	case 1:
		B = mem->read(SP);
		++SP;
		break;
	}
}

void GBCPU::xC2() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 2:
		tempByte2 = mem->read(PC);
		++PC;

		if (F & Z_FLAG) {
			cyclesRemaining = 1;
		}
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xC3() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 2:
		tempByte2 = mem->read(PC);
		++PC;
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xC4() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 6;
		break;
	case 5:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 4:
		tempByte2 = mem->read(PC);
		++PC;

		if (F & Z_FLAG) {
			cyclesRemaining = 1;
		}
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = tempByte1 + (tempByte2 << 8);
	}
}

void GBCPU::xC5() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, B);
		break;
	case 1:
		--SP;
		mem->write(SP, C);
	}
}

void GBCPU::xC6() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		tempByte1 = mem->read(PC);
		++PC;

		bool halfCarryFlag = ((A & 0b01111) + (tempByte1 & 0b01111) >= 0b10000);

		A = A + tempByte1;
		bool carryFlag = (A < tempByte1);
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::xC7() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = 0x00;
	}
}

void GBCPU::xC8() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 5;
		break;
	case 4:
		if (!(F & Z_FLAG)) {
			cyclesRemaining = 1;
		}
		break;
	case 3:
		tempByte1 = mem->read(SP);
		++SP;
		break;
	case 2:
		tempByte2 = mem->read(SP);
		++SP;
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xC9() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(SP);
		++SP;
		break;
	case 2:
		tempByte2 = mem->read(SP);
		++SP;
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xCA() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 2:
		tempByte2 = mem->read(PC);
		++PC;

		if (!(F & Z_FLAG)) {
			cyclesRemaining = 1;
		}
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xCB() {
	cyclesRemaining = 1;
	nextInstructionPrefixed = true;
}

void GBCPU::xCC() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 6;
		break;
	case 5:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 4:
		tempByte2 = mem->read(PC);
		++PC;

		if (!(F & Z_FLAG)) {
			cyclesRemaining = 1;
		}
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = tempByte1 + (tempByte2 << 8);
	}
}

void GBCPU::xCD() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 6;
		break;
	case 5:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 4:
		tempByte2 = mem->read(PC);
		++PC;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = tempByte1 + (tempByte2 << 8);
	}
}

void GBCPU::xCE() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		tempByte1 = mem->read(PC);
		++PC;

		bool oldCarry = F & C_FLAG;

		bool halfCarryFlag = ((A & 0b01111) + (tempByte1 & 0b01111) + oldCarry >= 0b10000);

		A = A + tempByte1 + oldCarry;
		bool carryFlag = (A < tempByte1 + oldCarry);
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::xCF() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = 0x08;
	}
}

void GBCPU::xD0() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 5;
		break;
	case 4:
		if (F & C_FLAG) {
			cyclesRemaining = 1;
		}
		break;
	case 3:
		tempByte1 = mem->read(SP);
		++SP;
		break;
	case 2:
		tempByte2 = mem->read(SP);
		++SP;
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xD1() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		E = mem->read(SP);
		++SP;
		break;
	case 1:
		D = mem->read(SP);
		++SP;
		break;
	}
}

void GBCPU::xD2() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 2:
		tempByte2 = mem->read(PC);
		++PC;

		if (F & C_FLAG) {
			cyclesRemaining = 1;
		}
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xD4() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 6;
		break;
	case 5:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 4:
		tempByte2 = mem->read(PC);
		++PC;

		if (F & C_FLAG) {
			cyclesRemaining = 1;
		}
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = tempByte1 + (tempByte2 << 8);
	}
}

void GBCPU::xD5() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, D);
		break;
	case 1:
		--SP;
		mem->write(SP, E);
	}
}

void GBCPU::xD6() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		tempByte1 = mem->read(PC);
		++PC;

		bool halfCarryFlag = ((A & 0b01111) < (tempByte1 & 0b01111));
		bool carryFlag = (A < tempByte1);

		A = A - tempByte1;
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::xD7() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = 0x10;
	}
}

void GBCPU::xD8() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 5;
		break;
	case 4:
		if (!(F & C_FLAG)) {
			cyclesRemaining = 1;
		}
		break;
	case 3:
		tempByte1 = mem->read(SP);
		++SP;
		break;
	case 2:
		tempByte2 = mem->read(SP);
		++SP;
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xD9() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(SP);
		++SP;
		break;
	case 2:
		tempByte2 = mem->read(SP);
		++SP;
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		IME = 1;
		break;
	}
}

void GBCPU::xDA() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 2:
		tempByte2 = mem->read(PC);
		++PC;

		if (!(F & C_FLAG)) {
			cyclesRemaining = 1;
		}
		break;
	case 1:
		PC = tempByte1 + (tempByte2 << 8);
		break;
	}
}

void GBCPU::xDC() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 6;
		break;
	case 5:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 4:
		tempByte2 = mem->read(PC);
		++PC;

		if (!(F & C_FLAG)) {
			cyclesRemaining = 1;
		}
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = tempByte1 + (tempByte2 << 8);
	}
}

void GBCPU::xDE() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		tempByte1 = mem->read(PC);
		++PC;

		bool oldCarry = F & C_FLAG;

		bool halfCarryFlag = ((A & 0b01111) < (tempByte1 & 0b01111) + oldCarry);
		bool carryFlag = (A < tempByte1 + oldCarry);

		A = A - (tempByte1 + oldCarry);
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::xDF() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = 0x18;
	}
}

void GBCPU::xE0() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 1:
		mem->write(0xFF00 + tempByte1, A);
		break;
	}
}

void GBCPU::xE1() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		L = mem->read(SP);
		++SP;
		break;
	case 1:
		H = mem->read(SP);
		++SP;
		break;
	}
}

void GBCPU::xE2() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		mem->write(0xFF00 + C, A);
		break;
	}
}

void GBCPU::xE5() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, H);
		break;
	case 1:
		--SP;
		mem->write(SP, L);
	}
}

void GBCPU::xE6() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		tempByte1 = mem->read(PC);
		++PC;

		A = A & tempByte1;
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG + H_FLAG;
	}
}

void GBCPU::xE7() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = 0x20;
	}
}

void GBCPU::xE8() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		int offset = mem->read(PC);
		++PC;
		
		if (offset >= 128) {
			offset -= 256;
		}
		bool halfCarryFlag = ((SP & 15) + (offset & 15)) > 15;

		address oldSPValue = SP;
		SP += offset;
		bool carryFlag = ((byte)oldSPValue > (byte)SP);

		F = halfCarryFlag * H_FLAG + carryFlag * C_FLAG;
		break;
	}
}

void GBCPU::xE9() {
	cyclesRemaining = 1;
	PC = L + ((H << 8) & 0b1111111100000000);
}

void GBCPU::xEA() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 2:
		tempByte2 = mem->read(PC);
		++PC;
		break;
	case 1:
		tempAddress = tempByte1 + (tempByte2 << 8);
		mem->write(tempAddress, A);
		break;
	}
}

void GBCPU::xEE() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		tempByte1 = mem->read(PC);
		++PC;

		A = A ^ tempByte1;
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG;
	}
}

void GBCPU::xEF() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = 0x28;
	}
}

void GBCPU::xF0() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 1:
		A = mem->read(0xFF00 + tempByte1);
		break;
	}
}

void GBCPU::xF1() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		F = mem->read(SP) & 0b11110000;
		++SP;
		break;
	case 1:
		A = mem->read(SP);
		++SP;
		break;
	}
}

void GBCPU::xF2() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		A = mem->read(0xFF00 + C);
		break;
	}
}

void GBCPU::xF3() {
	cyclesRemaining = 1;
	IME = 0;
}

void GBCPU::xF5() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, A);
		break;
	case 1:
		--SP;
		mem->write(SP, F);
	}
}

void GBCPU::xF6() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		tempByte1 = mem->read(PC);
		++PC;

		A = A | tempByte1;
		bool zeroFlag = (A == 0);

		F = zeroFlag * Z_FLAG;
	}
}

void GBCPU::xF7() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = 0x30;
	}
}

void GBCPU::xF8() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 3;
		break;
	case 2:
		int offset = mem->read(PC);
		++PC;

		if (offset >= 128) {
			offset -= 256;
		}
		bool halfCarryFlag = ((SP & 15) + (offset & 15)) > 15;

		tempAddress = SP + offset;
		bool carryFlag = ((byte)SP > (byte)tempAddress);

		H = tempAddress >> 8;
		L = tempAddress & 0xFF;

		F = halfCarryFlag * H_FLAG + carryFlag * C_FLAG;
		break;
	}
}

void GBCPU::xF9() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		SP = L + (H << 8);
	}
}

void GBCPU::xFA() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 3:
		tempByte1 = mem->read(PC);
		++PC;
		break;
	case 2:
		tempByte2 = mem->read(PC);
		++PC;
		break;
	case 1:
		tempAddress = tempByte1 + (tempByte2 << 8);
		A = mem->read(tempAddress);
		break;
	}
}

void GBCPU::xFB() {
	cyclesRemaining = 1;
	instructionsBeforeIMESet = 1;
}

void GBCPU::xFE() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 2;
		break;
	case 1:
		tempByte1 = mem->read(PC);
		++PC;

		bool halfCarryFlag = ((A & 0b01111) < (tempByte1 & 0b01111));
		bool carryFlag = (A < tempByte1);
		bool zeroFlag = (A == tempByte1);

		F = zeroFlag * Z_FLAG + N_FLAG + carryFlag * C_FLAG + halfCarryFlag * H_FLAG;
	}
}

void GBCPU::xFF() {
	switch (cyclesRemaining) {
	case 0:
		cyclesRemaining = 4;
		break;
	case 2:
		--SP;
		mem->write(SP, PC >> 8);
		break;
	case 1:
		--SP;
		mem->write(SP, PC & 0xFF);
		PC = 0x38;
	}
}