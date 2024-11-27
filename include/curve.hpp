#pragma once

class Graphics;
#include <array>
#include "model.hpp"

class Curve {
public:
    std::array<Vec, 4> points;
    SDL_Color color;
    bool show_contr;
    int div;
    Curve(std::array<Vec, 4> points, SDL_Color color = {255, 255, 255});
    virtual ~Curve() {}
    virtual Model by_matrix(int n) const = 0;
    virtual Model control(SDL_Color color) const = 0;
};