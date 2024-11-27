#include "circle.hpp"

#include "graphics.hpp"
#include "model.hpp"

void Circle::draw(Graphics &graphics) const {
    Model m;
    Vec orient = direction.has_value() ? direction.value() : graphics.camera.orientation;
    Vec x = radius * (orient ^ Matrix::rotateY(0.5) * Matrix::rotateZ(0.5) * orient).normal();
    Vec y = orient ^ x;
    for (int i = 0; i < divisions; i++)
        m.addPoint(center + std::cos(2 * i * M_PI / divisions) * x + std::sin(2 * i * M_PI / divisions) * y);
    for (int i = 0; i < divisions; i++)
        m.edges.emplace_back(&m, i, (i + 1) % divisions, color);
    if (show_dir)
    {
        int p1 = m.addPoint(center);
        int p2 = m.addPoint(center + 0.25 * radius * (direction.has_value() ? direction.value() : graphics.camera.orientation));
        m.edges.emplace_back(&m, p1, p2, color);
    }
    m.draw(graphics);
}