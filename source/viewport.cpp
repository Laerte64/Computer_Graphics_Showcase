#include "viewport.hpp"

Vec viewport::transform(int width, int height, Vec point) {
    return Vec(width * (point.x + 1) / 2, height * (1 - point.y) / 2, point.z);
}