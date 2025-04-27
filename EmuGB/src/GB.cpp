#include "GB.h"
#include "CPU/CPUTests.h"

void GB::update(TileMap* tileMap) { 
	CPU.update();

	Mem.update();

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

	// Update inputs
	controller.update(&Mem);

	
}

void GB::runTests() {
	int totalPassedTests = 0;

	totalPassedTests += testUnprefixedCodes(&CPU);
	totalPassedTests += testPrefixedCodes(&CPU);

	std::cout << "TOTAL TESTS PASSED: " << totalPassedTests << std::endl;
}