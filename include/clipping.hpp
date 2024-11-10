#pragma once

#include "vec.hpp"
#include <cmath>
#include <optional>

class Clipping {
public:
    static std::optional<std::pair<Vec, Vec>> clip(const Vec& p1, const Vec& p2);

private:
    enum class Side {
        Inside  = 0b000000,
        Left    = 0b000001,
        Right   = 0b000010,
        Bottom  = 0b000100,
        Top     = 0b001000,
        Near    = 0b010000,
        Far     = 0b100000
    };

    static int clipReg(const Vec& p);
    static Vec clipSide(const Vec& p1, const Vec& p2, Side side);
};
