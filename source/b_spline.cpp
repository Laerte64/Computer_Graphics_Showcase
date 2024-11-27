#include "b_spline.hpp"

BSpline::BSpline(std::array<Vec, 4> points, SDL_Color color) : Curve(std::move(points), color) {}

Model BSpline::by_matrix(int n) const {
    Model m;
    
    float t = 0;
    m.addPoint(points[0]);
    while (t < 1) {
        m.addPoint(by_matrix(t, {2 * points[0] - points[1], points[0], points[1], points[2]}));
        t += 3.f / n;
    }
    while (t < 2) {
        m.addPoint(by_matrix(t - 1, {points[0], points[1], points[2], points[3]}));
        t += 3.f / n;
    }
    while (t < 3) {
        m.addPoint(by_matrix(t - 2, {points[1], points[2], points[3], 2 * points[3] - points[2]}));
        t += 3.f / n;
    }
    m.addPoint(points[3]);

    for (int i =0; i < n; i++)
        m.edges.emplace_back(&m, i, i + 1, color);

    return m;
}

Model BSpline::control(SDL_Color color) const
{
    auto m = Model();
    m.addPoint(points[0]);
    for (int i = 0; i < 3; i++) {
        m.addPoint(points[i + 1]);
        m.edges.emplace_back(&m, i, i + 1, color);
    }
    return m;
}

Vec BSpline::by_matrix(float t, const std::array<Vec, 4> &points) const
{
    float h[4][4] = {
            { -1,  3, -3, 1 },
            {  3, -6,  3, 0 },
            { -3,  0,  3, 0 },
            {  1,  4,  1, 0 }
        };

        float T[4] = { t * t * t, t * t, t, 1 };

        float coefficients[4] = { 0 };
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                coefficients[i] += 1.f / 6 * T[j] * h[j][i];
            }
        }

        Vec point = coefficients[0] * points[0] + coefficients[1] * points[1] + coefficients[2] * points[2] + coefficients[3] * points[3];
        return point;
}