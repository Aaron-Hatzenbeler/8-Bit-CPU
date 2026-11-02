
#pragma once

#include <cstdint>

#include "../Gates/ConstantGate.h"
#include "../Gates/XORGate.h"

#include "EightBitAdder.h"

struct EightBitAddSubResult {
    uint8_t result;
    bool carry;
};

class EightBitAddSub {
public:
    EightBitAddSub(
        uint8_t in1,
        uint8_t in2,
        bool subtract
    )
        : input1(in1),
          input2(in2),
          subtractMode(subtract) {}

    EightBitAddSubResult evaluate() {

        uint8_t modifiedB = 0;

        // Conditionally invert each bit of B.
        for (int i = 0; i < 8; i++) {

            bool bitB = (input2 >> i) & 1U;

            ConstantGate bGate(bitB);
            ConstantGate subGate(subtractMode);

            XORGate xorGate(&bGate, &subGate);

            bool output = xorGate.evaluate();

            modifiedB |= static_cast<uint8_t>(
                static_cast<uint8_t>(output) << i
            );
        }

        // Reuse your existing 8-bit adder.
        EightBitAdder adder(
            input1,
            modifiedB,
            subtractMode
        );

        EightBitAdderResult result = adder.evaluate();

        return {
            result.sum,
            result.carry
        };
    }

private:
    uint8_t input1;
    uint8_t input2;
    bool subtractMode;
};
