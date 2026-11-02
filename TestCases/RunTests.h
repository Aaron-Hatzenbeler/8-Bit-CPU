#pragma once

#include "TestAdders.h"
#include "TestMutiplexers.h"

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

bool runAllMuxTests() {
    bool allPassed = true;

    if (!ExhaustiveTest_TwoToOneMux()) {
        printf("ExhaustiveTest_TwoToOneMux failed!\n");
        allPassed = false;
    }

    if (!ExhaustiveTest_EightBitMux()) {
        printf("ExhaustiveTest_EightBitMux failed!\n");
        allPassed = false;
    }

    printf("All multiplexer tests completed.\n");

    return allPassed;
}





bool runAllTests() {
    bool allPassed = true;

    if (!runAllAdderTests()) {
        allPassed = false;
    }

    if (!runAllMuxTests()) {
        allPassed = false;
    }

    return allPassed;
}