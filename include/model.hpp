#pragma once

class Model;
#include "vec.hpp"
#include <vector>
#include <optional>
#include "edge.hpp"

class Model {
public:
    std::vector<std::optional<Vec>> points;
    std::vector<Edge> edges;

    Model();
    unsigned short addPoint(Vec point);
    void draw(Graphics& graphics, void (*algorithm)(Graphics& graphics, Vec p1, Vec p2, SDL_Color color)) const;
    Vec mid_point() const;
    void homogenous_tranf(Matrix transf);
};