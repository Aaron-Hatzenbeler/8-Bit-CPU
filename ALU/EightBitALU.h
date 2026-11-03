
#pragma once

#include <cstdint>
#include <cstdio>

#include "../Multiplexer/EightBitMux.h"
#include "EightBitAND.h"
#include "EightBitOR.h"
#include "../Arithmetic/EightBitAddSub.h"

struct EightBitALUResult {
    uint8_t result;
    bool carry;
};

class EightBitALU {
public:
    EightBitALU(uint8_t a, uint8_t b, uint8_t opcode)
        : inputA(a), inputB(b), opcode(opcode) {}

    EightBitALUResult evaluate() {
        if (opcode > 0b011) {
            std::printf(
                "Unsupported opcode: %u\n",
                static_cast<unsigned>(opcode)
            );
            return {0, false};
        }

        // Extract opcode selection bits
        bool select0 = opcode & 1U;
        bool select1 = (opcode >> 1) & 1U;

        // Logic circuits
        EightBitAND andCircuit(inputA, inputB);
        EightBitOR orCircuit(inputA, inputB);

        uint8_t andResult = andCircuit.evaluate().output;
        uint8_t orResult = orCircuit.evaluate().output;

        // Select AND or OR
        EightBitMux logicMux(
            andResult,
            orResult,
            select0
        );

        uint8_t logicResult = logicMux.evaluate().output;

        // One arithmetic circuit handles ADD and SUB
        EightBitAddSub arithmeticCircuit(
            inputA,
            inputB,
            select0
        );

        EightBitAddSubResult arithmeticResult =
            arithmeticCircuit.evaluate();

        // Select logic or arithmetic
        EightBitMux resultMux(
            logicResult,
            arithmeticResult.result,
            select1
        );

        uint8_t result = resultMux.evaluate().output;

        // Only arithmetic instructions expose carry
        bool carry = select1 && arithmeticResult.carry;

        return {result, carry};
    }

private:
    uint8_t inputA;
    uint8_t inputB;
    uint8_t opcode;
};
