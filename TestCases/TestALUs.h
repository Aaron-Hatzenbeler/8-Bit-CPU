#pragma once
#include <cstdint>
#include <stdio.h>

#include "../ALU/EightBitAND.h"
#include "../ALU/EightBitOR.h"


bool ExhaustiveTest_EightBitAND() {
    int passed = 0;

    for (int a = 0; a < 256; ++a) {
        for (int b = 0; b < 256; ++b) {

            EightBitAND circuit(
                static_cast<uint8_t>(a),
                static_cast<uint8_t>(b)
            );

            EightBitANDResult result = circuit.evaluate();

            uint8_t expected =
                static_cast<uint8_t>(a & b);

            if (result.output != expected) {
                printf(
                    "FAILED: %d AND %d\n"
                    "Expected: %u\n"
                    "Actual:   %u\n",
                    a, b,
                    static_cast<unsigned>(expected),
                    static_cast<unsigned>(result.output)
                );

                return false;
            }

            ++passed;
        }
    }

    printf("Passed all %d combinations!\n", passed);
    return true;
}


bool ExhaustiveTest_EightBitOR() {
    int passed = 0;

    for (int a = 0; a < 256; ++a) {
        for (int b = 0; b < 256; ++b) {

            EightBitOR circuit(
                static_cast<uint8_t>(a),
                static_cast<uint8_t>(b)
            );

            EightBitORResult result = circuit.evaluate();

            uint8_t expected =
                static_cast<uint8_t>(a | b);

            if (result.output != expected) {
                printf(
                    "FAILED: %d OR %d\n"
                    "Expected: %u\n"
                    "Actual:   %u\n",
                    a, b,
                    static_cast<unsigned>(expected),
                    static_cast<unsigned>(result.output)
                );

                return false;
            }

            ++passed;
        }
    }

    printf("Passed all %d combinations!\n", passed);
    return true;
}
