#pragma once

class Gate {
    public:
        virtual bool evaluate() = 0;
        virtual ~Gate() = default;
};