#pragma once

class Edge;
#include <SDL2/SDL.h>
#include "model.hpp"

class Graphics;

class Edge {
public:
    int p1_index, p2_index;
    SDL_Color color;
    Model* model;

    Edge(Model* model, int p1, int p2, SDL_Color color = {255, 255, 255});

    static void DDA(Graphics& graphics, Vec p1, Vec p2, SDL_Color color);
    static void Bresenham(Graphics& graphics, Vec p1, Vec p2, SDL_Color color);

    void draw(Graphics& graphics) const;    
};