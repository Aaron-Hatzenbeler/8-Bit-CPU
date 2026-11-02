#pragma once

#include <cstdint>

#include "ConstantGate.h"

#include "FullAdder.h"

#include "AndGate.h"
#include "XORGate.h"

struct EightBitAdderResult {
    uint8_t sum;
    bool carry;
};

class EightBitAdder {
    public:

        EightBitAdder(uint8_t in1, uint8_t in2, bool carryIn) : input1(in1), input2(in2), carryInput(carryIn) {}

        EightBitAdderResult evaluate() {
            uint8_t sum = 0;
            bool carry = carryInput;

            for (int i = 0; i < 8; i++) {
                bool bitA = (input1 >> i) & 1U;
                bool bitB = (input2 >> i) & 1U;

                ConstantGate in1(bitA);
                ConstantGate in2(bitB);
                ConstantGate carryIn(carry);

                FullAdder fullAdder(
                    &in1,
                    &in2,
                    &carryIn
                );

                FullAdderResult stage = fullAdder.evaluate();

                sum |= static_cast<uint8_t>(
                    static_cast<uint8_t>(stage.sum) << i
                );

                carry = stage.carry;
            }

            return {sum, carry};
        }

    private:
        uint8_t input1;
        uint8_t input2;
        bool carryInput;
};