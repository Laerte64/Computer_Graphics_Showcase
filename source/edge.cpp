#include "edge.hpp"

#include <iostream>
#include "viewport.hpp"
#include "clipping.hpp"
#include "graphics.hpp"

Edge::Edge(Model* model, int p1, int p2, SDL_Color color) : p1_index(p1), p2_index(p2), color(color), model(model) {}

void Edge::draw(Graphics& graphics) const {
    if (!model->points[p1_index].has_value())
        return;
    if (!model->points[p2_index].has_value())
        return;
    auto transf = graphics.camera.projection();
    auto p1 = transf *  model->points[p1_index].value();
    auto p2 = transf *  model->points[p2_index].value();
    auto clipped = Clipping::clip(p1, p2);
    if (!clipped.has_value())
        return;
    p1 = viewport::transform(graphics.width, graphics.height, clipped.value().first);
    p2 = viewport::transform(graphics.width, graphics.height, clipped.value().second);
    graphics.printer(graphics, p1, p2, color);
}

void Edge::DDA(Graphics& graphics, Vec p1, Vec p2, SDL_Color color) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float steps = std::max(std::abs(dx), std::abs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = p1.x;
    float y = p1.y;

    for (int i = 0; i <= steps; i++) {
        graphics.renderPixel(static_cast<int>(x), static_cast<int>(y), color);
        x += xIncrement;
        y += yIncrement;
    }
}

void Edge::Bresenham(Graphics& graphics, Vec p1, Vec p2, SDL_Color color) {
    int x1 = static_cast<int>(p1.x);
    int y1 = static_cast<int>(p1.y);
    int x2 = static_cast<int>(p2.x);
    int y2 = static_cast<int>(p2.y);

    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        graphics.renderPixel(x1, y1, color);

        if (x1 == x2 && y1 == y2) 
            break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
