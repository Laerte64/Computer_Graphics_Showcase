#include "circle.hpp"

#include "graphics.hpp"
#include "model.hpp"
#include <iostream>

void Circle::draw(Graphics &graphics) const {
    Model m;
    const int n = 64;
    Vec orient = direction.has_value() ? direction.value() : graphics.camera.orientation;
    Vec x = radius * (orient ^ Matrix::rotateY(0.5) * Matrix::rotateZ(0.5) * orient).normal();
    Vec y = orient ^ x;
    for (int i = 0; i < n; i++)
        m.addPoint(center + std::cos(2 * i * M_PI / n) * x + std::sin(2 * i * M_PI / n) * y);
    for (int i = 0; i < n; i++)
        m.edges.emplace_back(&m, i, (i + 1) % n);
    m.draw(graphics, Edge::DDA);
}