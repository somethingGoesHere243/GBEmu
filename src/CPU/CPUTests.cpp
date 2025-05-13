#include "CPU/CPUTests.h"

// NOTE: Many of the SM83 Tests now fail to pass due to there reliance on Memory addresses which should not be read to or written from

void initCPU(nlohmann::json& initialState, GBCPU& cpu) {
	// Reset CPU internal state
	cpu.OPCode = 0;
	cpu.OPCodeStep = 0;
	cpu.nextInstructionPrefixed = false;
	cpu.IME = (int)initialState["ime"];
	cpu.instructionsBeforeIMESet = 0;
	cpu.isHalted = false;

	cpu.tempBytePtr = nullptr;
	cpu.tempByte = 0;
	cpu.tempAddress = 0;

	// Set CPU registers as specified
	cpu.A = initialState["a"];
	cpu.B = initialState["b"];
	cpu.C = initialState["c"];
	cpu.D = initialState["d"];
	cpu.E = initialState["e"];
	cpu.F = initialState["f"];
	cpu.H = initialState["h"];
	cpu.L = initialState["l"];
	cpu.PC = initialState["pc"];
	cpu.SP = initialState["sp"];

	// Set given memory values
	for (std::vector<int> memData : initialState["ram"]) {
		cpu.mem->write(memData[0], memData[1]);
	}
}

