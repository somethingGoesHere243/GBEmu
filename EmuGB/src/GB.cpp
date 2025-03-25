#include "GB.h"
#include "CPU/CPUTests.h"

void GB::update() { 
	// PPU updates 4 times for each CPU Update
	CPU.update();
	PPU.update();
	PPU.update();
	PPU.update();
	PPU.update();
}

void GB::runTests() {
	int totalPassedTests = 0;

	totalPassedTests += testUnprefixedCodes(&CPU);
	totalPassedTests += testPrefixedCodes(&CPU);

	std::cout << "TOTAL TESTS PASSED: " << totalPassedTests << std::endl;
}