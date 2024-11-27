#include "curve.hpp"

Curve::Curve(std::array<Vec, 4> points, SDL_Color color) : points(std::move(points)), color(color), div(30)  {}