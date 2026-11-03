#pragma once
#include <cstdint>
#include <stdio.h>

#include "../ALU/EightBitAND.h"
#include "../ALU/EightBitOR.h"
#include "../ALU/EightBitALU.h"


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


bool ExhaustiveTest_EightBitALU() {
    int passed = 0;

    for (int opcode = 0; opcode <= 0b011; ++opcode) {
        for (int a = 0; a < 256; ++a) {
            for (int b = 0; b < 256; ++b) {

                EightBitALU alu(
                    static_cast<uint8_t>(a),
                    static_cast<uint8_t>(b),
                    static_cast<uint8_t>(opcode)
                );

                EightBitALUResult result = alu.evaluate();

                uint8_t expected = 0;
                bool expectedCarry = false;

                switch (opcode) {
                    case 0b000:
                        expected = static_cast<uint8_t>(a & b);
                        break;

                    case 0b001:
                        expected = static_cast<uint8_t>(a | b);
                        break;

                    case 0b010: {
                        int sum = a + b;
                        expected = static_cast<uint8_t>(sum);
                        expectedCarry = sum > 255;
                        break;
                    }
                    case 0b011: { // SUBTRACT
                        expected = static_cast<uint8_t>(a - b);
                        expectedCarry = a >= b;
                        break;
                    }
                }

                if (result.result != expected ||
                    result.carry != expectedCarry) {

                    printf(
                        "ALU FAILED: opcode=%d A=%d B=%d\n"
                        "Expected: result=%u carry=%d\n"
                        "Actual:   result=%u carry=%d\n",
                        opcode, a, b,
                        static_cast<unsigned>(expected),
                        expectedCarry,
                        static_cast<unsigned>(result.result),
                        result.carry
                    );

                    return false;
                }

                ++passed;
            }
        }
    }

    printf("ALU passed all %d combinations!\n", passed);
    return true;
}
