#pragma once

#include "Gate.h"

class OrGate : public Gate {
    public:
        bool evaluate() override {
            return input1->evaluate() || input2->evaluate();
        }

        OrGate(Gate* in1, Gate* in2) : input1(in1), input2(in2) {}

    private:
        Gate* input1;
        Gate* input2;
};