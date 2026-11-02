#pragma once

#include "Gate.h"

class ConstantGate : public Gate {
    private:
        bool value;
    public:
        ConstantGate(bool value) : value(value) {}
        bool evaluate() override {
            return value;
        }
};