bool checkCPU(std::string testName, nlohmann::json& finalState, GBCPU& cpu) {
	// Check IME
	if ((int)cpu.IME != finalState["ime"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect IME value.\n";
		std::cout << "Expected: " << (int)finalState["ime"] << " Received: " << (int)cpu.IME << std::endl;
		return false;
	}

	// Check CPU registers
	if (cpu.A != (byte)finalState["a"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect A register value.\n";
		std::cout << "Expected: " << (int)finalState["a"] << " Received: " << (int)cpu.A << std::endl;
		return false;
	}
	if (cpu.B != (byte)finalState["b"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect B register value.\n";
		std::cout << "Expected: " << (int)finalState["b"] << " Received: " << (int)cpu.B << std::endl;
		return false;
	}
	if (cpu.C != (byte)finalState["c"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect C register value.\n";
		std::cout << "Expected: " << (int)finalState["c"] << " Received: " << (int)cpu.C << std::endl;
		return false;
	}
	if (cpu.D != (byte)finalState["d"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect D register value.\n";
		std::cout << "Expected: " << (int)finalState["d"] << " Received: " << (int)cpu.D << std::endl;
		return false;
	}
	if (cpu.E != (byte)finalState["e"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect E register value.\n";
		std::cout << "Expected: " << (int)finalState["e"] << " Received: " << (int)cpu.E << std::endl;
		return false;
	}
	if (cpu.F != (byte)finalState["f"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect F register value.\n";
		std::cout << "Expected: " << (int)finalState["f"] << " Received: " << (int)cpu.F << std::endl;
		return false;
	}
	if (cpu.H != (byte)finalState["h"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect H register value.\n";
		std::cout << "Expected: " << (int)finalState["h"] << " Received: " << (int)cpu.H << std::endl;
		return false;
	}
	if (cpu.L != (byte)finalState["l"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect L register value.\n";
		std::cout << "Expected: " << (int)finalState["l"] << " Received: " << (int)cpu.L << std::endl;
		return false;
	}

	if (cpu.PC != (address)finalState["pc"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect PC register value.\n";
		std::cout << "Expected: " << (int)finalState["pc"] << " Received: " << (int)cpu.PC << std::endl;
		return false;
	}
	if (cpu.SP != (address)finalState["sp"]) {
		std::cout << "TEST: " << testName << " failed due to incorrect SP register value.\n";
		std::cout << "Expected: " << (int)finalState["sp"] << " Received: " << (int)cpu.SP << std::endl;
		return false;
	}

	// Check given memory values
	for (std::vector<int> memData : finalState["ram"]) {
		if (cpu.mem->read(memData[0]) != (byte)memData[1]) {
			std::cout << "TEST: " << testName << " failed due to incorrect value stored in memory address " << memData[0] << std::endl;
			return false;
		}
	}

	return true;
}

int runTest(std::string OPCode, GBCPU& cpu) {
	int numberFailed = 0;
	int numberPassed = 0;

	std::ifstream f("src/CPU/CPUTests/" + OPCode + ".json");
	nlohmann::json testData = nlohmann::json::parse(f);
	std::cout << "Testing OPCode: " << OPCode << std::endl;
	for (nlohmann::json test : testData) {
		// Set initial state of CPU
		initCPU(test["initial"], cpu);

		// Get number of expected cpu cycles
		int cycleCount = test["cycles"].size();

		// Run cpu for given number of cycles
		for (int i = 0; i < cycleCount; ++i) {
			cpu.update();
		}

		// Check final state agrees with test
		bool success = checkCPU(test["name"], test["final"], cpu);

		if (success) {
			++numberPassed;
		}
		else {
			++numberFailed;
		}
	}
	std::cout << "\n Tests Passed: " << numberPassed << std::endl;
	std::cout << "Tests Failed : " << numberFailed << std::endl << std::endl << std::endl;

	return numberPassed;
}

int testUnprefixedCodes(GBCPU* cpu) {
	int totalPassedTests = 0;

	totalPassedTests += runTest("00", *cpu);
	totalPassedTests += runTest("01", *cpu);
	totalPassedTests += runTest("02", *cpu);
	totalPassedTests += runTest("03", *cpu);
	totalPassedTests += runTest("04", *cpu);
	totalPassedTests += runTest("05", *cpu);
	totalPassedTests += runTest("06", *cpu);
	totalPassedTests += runTest("07", *cpu);
	totalPassedTests += runTest("08", *cpu);
	totalPassedTests += runTest("09", *cpu);
	totalPassedTests += runTest("0A", *cpu);
	totalPassedTests += runTest("0B", *cpu);
	totalPassedTests += runTest("0C", *cpu);
	totalPassedTests += runTest("0D", *cpu);
	totalPassedTests += runTest("0E", *cpu);
	totalPassedTests += runTest("0F", *cpu);

	totalPassedTests += runTest("10", *cpu);
	totalPassedTests += runTest("11", *cpu);
	totalPassedTests += runTest("12", *cpu);
	totalPassedTests += runTest("13", *cpu);
	totalPassedTests += runTest("14", *cpu);
	totalPassedTests += runTest("15", *cpu);
	totalPassedTests += runTest("16", *cpu);
	totalPassedTests += runTest("17", *cpu);
	totalPassedTests += runTest("18", *cpu);
	totalPassedTests += runTest("19", *cpu);
	totalPassedTests += runTest("1A", *cpu);
	totalPassedTests += runTest("1B", *cpu);
	totalPassedTests += runTest("1C", *cpu);
	totalPassedTests += runTest("1D", *cpu);
	totalPassedTests += runTest("1E", *cpu);
	totalPassedTests += runTest("1F", *cpu);

	totalPassedTests += runTest("20", *cpu);
	totalPassedTests += runTest("21", *cpu);
	totalPassedTests += runTest("22", *cpu);
	totalPassedTests += runTest("23", *cpu);
	totalPassedTests += runTest("24", *cpu);
	totalPassedTests += runTest("25", *cpu);
	totalPassedTests += runTest("26", *cpu);
	totalPassedTests += runTest("27", *cpu);
	totalPassedTests += runTest("28", *cpu);
	totalPassedTests += runTest("29", *cpu);
	totalPassedTests += runTest("2A", *cpu);
	totalPassedTests += runTest("2B", *cpu);
	totalPassedTests += runTest("2C", *cpu);
	totalPassedTests += runTest("2D", *cpu);
	totalPassedTests += runTest("2E", *cpu);
	totalPassedTests += runTest("2F", *cpu);

	totalPassedTests += runTest("30", *cpu);
	totalPassedTests += runTest("31", *cpu);
	totalPassedTests += runTest("32", *cpu);
	totalPassedTests += runTest("33", *cpu);
	totalPassedTests += runTest("34", *cpu);
	totalPassedTests += runTest("35", *cpu);
	totalPassedTests += runTest("36", *cpu);
	totalPassedTests += runTest("37", *cpu);
	totalPassedTests += runTest("38", *cpu);
	totalPassedTests += runTest("39", *cpu);
	totalPassedTests += runTest("3A", *cpu);
	totalPassedTests += runTest("3B", *cpu);
	totalPassedTests += runTest("3C", *cpu);
	totalPassedTests += runTest("3D", *cpu);
	totalPassedTests += runTest("3E", *cpu);
	totalPassedTests += runTest("3F", *cpu);

	totalPassedTests += runTest("40", *cpu);
	totalPassedTests += runTest("41", *cpu);
	totalPassedTests += runTest("42", *cpu);
	totalPassedTests += runTest("43", *cpu);
	totalPassedTests += runTest("44", *cpu);
	totalPassedTests += runTest("45", *cpu);
	totalPassedTests += runTest("46", *cpu);
	totalPassedTests += runTest("47", *cpu);
	totalPassedTests += runTest("48", *cpu);
	totalPassedTests += runTest("49", *cpu);
	totalPassedTests += runTest("4A", *cpu);
	totalPassedTests += runTest("4B", *cpu);
	totalPassedTests += runTest("4C", *cpu);
	totalPassedTests += runTest("4D", *cpu);
	totalPassedTests += runTest("4E", *cpu);
	totalPassedTests += runTest("4F", *cpu);

	totalPassedTests += runTest("50", *cpu);
	totalPassedTests += runTest("51", *cpu);
	totalPassedTests += runTest("52", *cpu);
	totalPassedTests += runTest("53", *cpu);
	totalPassedTests += runTest("54", *cpu);
	totalPassedTests += runTest("55", *cpu);
	totalPassedTests += runTest("56", *cpu);
	totalPassedTests += runTest("57", *cpu);
	totalPassedTests += runTest("58", *cpu);
	totalPassedTests += runTest("59", *cpu);
	totalPassedTests += runTest("5A", *cpu);
	totalPassedTests += runTest("5B", *cpu);
	totalPassedTests += runTest("5C", *cpu);
	totalPassedTests += runTest("5D", *cpu);
	totalPassedTests += runTest("5E", *cpu);
	totalPassedTests += runTest("5F", *cpu);

	totalPassedTests += runTest("60", *cpu);
	totalPassedTests += runTest("61", *cpu);
	totalPassedTests += runTest("62", *cpu);
	totalPassedTests += runTest("63", *cpu);
	totalPassedTests += runTest("64", *cpu);
	totalPassedTests += runTest("65", *cpu);
	totalPassedTests += runTest("66", *cpu);
	totalPassedTests += runTest("67", *cpu);
	totalPassedTests += runTest("68", *cpu);
	totalPassedTests += runTest("69", *cpu);
	totalPassedTests += runTest("6A", *cpu);
	totalPassedTests += runTest("6B", *cpu);
	totalPassedTests += runTest("6C", *cpu);
	totalPassedTests += runTest("6D", *cpu);
	totalPassedTests += runTest("6E", *cpu);
	totalPassedTests += runTest("6F", *cpu);

	totalPassedTests += runTest("70", *cpu);
	totalPassedTests += runTest("71", *cpu);
	totalPassedTests += runTest("72", *cpu);
	totalPassedTests += runTest("73", *cpu);
	totalPassedTests += runTest("74", *cpu);
	totalPassedTests += runTest("75", *cpu);
	totalPassedTests += runTest("76", *cpu);
	totalPassedTests += runTest("77", *cpu);
	totalPassedTests += runTest("78", *cpu);
	totalPassedTests += runTest("79", *cpu);
	totalPassedTests += runTest("7A", *cpu);
	totalPassedTests += runTest("7B", *cpu);
	totalPassedTests += runTest("7C", *cpu);
	totalPassedTests += runTest("7D", *cpu);
	totalPassedTests += runTest("7E", *cpu);
	totalPassedTests += runTest("7F", *cpu);

	totalPassedTests += runTest("80", *cpu);
	totalPassedTests += runTest("81", *cpu);
	totalPassedTests += runTest("82", *cpu);
	totalPassedTests += runTest("83", *cpu);
	totalPassedTests += runTest("84", *cpu);
	totalPassedTests += runTest("85", *cpu);
	totalPassedTests += runTest("86", *cpu);
	totalPassedTests += runTest("87", *cpu);
	totalPassedTests += runTest("88", *cpu);
	totalPassedTests += runTest("89", *cpu);
	totalPassedTests += runTest("8A", *cpu);
	totalPassedTests += runTest("8B", *cpu);
	totalPassedTests += runTest("8C", *cpu);
	totalPassedTests += runTest("8D", *cpu);
	totalPassedTests += runTest("8E", *cpu);
	totalPassedTests += runTest("8F", *cpu);

	totalPassedTests += runTest("90", *cpu);
	totalPassedTests += runTest("91", *cpu);
	totalPassedTests += runTest("92", *cpu);
	totalPassedTests += runTest("93", *cpu);
	totalPassedTests += runTest("94", *cpu);
	totalPassedTests += runTest("95", *cpu);
	totalPassedTests += runTest("96", *cpu);
	totalPassedTests += runTest("97", *cpu);
	totalPassedTests += runTest("98", *cpu);
	totalPassedTests += runTest("99", *cpu);
	totalPassedTests += runTest("9A", *cpu);
	totalPassedTests += runTest("9B", *cpu);
	totalPassedTests += runTest("9C", *cpu);
	totalPassedTests += runTest("9D", *cpu);
	totalPassedTests += runTest("9E", *cpu);
	totalPassedTests += runTest("9F", *cpu);

	totalPassedTests += runTest("A0", *cpu);
	totalPassedTests += runTest("A1", *cpu);
	totalPassedTests += runTest("A2", *cpu);
	totalPassedTests += runTest("A3", *cpu);
	totalPassedTests += runTest("A4", *cpu);
	totalPassedTests += runTest("A5", *cpu);
	totalPassedTests += runTest("A6", *cpu);
	totalPassedTests += runTest("A7", *cpu);
	totalPassedTests += runTest("A8", *cpu);
	totalPassedTests += runTest("A9", *cpu);
	totalPassedTests += runTest("AA", *cpu);
	totalPassedTests += runTest("AB", *cpu);
	totalPassedTests += runTest("AC", *cpu);
	totalPassedTests += runTest("AD", *cpu);
	totalPassedTests += runTest("AE", *cpu);
	totalPassedTests += runTest("AF", *cpu);

	totalPassedTests += runTest("B0", *cpu);
	totalPassedTests += runTest("B1", *cpu);
	totalPassedTests += runTest("B2", *cpu);
	totalPassedTests += runTest("B3", *cpu);
	totalPassedTests += runTest("B4", *cpu);
	totalPassedTests += runTest("B5", *cpu);
	totalPassedTests += runTest("B6", *cpu);
	totalPassedTests += runTest("B7", *cpu);
	totalPassedTests += runTest("B8", *cpu);
	totalPassedTests += runTest("B9", *cpu);
	totalPassedTests += runTest("BA", *cpu);
	totalPassedTests += runTest("BB", *cpu);
	totalPassedTests += runTest("BC", *cpu);
	totalPassedTests += runTest("BD", *cpu);
	totalPassedTests += runTest("BE", *cpu);
	totalPassedTests += runTest("BF", *cpu);

	totalPassedTests += runTest("C0", *cpu);
	totalPassedTests += runTest("C1", *cpu);
	totalPassedTests += runTest("C2", *cpu);
	totalPassedTests += runTest("C3", *cpu);
	totalPassedTests += runTest("C4", *cpu);
	totalPassedTests += runTest("C5", *cpu);
	totalPassedTests += runTest("C6", *cpu);
	totalPassedTests += runTest("C7", *cpu);
	totalPassedTests += runTest("C8", *cpu);
	totalPassedTests += runTest("C9", *cpu);
	totalPassedTests += runTest("CA", *cpu);
	totalPassedTests += runTest("CC", *cpu);
	totalPassedTests += runTest("CD", *cpu);
	totalPassedTests += runTest("CE", *cpu);
	totalPassedTests += runTest("CF", *cpu);

	totalPassedTests += runTest("D0", *cpu);
	totalPassedTests += runTest("D1", *cpu);
	totalPassedTests += runTest("D2", *cpu);
	totalPassedTests += runTest("D4", *cpu);
	totalPassedTests += runTest("D5", *cpu);
	totalPassedTests += runTest("D6", *cpu);
	totalPassedTests += runTest("D7", *cpu);
	totalPassedTests += runTest("D8", *cpu);
	totalPassedTests += runTest("D9", *cpu);
	totalPassedTests += runTest("DA", *cpu);
	totalPassedTests += runTest("DC", *cpu);
	totalPassedTests += runTest("DE", *cpu);
	totalPassedTests += runTest("DF", *cpu);

	totalPassedTests += runTest("E0", *cpu);
	totalPassedTests += runTest("E1", *cpu);
	totalPassedTests += runTest("E2", *cpu);
	totalPassedTests += runTest("E5", *cpu);
	totalPassedTests += runTest("E6", *cpu);
	totalPassedTests += runTest("E7", *cpu);
	totalPassedTests += runTest("E8", *cpu);
	totalPassedTests += runTest("E9", *cpu);
	totalPassedTests += runTest("EA", *cpu);
	totalPassedTests += runTest("EE", *cpu);
	totalPassedTests += runTest("EF", *cpu);

	totalPassedTests += runTest("F0", *cpu);
	totalPassedTests += runTest("F1", *cpu);
	totalPassedTests += runTest("F2", *cpu);
	totalPassedTests += runTest("F3", *cpu);
	totalPassedTests += runTest("F5", *cpu);
	totalPassedTests += runTest("F6", *cpu);
	totalPassedTests += runTest("F7", *cpu);
	totalPassedTests += runTest("F8", *cpu);
	totalPassedTests += runTest("F9", *cpu);
	totalPassedTests += runTest("FA", *cpu);
	totalPassedTests += runTest("FB", *cpu);
	totalPassedTests += runTest("FE", *cpu);
	totalPassedTests += runTest("FF", *cpu);

	return totalPassedTests;
}

int testPrefixedCodes(GBCPU* cpu) {
	int totalPassedTests = 0;

	totalPassedTests += runTest("cb 00", *cpu);
	totalPassedTests += runTest("cb 01", *cpu);
	totalPassedTests += runTest("cb 02", *cpu);
	totalPassedTests += runTest("cb 03", *cpu);
	totalPassedTests += runTest("cb 04", *cpu);
	totalPassedTests += runTest("cb 05", *cpu);
	totalPassedTests += runTest("cb 06", *cpu);
	totalPassedTests += runTest("cb 07", *cpu);
	totalPassedTests += runTest("cb 08", *cpu);
	totalPassedTests += runTest("cb 09", *cpu);
	totalPassedTests += runTest("cb 0A", *cpu);
	totalPassedTests += runTest("cb 0B", *cpu);
	totalPassedTests += runTest("cb 0C", *cpu);
	totalPassedTests += runTest("cb 0D", *cpu);
	totalPassedTests += runTest("cb 0E", *cpu);
	totalPassedTests += runTest("cb 0F", *cpu);

	totalPassedTests += runTest("cb 10", *cpu);
	totalPassedTests += runTest("cb 11", *cpu);
	totalPassedTests += runTest("cb 12", *cpu);
	totalPassedTests += runTest("cb 13", *cpu);
	totalPassedTests += runTest("cb 14", *cpu);
	totalPassedTests += runTest("cb 15", *cpu);
	totalPassedTests += runTest("cb 16", *cpu);
	totalPassedTests += runTest("cb 17", *cpu);
	totalPassedTests += runTest("cb 18", *cpu);
	totalPassedTests += runTest("cb 19", *cpu);
	totalPassedTests += runTest("cb 1A", *cpu);
	totalPassedTests += runTest("cb 1B", *cpu);
	totalPassedTests += runTest("cb 1C", *cpu);
	totalPassedTests += runTest("cb 1D", *cpu);
	totalPassedTests += runTest("cb 1E", *cpu);
	totalPassedTests += runTest("cb 1F", *cpu);

	totalPassedTests += runTest("cb 20", *cpu);
	totalPassedTests += runTest("cb 21", *cpu);
	totalPassedTests += runTest("cb 22", *cpu);
	totalPassedTests += runTest("cb 23", *cpu);
	totalPassedTests += runTest("cb 24", *cpu);
	totalPassedTests += runTest("cb 25", *cpu);
	totalPassedTests += runTest("cb 26", *cpu);
	totalPassedTests += runTest("cb 27", *cpu);
	totalPassedTests += runTest("cb 28", *cpu);
	totalPassedTests += runTest("cb 29", *cpu);
	totalPassedTests += runTest("cb 2A", *cpu);
	totalPassedTests += runTest("cb 2B", *cpu);
	totalPassedTests += runTest("cb 2C", *cpu);
	totalPassedTests += runTest("cb 2D", *cpu);
	totalPassedTests += runTest("cb 2E", *cpu);
	totalPassedTests += runTest("cb 2F", *cpu);

	totalPassedTests += runTest("cb 30", *cpu);
	totalPassedTests += runTest("cb 31", *cpu);
	totalPassedTests += runTest("cb 32", *cpu);
	totalPassedTests += runTest("cb 33", *cpu);
	totalPassedTests += runTest("cb 34", *cpu);
	totalPassedTests += runTest("cb 35", *cpu);
	totalPassedTests += runTest("cb 36", *cpu);
	totalPassedTests += runTest("cb 37", *cpu);
	totalPassedTests += runTest("cb 38", *cpu);
	totalPassedTests += runTest("cb 39", *cpu);
	totalPassedTests += runTest("cb 3A", *cpu);
	totalPassedTests += runTest("cb 3B", *cpu);
	totalPassedTests += runTest("cb 3C", *cpu);
	totalPassedTests += runTest("cb 3D", *cpu);
	totalPassedTests += runTest("cb 3E", *cpu);
	totalPassedTests += runTest("cb 3F", *cpu);

	totalPassedTests += runTest("cb 40", *cpu);
	totalPassedTests += runTest("cb 41", *cpu);
	totalPassedTests += runTest("cb 42", *cpu);
	totalPassedTests += runTest("cb 43", *cpu);
	totalPassedTests += runTest("cb 44", *cpu);
	totalPassedTests += runTest("cb 45", *cpu);
	totalPassedTests += runTest("cb 46", *cpu);
	totalPassedTests += runTest("cb 47", *cpu);
	totalPassedTests += runTest("cb 48", *cpu);
	totalPassedTests += runTest("cb 49", *cpu);
	totalPassedTests += runTest("cb 4A", *cpu);
	totalPassedTests += runTest("cb 4B", *cpu);
	totalPassedTests += runTest("cb 4C", *cpu);
	totalPassedTests += runTest("cb 4D", *cpu);
	totalPassedTests += runTest("cb 4E", *cpu);
	totalPassedTests += runTest("cb 4F", *cpu);

	totalPassedTests += runTest("cb 50", *cpu);
	totalPassedTests += runTest("cb 51", *cpu);
	totalPassedTests += runTest("cb 52", *cpu);
	totalPassedTests += runTest("cb 53", *cpu);
	totalPassedTests += runTest("cb 54", *cpu);
	totalPassedTests += runTest("cb 55", *cpu);
	totalPassedTests += runTest("cb 56", *cpu);
	totalPassedTests += runTest("cb 57", *cpu);
	totalPassedTests += runTest("cb 58", *cpu);
	totalPassedTests += runTest("cb 59", *cpu);
	totalPassedTests += runTest("cb 5A", *cpu);
	totalPassedTests += runTest("cb 5B", *cpu);
	totalPassedTests += runTest("cb 5C", *cpu);
	totalPassedTests += runTest("cb 5D", *cpu);
	totalPassedTests += runTest("cb 5E", *cpu);
	totalPassedTests += runTest("cb 5F", *cpu);

	totalPassedTests += runTest("cb 60", *cpu);
	totalPassedTests += runTest("cb 61", *cpu);
	totalPassedTests += runTest("cb 62", *cpu);
	totalPassedTests += runTest("cb 63", *cpu);
	totalPassedTests += runTest("cb 64", *cpu);
	totalPassedTests += runTest("cb 65", *cpu);
	totalPassedTests += runTest("cb 66", *cpu);
	totalPassedTests += runTest("cb 67", *cpu);
	totalPassedTests += runTest("cb 68", *cpu);
	totalPassedTests += runTest("cb 69", *cpu);
	totalPassedTests += runTest("cb 6A", *cpu);
	totalPassedTests += runTest("cb 6B", *cpu);
	totalPassedTests += runTest("cb 6C", *cpu);
	totalPassedTests += runTest("cb 6D", *cpu);
	totalPassedTests += runTest("cb 6E", *cpu);
	totalPassedTests += runTest("cb 6F", *cpu);

	totalPassedTests += runTest("cb 70", *cpu);
	totalPassedTests += runTest("cb 71", *cpu);
	totalPassedTests += runTest("cb 72", *cpu);
	totalPassedTests += runTest("cb 73", *cpu);
	totalPassedTests += runTest("cb 74", *cpu);
	totalPassedTests += runTest("cb 75", *cpu);
	totalPassedTests += runTest("cb 76", *cpu);
	totalPassedTests += runTest("cb 77", *cpu);
	totalPassedTests += runTest("cb 78", *cpu);
	totalPassedTests += runTest("cb 79", *cpu);
	totalPassedTests += runTest("cb 7A", *cpu);
	totalPassedTests += runTest("cb 7B", *cpu);
	totalPassedTests += runTest("cb 7C", *cpu);
	totalPassedTests += runTest("cb 7D", *cpu);
	totalPassedTests += runTest("cb 7E", *cpu);
	totalPassedTests += runTest("cb 7F", *cpu);

	totalPassedTests += runTest("cb 80", *cpu);
	totalPassedTests += runTest("cb 81", *cpu);
	totalPassedTests += runTest("cb 82", *cpu);
	totalPassedTests += runTest("cb 83", *cpu);
	totalPassedTests += runTest("cb 84", *cpu);
	totalPassedTests += runTest("cb 85", *cpu);
	totalPassedTests += runTest("cb 86", *cpu);
	totalPassedTests += runTest("cb 87", *cpu);
	totalPassedTests += runTest("cb 88", *cpu);
	totalPassedTests += runTest("cb 89", *cpu);
	totalPassedTests += runTest("cb 8A", *cpu);
	totalPassedTests += runTest("cb 8B", *cpu);
	totalPassedTests += runTest("cb 8C", *cpu);
	totalPassedTests += runTest("cb 8D", *cpu);
	totalPassedTests += runTest("cb 8E", *cpu);
	totalPassedTests += runTest("cb 8F", *cpu);

	totalPassedTests += runTest("cb 90", *cpu);
	totalPassedTests += runTest("cb 91", *cpu);
	totalPassedTests += runTest("cb 92", *cpu);
	totalPassedTests += runTest("cb 93", *cpu);
	totalPassedTests += runTest("cb 94", *cpu);
	totalPassedTests += runTest("cb 95", *cpu);
	totalPassedTests += runTest("cb 96", *cpu);
	totalPassedTests += runTest("cb 97", *cpu);
	totalPassedTests += runTest("cb 98", *cpu);
	totalPassedTests += runTest("cb 99", *cpu);
	totalPassedTests += runTest("cb 9A", *cpu);
	totalPassedTests += runTest("cb 9B", *cpu);
	totalPassedTests += runTest("cb 9C", *cpu);
	totalPassedTests += runTest("cb 9D", *cpu);
	totalPassedTests += runTest("cb 9E", *cpu);
	totalPassedTests += runTest("cb 9F", *cpu);

	totalPassedTests += runTest("cb A0", *cpu);
	totalPassedTests += runTest("cb A1", *cpu);
	totalPassedTests += runTest("cb A2", *cpu);
	totalPassedTests += runTest("cb A3", *cpu);
	totalPassedTests += runTest("cb A4", *cpu);
	totalPassedTests += runTest("cb A5", *cpu);
	totalPassedTests += runTest("cb A6", *cpu);
	totalPassedTests += runTest("cb A7", *cpu);
	totalPassedTests += runTest("cb A8", *cpu);
	totalPassedTests += runTest("cb A9", *cpu);
	totalPassedTests += runTest("cb AA", *cpu);
	totalPassedTests += runTest("cb AB", *cpu);
	totalPassedTests += runTest("cb AC", *cpu);
	totalPassedTests += runTest("cb AD", *cpu);
	totalPassedTests += runTest("cb AE", *cpu);
	totalPassedTests += runTest("cb AF", *cpu);

	totalPassedTests += runTest("cb B0", *cpu);
	totalPassedTests += runTest("cb B1", *cpu);
	totalPassedTests += runTest("cb B2", *cpu);
	totalPassedTests += runTest("cb B3", *cpu);
	totalPassedTests += runTest("cb B4", *cpu);
	totalPassedTests += runTest("cb B5", *cpu);
	totalPassedTests += runTest("cb B6", *cpu);
	totalPassedTests += runTest("cb B7", *cpu);
	totalPassedTests += runTest("cb B8", *cpu);
	totalPassedTests += runTest("cb B9", *cpu);
	totalPassedTests += runTest("cb BA", *cpu);
	totalPassedTests += runTest("cb BB", *cpu);
	totalPassedTests += runTest("cb BC", *cpu);
	totalPassedTests += runTest("cb BD", *cpu);
	totalPassedTests += runTest("cb BE", *cpu);
	totalPassedTests += runTest("cb BF", *cpu);

	totalPassedTests += runTest("cb C0", *cpu);
	totalPassedTests += runTest("cb C1", *cpu);
	totalPassedTests += runTest("cb C2", *cpu);
	totalPassedTests += runTest("cb C3", *cpu);
	totalPassedTests += runTest("cb C4", *cpu);
	totalPassedTests += runTest("cb C5", *cpu);
	totalPassedTests += runTest("cb C6", *cpu);
	totalPassedTests += runTest("cb C7", *cpu);
	totalPassedTests += runTest("cb C8", *cpu);
	totalPassedTests += runTest("cb C9", *cpu);
	totalPassedTests += runTest("cb CA", *cpu);
	totalPassedTests += runTest("cb CB", *cpu);
	totalPassedTests += runTest("cb CC", *cpu);
	totalPassedTests += runTest("cb CD", *cpu);
	totalPassedTests += runTest("cb CE", *cpu);
	totalPassedTests += runTest("cb CF", *cpu);

	totalPassedTests += runTest("cb D0", *cpu);
	totalPassedTests += runTest("cb D1", *cpu);
	totalPassedTests += runTest("cb D2", *cpu);
	totalPassedTests += runTest("cb D3", *cpu);
	totalPassedTests += runTest("cb D4", *cpu);
	totalPassedTests += runTest("cb D5", *cpu);
	totalPassedTests += runTest("cb D6", *cpu);
	totalPassedTests += runTest("cb D7", *cpu);
	totalPassedTests += runTest("cb D8", *cpu);
	totalPassedTests += runTest("cb D9", *cpu);
	totalPassedTests += runTest("cb DA", *cpu);
	totalPassedTests += runTest("cb DB", *cpu);
	totalPassedTests += runTest("cb DC", *cpu);
	totalPassedTests += runTest("cb DD", *cpu);
	totalPassedTests += runTest("cb DE", *cpu);
	totalPassedTests += runTest("cb DF", *cpu);

	totalPassedTests += runTest("cb E0", *cpu);
	totalPassedTests += runTest("cb E1", *cpu);
	totalPassedTests += runTest("cb E2", *cpu);
	totalPassedTests += runTest("cb E3", *cpu);
	totalPassedTests += runTest("cb E4", *cpu);
	totalPassedTests += runTest("cb E5", *cpu);
	totalPassedTests += runTest("cb E6", *cpu);
	totalPassedTests += runTest("cb E7", *cpu);
	totalPassedTests += runTest("cb E8", *cpu);
	totalPassedTests += runTest("cb E9", *cpu);
	totalPassedTests += runTest("cb EA", *cpu);
	totalPassedTests += runTest("cb EB", *cpu);
	totalPassedTests += runTest("cb EC", *cpu);
	totalPassedTests += runTest("cb ED", *cpu);
	totalPassedTests += runTest("cb EE", *cpu);
	totalPassedTests += runTest("cb EF", *cpu);

	totalPassedTests += runTest("cb F0", *cpu);
	totalPassedTests += runTest("cb F1", *cpu);
	totalPassedTests += runTest("cb F2", *cpu);
	totalPassedTests += runTest("cb F3", *cpu);
	totalPassedTests += runTest("cb F4", *cpu);
	totalPassedTests += runTest("cb F5", *cpu);
	totalPassedTests += runTest("cb F6", *cpu);
	totalPassedTests += runTest("cb F7", *cpu);
	totalPassedTests += runTest("cb F8", *cpu);
	totalPassedTests += runTest("cb F9", *cpu);
	totalPassedTests += runTest("cb FA", *cpu);
	totalPassedTests += runTest("cb FB", *cpu);
	totalPassedTests += runTest("cb FC", *cpu);
	totalPassedTests += runTest("cb FD", *cpu);
	totalPassedTests += runTest("cb FE", *cpu);
	totalPassedTests += runTest("cb FF", *cpu);

	return totalPassedTests;
}