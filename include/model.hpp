#pragma once

class Model;
#include "vec.hpp"
#include <vector>
#include <optional>
#include "edge.hpp"

class Graphics;

class Model {
public:
    std::vector<std::optional<Vec>> points;
    std::vector<Edge> edges;

    Model();
    unsigned short addPoint(Vec point);
    void removePoint(int id);
    void draw(Graphics& graphics) const;
    Vec mid_point() const;
    void transform(Vec pivot, Matrix transf);

    static void cube(Model& model);
    static void pyramid(Model& model);
};