#pragma once
#include <cstdint>
#include <stdio.h>

#include "../Multiplexer/TwoToOneMux.h"
#include "../Multiplexer/EightBitMux.h"

bool ExhaustiveTest_TwoToOneMux() {

    int passed = 0;

    for (int a = 0; a < 2; ++a) {
        for (int b = 0; b < 2; ++b) {
            for (int select = 0; select < 2; ++select) {

                TwoToOneMux mux(
                    a != 0,
                    b != 0,
                    select != 0
                );

                TwoToOneMuxResult result = mux.evaluate();

                bool expected = select ? b : a;

                if (result.output != expected) {
                    printf(
                        "FAILED: A=%d B=%d S=%d\n"
                        "Expected: %d\n"
                        "Actual:   %d\n",
                        a, b, select,
                        static_cast<int>(expected),
                        static_cast<int>(result.output)
                    );

                    return false;
                }

                ++passed;
            }
        }
    }

    printf("Passed all %d combinations!\n", passed);
    return true;
}

bool ExhaustiveTest_EightBitMux() {
    int passed = 0;

    for (int a = 0; a < 256; ++a) {
        for (int b = 0; b < 256; ++b) {
            for (int select = 0; select < 2; ++select) {

                EightBitMux mux(
                    static_cast<uint8_t>(a),
                    static_cast<uint8_t>(b),
                    select != 0
                );

                EightBitMuxResult result = mux.evaluate();

                uint8_t expected = select ? static_cast<uint8_t>(b) : static_cast<uint8_t>(a);

                if (result.output != expected) {
                    printf(
                        "FAILED: A=%d B=%d S=%d\n"
                        "Expected: %u\n"
                        "Actual:   %u\n",
                        a, b, select,
                        static_cast<unsigned>(expected),
                        static_cast<unsigned>(result.output)
                    );

                    return false;
                }

                ++passed;
            }
        }
    }

    printf("Passed all %d combinations!\n", passed);
    return true;
}