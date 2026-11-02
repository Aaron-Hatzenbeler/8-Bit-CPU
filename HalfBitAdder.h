#pragma once

#include "Gate.h"
#include "AndGate.h"
#include "XORGate.h"

struct HalfBitAdderResult {
    bool sum;
    bool carry;
};

class HalfBitAdder {
    public:
        HalfBitAdderResult evaluate() {
            bool sum = XORGate(input1, input2).evaluate();
            bool carry = AndGate(input1, input2).evaluate();
            return {sum, carry};
        }

        HalfBitAdder(Gate* in1, Gate* in2) : input1(in1), input2(in2) {}

    private:
        Gate* input1;
        Gate* input2;
};