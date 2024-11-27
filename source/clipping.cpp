#include "clipping.hpp"

std::pair<Vec, Vec> Clipping::corners = {Vec(-1, -1, -1), Vec(1, 1, 1)};

std::optional<std::pair<Vec, Vec>> Clipping::clip(const Vec& p1, const Vec& p2) {
    std::optional<std::pair<Vec, Vec>> result = {{p1, p2}};
    result = clipX(result.value().first, result.value().second);
    if (!result.has_value())
        return std::nullopt;
    result = clipY(result.value().first, result.value().second);
    if (!result.has_value())
        return std::nullopt;
    result = clipZ(result.value().first, result.value().second);
    return result;
}

std::optional<std::pair<Vec, Vec>> Clipping::clipX(const Vec &p1, const Vec &p2)
{
    Side reg1 = 
        p1.x < corners.first.x ? 
            Side::Left :
        p1.x > corners.second.x ? 
            Side::Right :
        Side::Inside;
    Side reg2 = 
        p2.x < corners.first.x ? 
            Side::Left :
        p2.x > corners.second.x ? 
            Side::Right :
        Side::Inside;
    if ((int(reg1) | int(reg2)) == 0)
        return {{p1, p2}};
    if ((int(reg1) ^ int(reg2)) == 0)
        return std::nullopt;
    std::pair<Vec, Vec> result = {{clipSide(p1, p2, reg1)}, {clipSide(p2, p1, reg2)}};
    return result;
}

std::optional<std::pair<Vec, Vec>> Clipping::clipY(const Vec &p1, const Vec &p2)
{
    Side reg1 = 
        p1.y < corners.first.y ? 
            Side::Bottom :
        p1.y > corners.second.y ? 
            Side::Top :
        Side::Inside;
    Side reg2 = 
        p2.y < corners.first.y ? 
            Side::Bottom :
        p2.y > corners.second.y ? 
            Side::Top :
        Side::Inside;
    if ((int(reg1) | int(reg2)) == 0)
        return {{p1, p2}};
    if ((int(reg1) ^ int(reg2)) == 0)
        return std::nullopt;
    std::pair<Vec, Vec> result = {{clipSide(p1, p2, reg1)}, {clipSide(p2, p1, reg2)}};
    return result;
}

std::optional<std::pair<Vec, Vec>> Clipping::clipZ(const Vec &p1, const Vec &p2)
{
    Side reg1 = 
        p1.z < corners.first.z ? 
            Side::Near :
        p1.z > corners.second.z ? 
            Side::Far :
        Side::Inside;
    Side reg2 = 
        p2.z < corners.first.z ? 
            Side::Near :
        p2.z > corners.second.z ? 
            Side::Far :
        Side::Inside;
    if ((int(reg1) | int(reg2)) == 0)
        return {{p1, p2}};
    if ((int(reg1) ^ int(reg2)) == 0)
        return std::nullopt;
    std::pair<Vec, Vec> result = {{clipSide(p1, p2, reg1)}, {clipSide(p2, p1, reg2)}};
    return result;
}

Vec Clipping::clipSide(const Vec& p1, const Vec& p2, Side side) {
    switch (side) {
    case Side::Left:
        return Vec(
            corners.first.x,
            p1.y +  (corners.first.x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x),
            p1.z + (corners.first.x - p1.x) * (p2.z - p1.z) / (p2.x - p1.x)
        );
    case Side::Right:
        return Vec(
            corners.second.x,
            p1.y + (corners.second.x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x),
            p1.z + (corners.second.x - p1.x) * (p2.z - p1.z) / (p2.x - p1.x)
        );
    case Side::Bottom:
        return Vec(
            p1.x + (corners.first.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y),
            corners.first.y,
            p1.z + (corners.first.y - p1.y) * (p2.z - p1.z) / (p2.y - p1.y)
        );
    case Side::Top:
        return Vec(
            p1.x + (corners.second.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y),
            corners.second.y,
            p1.z + (corners.second.y - p1.y) * (p2.z - p1.z) / (p2.y - p1.y)
        );
    case Side::Near:
        return Vec(
            p1.x + (corners.first.z - p1.z) * (p2.x - p1.x) / (p2.z - p1.z),
            p1.y + (corners.first.z - p1.z) * (p2.y - p1.y) / (p2.z - p1.z),
            corners.first.z
        );
    case Side::Far:
        return Vec(
            p1.x + (corners.second.z - p1.z) * (p2.x - p1.x) / (p2.z - p1.z),
            p1.y + (corners.second.z - p1.z) * (p2.y - p1.y) / (p2.z - p1.z),
            corners.second.z
        );
    default:
        return p1;
    }
}