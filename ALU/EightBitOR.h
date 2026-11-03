
#pragma once

#include <cstdint>

#include "../Gates/AndGate.h"
#include "../Gates/OrGate.h"
#include "../Gates/ConstantGate.h"

struct EightBitORResult {
    uint8_t input1;
    uint8_t input2;
    uint8_t output;
};

class EightBitOR {
public:
    EightBitOR(uint8_t in1, uint8_t in2)
        : input1(in1), input2(in2) {}

    EightBitORResult evaluate() {
        uint8_t output = 0;

        for (int i = 0; i < 8; i++) {
            bool bitA = (input1 >> i) & 1U;
            bool bitB = (input2 >> i) & 1U;

            ConstantGate in1(bitA);
            ConstantGate in2(bitB);

            OrGate orGate(&in1, &in2);

            bool orOutput = orGate.evaluate();

            output |= static_cast<uint8_t>(
                static_cast<uint8_t>(orOutput) << i
            );
        }

        return {input1, input2, output};
    }

private:
    uint8_t input1;
    uint8_t input2;
};
