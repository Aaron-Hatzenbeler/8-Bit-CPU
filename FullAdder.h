#pragma once

#include "AndGate.h"
#include "XORGate.h"
#include "HalfBitAdder.h"

struct FullAdderResult {
    bool sum;
    bool carry;

};

class FullAdder {
    public: 
        FullAdderResult evaluate() {

            HalfBitAdder halfAdder1(input1, input2);
            HalfBitAdderResult halfAdder1Result = halfAdder1.evaluate();

            HalfBitAdder halfAdder2(new ConstantGate(halfAdder1Result.sum), carryInput);
            HalfBitAdderResult halfAdder2Result = halfAdder2.evaluate();

            bool finalCarry = halfAdder1Result.carry || halfAdder2Result.carry;
            return {halfAdder2Result.sum, finalCarry};
        }

        FullAdder(Gate* in1, Gate* in2, Gate* carryIn) : input1(in1), input2(in2), carryInput(carryIn) {}

    private:
        Gate* input1;
        Gate* input2;
        Gate* carryInput;
};