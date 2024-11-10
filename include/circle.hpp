#pragma once

#include "vec.hpp"
#include <optional>
#include <SDL2/SDL.h>
#include "graphics.hpp"

class Circle {
public:
    Vec center;
    float radius;
    std::optional<Vec> direction;
    SDL_Color color;

    Circle(Vec center, float radius, std::optional<Vec> direction = std::nullopt, SDL_Color color = {255, 255, 255}) : 
        center(center), radius(radius), direction(direction), color(color) {}
    void draw(Graphics &graphics) const;
};