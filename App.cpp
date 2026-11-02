#include "Gates.h"

#include <stdio.h>

struct inputs 
{
    uint8_t input1;
    uint8_t input2;
    bool carryIn;
};

struct outputs 
{
    uint8_t sum;
    bool carryOut;
};

bool SmokeScreen_EightBitAdder() {
    inputs testInputs[] = {
        {225, 1, false},
        {255, 1, false},
        {127, 1, false},
        {255, 255, false},
        {255, 255, true},
        {0, 0, 1}
    };

    outputs expectedOutputs[] = {
        {226, false},
        {0, true},
        {128, false},
        {254, true},
        {255, true},
        {1, false}
    };

    for (int i = 0; i < sizeof(testInputs) / sizeof(testInputs[0]); i++) {
        EightBitAdder adder(testInputs[i].input1, testInputs[i].input2, testInputs[i].carryIn);
        EightBitAdderResult result = adder.evaluate();

        if (result.sum != expectedOutputs[i].sum || result.carry != expectedOutputs[i].carryOut) {
            printf("Test %d failed: Expected sum %d, carry %d but got sum %d, carry %d\n", 
                i + 1, 
                expectedOutputs[i].sum, 
                expectedOutputs[i].carryOut, 
                result.sum, 
                result.carry);
            return false;
        }
    }
    return true;
}

bool ExhaustiveTest_EightBitAdder() {
    for (int a = 0; a < 256; ++a) {
        for (int b = 0; b < 256; ++b) {
            for (int carryIn = 0; carryIn < 2; ++carryIn) {

                EightBitAdder adder(
                    static_cast<uint8_t>(a),
                    static_cast<uint8_t>(b),
                    carryIn != 0
                );

                EightBitAdderResult result = adder.evaluate();

                // Use wider arithmetic as the reference.
                int expected = a + b + carryIn;

                uint8_t expectedSum =
                    static_cast<uint8_t>(expected & 0xFF);

                bool expectedCarry = expected > 255;

                if (result.sum != expectedSum ||
                    result.carry != expectedCarry) {

                    printf(
                        "FAILED: %d + %d + %d\n"
                        "Expected: sum=%u, carry=%d\n"
                        "Actual:   sum=%u, carry=%d\n",
                        a, b, carryIn,
                        static_cast<unsigned>(expectedSum),
                        static_cast<int>(expectedCarry),
                        static_cast<unsigned>(result.sum),
                        static_cast<int>(result.carry)
                    );

                    return false;
                }
            }
        }
    }

    printf("Passed all 131072 combinations!\n");
    return true;
}

int main() {

    
    if (SmokeScreen_EightBitAdder()) {
        printf("All tests passed!\n");
    } else {
        printf("Some tests failed.\n");
    }

    if (ExhaustiveTest_EightBitAdder()) {
        printf("All tests passed!\n");
    } else {
        printf("Some tests failed.\n");
    }

    return 0;
}