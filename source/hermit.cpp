#include "hermit.hpp"

Hermit::Hermit(std::array<Vec, 4> points, SDL_Color color) : Curve(std::move(points), color)  {}

Model Hermit::by_matrix(int n) const {
    Model m;
    m.addPoint(by_matrix(0.f));
    for (int i = 0; i < n; i++) {
        m.addPoint(by_matrix((i + 1) * 1.f / n));
        m.edges.emplace_back(&m, i, i + 1, color);
    }
    return m;
}

Model Hermit::control(SDL_Color color) const
{
    auto m = Model();
    for (int i = 0; i < 4; i++)
        m.addPoint(points[i]);
    m.edges.emplace_back(&m, 0, 1, color);
    m.edges.emplace_back(&m, 2, 3, color);
    return m;
}

Vec Hermit::by_matrix(float t) const {
    float h[4][4] = {
            {  2, -2,  1,  1 },
            { -3,  3, -2, -1 },
            {  0,  0,  1,  0 },
            {  1,  0,  0,  0 }
        };

        float T[4] = { t * t * t, t * t, t, 1 };

        float coefficients[4] = { 0 };
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                coefficients[i] += T[j] * h[j][i];
            }
        }

        Vec point = coefficients[0] * points[0] + coefficients[1] * points[3] + coefficients[2] * (points[1] - points[0]) + coefficients[3] * (points[2] - points[3]);
        return point;
}