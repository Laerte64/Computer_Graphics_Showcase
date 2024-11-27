#pragma once

#include "vec.hpp"
#include <cmath>
#include <optional>

class Clipping {
public:
    static std::pair<Vec, Vec> corners;
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

    static std::optional<std::pair<Vec, Vec>> clipX(const Vec& p1, const Vec& p2);
    static std::optional<std::pair<Vec, Vec>> clipY(const Vec& p1, const Vec& p2);
    static std::optional<std::pair<Vec, Vec>> clipZ(const Vec& p1, const Vec& p2);
    static Vec clipSide(const Vec& p1, const Vec& p2, Side side);
};
