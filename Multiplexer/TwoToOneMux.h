
#pragma once

#include "../Gates/AndGate.h"
#include "../Gates/OrGate.h"
#include "../Gates/NotGate.h"
#include "../Gates/ConstantGate.h"

struct TwoToOneMuxResult {
    bool output;
};

class TwoToOneMux {
public:
    TwoToOneMux(
        bool in1,
        bool in2,
        bool select
    )
        : input1(in1),
          input2(in2),
          selectLine(select) {}

    TwoToOneMuxResult evaluate() {

        ConstantGate in1(input1);
        ConstantGate in2(input2);
        ConstantGate select(selectLine);

        NotGate notSelect(&select);
        AndGate and1(&in1, &notSelect);

        AndGate and2(&in2, &select);
        OrGate orGate(&and1, &and2);

        return {orGate.evaluate()};
    }

private:
    bool input1;
    bool input2;
    bool selectLine;
};
