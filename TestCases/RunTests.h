#include "TestAdders.h"

bool runAllAdderTests() {
    bool allPassed = true;

    if (!SmokeScreen_EightBitAdder()) {
        printf("SmokeScreen_EightBitAdder failed!\n");
        allPassed = false;
    }

    if (!ExhaustiveTest_EightBitAdder()) {
        printf("ExhaustiveTest_EightBitAdder failed!\n");
        allPassed = false;
    }

    if (!ExhaustiveTest_EightBitAddSub()) {
        printf("ExhaustiveTest_EightBitAddSub failed!\n");
        allPassed = false;
    }

    printf("All adder tests completed.\n");

    return allPassed;
}