#pragma once
#include "CPU.h"

// Code for running SM83 per-instruction CPU tests (https://github.com/SingleStepTests/sm83)
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

// Sets the initial state of a CPU as defined by a test
void initCPU(nlohmann::json& initialState, GBCPU& cpu);

// Checks the final state of a CPU as defined by a test
bool checkCPU(std::string testName, nlohmann::json& finalState, GBCPU& cpu);

// Runs all tests for a given OPCode and returns the number of passed tests
int runTest(std::string OPCode, GBCPU& cpu);

// Runs tests for all 244 non-prefixed OPCodes and returns total number of passed tests
int testUnprefixedCodes(GBCPU* cpu);

// Runs test for all 256 prefixed OPCodes
int testPrefixedCodes(GBCPU* cpu);