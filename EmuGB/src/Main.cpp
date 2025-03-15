#include "Memory.h"
#include "CPU/CPU.h"
#include "CPU/CPUTests.h"

#include <iostream>
#include <vector>

int main() {
	GBCPU* testCPU = new GBCPU;

	int totalPassedTests = 0;

	totalPassedTests += testUnprefixedCodes(testCPU);
	totalPassedTests += testPrefixedCodes(testCPU);

	std::cout << "TOTAL TESTS PASSED: " << totalPassedTests << std::endl;
}