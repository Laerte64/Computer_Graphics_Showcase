#include "model.hpp"

Model::Model() : points(), edges() {}

unsigned short Model::addPoint(Vec point) {
    points.push_back(point);
    return points.size() - 1;
}

void Model::draw(Graphics& graphics, void (*algorithm)(Graphics& graphics, Vec p1, Vec p2, SDL_Color color)) const {
    for (auto edge : edges)
        edge.draw(graphics, algorithm);
}

Vec  Model::mid_point() const {
    int num = 0;
    Vec mid_p = Vec(0, 0, 0);
    for (std::optional<Vec> point : points)
        if (point.has_value()) {
            mid_p += point.value();
            num++;
        }
    return 1 / float(num) * mid_p;
}

void Model::homogenous_tranf(Matrix transf) {
    Vec mid_p = mid_point();
    for (std::optional<Vec>& point : points) {
        if (!point.has_value())
            continue;
        point.value() -= mid_p;
        point.value() *= transf;
        point.value() += mid_p;
    }
}