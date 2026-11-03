
#pragma once

#include <cstdint>

#include "../Gates/AndGate.h"
#include "../Gates/ConstantGate.h"

struct EightBitANDResult {
    uint8_t input1;
    uint8_t input2;
    uint8_t output;
};

class EightBitAND {
public:
    EightBitAND(uint8_t in1, uint8_t in2)
        : input1(in1), input2(in2) {}

    EightBitANDResult evaluate() {
        uint8_t output = 0;

        for (int i = 0; i < 8; i++) {
            bool bitA = (input1 >> i) & 1U;
            bool bitB = (input2 >> i) & 1U;

            // Convert bool inputs into gate objects.
            ConstantGate in1(bitA);
            ConstantGate in2(bitB);

            // Construct the AND gate using pointers.
            AndGate andGate(&in1, &in2);

            bool andOutput = andGate.evaluate();

            output |= static_cast<uint8_t>(
                static_cast<uint8_t>(andOutput) << i
            );
        }

        return {input1, input2, output};
    }

private:
    uint8_t input1;
    uint8_t input2;
};
