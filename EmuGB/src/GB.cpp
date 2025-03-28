#include "GB.h"
#include "CPU/CPUTests.h"

void GB::update(TileMap* tileMap) { 
	// Update inputs
	controller.update(&Mem);

	// Check for interrupts
	interruptHandler.update();

	// PPU updates 4 times for each CPU Update
	PPU.update(tileMap);
	timer.update();

	PPU.update(tileMap);
	timer.update();

	PPU.update(tileMap);
	timer.update();

	PPU.update(tileMap);
	timer.update();

	CPU.update();
}

void GB::runTests() {
	int totalPassedTests = 0;

	totalPassedTests += testUnprefixedCodes(&CPU);
	totalPassedTests += testPrefixedCodes(&CPU);

	std::cout << "TOTAL TESTS PASSED: " << totalPassedTests << std::endl;
}