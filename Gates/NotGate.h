#pragma once

#include "Gate.h"

class NotGate : public Gate {
    public:
        bool evaluate() override {
            return !input->evaluate();
        }

        NotGate(Gate* in) : input(in) {}

    private:
        Gate* input;
};