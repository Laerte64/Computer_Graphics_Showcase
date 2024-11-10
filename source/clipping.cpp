#include "clipping.hpp"

std::optional<std::pair<Vec, Vec>> Clipping::clip(const Vec& p1, const Vec& p2) {
    auto reg1 = clipReg(p1);
    auto reg2 = clipReg(p2);

    std::pair<Vec, Vec> result = {Vec(p1), Vec(p2)};
    for (int filter = 0b11; filter < 0b1000000; filter <<= 2)
    {
        auto _reg1 = filter & reg1;
        auto _reg2 = filter & reg2;

        if ((_reg1 | _reg2) == 0) // Both Inside
            continue;
        if ((_reg1 ^ _reg2) == 0) // Both in the same Region
            return std::nullopt;

        result.first = clipSide(result.first, result.second, Side(_reg1));
        result.second = clipSide(result.second, result.first, Side(_reg2));
    }
    return result;
}

int Clipping::clipReg(const Vec& p) {
    int code = int(Side::Inside);
    
    if (p.x < -1) code |= int(Side::Left);
    else 
    if (p.x >  1) code |= int(Side::Right);
    
    if (p.y < -1) code |= int(Side::Bottom);
    else 
    if (p.y >  1) code |= int(Side::Top);
    
    if (p.z < -1) code |= int(Side::Near);
    else 
    if (p.z >  1) code |= int(Side::Far);
    
    return code;
}

Vec Clipping::clipSide(const Vec& p1, const Vec& p2, Side side) {
    switch (side) {
    case Side::Left:
        return Vec(
            -1,
            p1.y + (-1 - p1.x) * (p2.y - p1.y) / (p2.x - p1.x),
            p1.z + (-1 - p1.x) * (p2.z - p1.z) / (p2.x - p1.x)
        );
    case Side::Right:
        return Vec(
            1,
            p1.y + (1 - p1.x) * (p2.y - p1.y) / (p2.x - p1.x),
            p1.z + (1 - p1.x) * (p2.z - p1.z) / (p2.x - p1.x)
        );
    case Side::Bottom:
        return Vec(
            p1.x + (-1 - p1.y) * (p2.x - p1.x) / (p2.y - p1.y),
            -1,
            p1.z + (-1 - p1.y) * (p2.z - p1.z) / (p2.y - p1.y)
        );
    case Side::Top:
        return Vec(
            p1.x + (1 - p1.y) * (p2.x - p1.x) / (p2.y - p1.y),
            1,
            p1.z + (1 - p1.y) * (p2.z - p1.z) / (p2.y - p1.y)
        );
    case Side::Near:
        return Vec(
            p1.x + (-1 - p1.z) * (p2.x - p1.x) / (p2.z - p1.z),
            p1.y + (-1 - p1.z) * (p2.y - p1.y) / (p2.z - p1.z),
            -1
        );
    case Side::Far:
        return Vec(
            p1.x + (1 - p1.z) * (p2.x - p1.x) / (p2.z - p1.z),
            p1.y + (1 - p1.z) * (p2.y - p1.y) / (p2.z - p1.z),
            1
        );
    default:
        return Vec(p1);
    }
}