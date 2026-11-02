#pragma once
#include <cstdint>

#include "TwoToOneMux.h"

struct EightBitMuxResult {
    uint8_t output;
};

class EightBitMux {
public:
    EightBitMux(uint8_t in1, uint8_t in2, bool select) 
        : input1(in1),
          input2(in2),
          selectLine(select) {}

    EightBitMuxResult evaluate() {
        uint8_t output = 0;

        for (int i = 0; i < 8; ++i) {
            bool bitA = (input1 >> i) & 1U;
            bool bitB = (input2 >> i) & 1U;

            TwoToOneMux mux(bitA, bitB, selectLine);
            bool muxOutput = mux.evaluate().output;

            output |= static_cast<uint8_t>(static_cast<uint8_t>(muxOutput) << i);
        }

        return {output};
    }

private:
    uint8_t input1;
    uint8_t input2;
    bool selectLine;
};