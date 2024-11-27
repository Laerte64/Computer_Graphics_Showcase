#include "model.hpp"

Model::Model() : points(), edges() {}

unsigned short Model::addPoint(Vec point) {
    for (int i = 0; i < int(points.size()); i++)
        if (!points[i].has_value()) {
            points[i] = point;
            return i;
        }
    points.push_back(point);
    return points.size() - 1;
}

void Model::removePoint(int id) {
    points[id] = std::nullopt;
    for (int i = edges.size() - 1; i >= 0; i--)
        if (edges[i].p1_index == id || edges[i].p2_index == id)
            edges.erase(edges.begin() + i);
}

void Model::draw(Graphics& graphics) const {
    for (auto& edge : edges)
        edge.draw(graphics);
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

void Model::transform(Vec pivot, Matrix transf) {
    for (std::optional<Vec>& point : points) {
        if (!point.has_value())
            continue;
        point.value() -= pivot;
        point.value() *= transf;
        point.value() += pivot;
    }
}

void Model::cube(Model& model) {
    model.addPoint({-0.5f, -0.5f, -0.5f});
    model.addPoint({ 0.5f, -0.5f, -0.5f});
    model.addPoint({ 0.5f,  0.5f, -0.5f});
    model.addPoint({-0.5f,  0.5f, -0.5f});
    model.addPoint({-0.5f, -0.5f,  0.5f});
    model.addPoint({ 0.5f, -0.5f,  0.5f});
    model.addPoint({ 0.5f,  0.5f,  0.5f});
    model.addPoint({-0.5f,  0.5f,  0.5f});
    std::array<std::pair<int, int>, 12> edges = {{
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7},
    }};
    for (auto edge : edges)
        model.edges.emplace_back(&model, edge.first, edge.second);
}

void Model::pyramid(Model &model){
    model.addPoint({-0.5f, -0.5f, -0.5f});
    model.addPoint({ 0.5f, -0.5f, -0.5f});
    model.addPoint({ 0.5f, -0.5f,  0.5f});
    model.addPoint({-0.5f, -0.5f,  0.5f});
    model.addPoint({ 0.0f,  0.5f,  0.0f});
    model.edges.emplace_back(&model, 0, 1);
    model.edges.emplace_back(&model, 1, 2);
    model.edges.emplace_back(&model, 2, 3);
    model.edges.emplace_back(&model, 3, 0);
    model.edges.emplace_back(&model, 0, 4);
    model.edges.emplace_back(&model, 1, 4);
    model.edges.emplace_back(&model, 2, 4);
    model.edges.emplace_back(&model, 3, 4);
}
