#pragma once

#include "vec.hpp"
#include <optional>
#include <SDL2/SDL.h>
#include "edge.hpp"

class Graphics;

class Circle {
public:
    Vec center;
    float radius;
    std::optional<Vec> direction;
    SDL_Color color;
    bool show_dir;
    int divisions;

    Circle(Vec center, float radius, std::optional<Vec> direction = std::nullopt, SDL_Color color = {255, 255, 255}) : 
        center(center), radius(radius), direction(direction), color(color), divisions(60) {}
    void draw(Graphics &graphics) const;
};