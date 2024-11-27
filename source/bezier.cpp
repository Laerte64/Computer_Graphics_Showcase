#include "bezier.hpp"

Bezier::Bezier(std::array<Vec, 4> points, SDL_Color color) : Curve(std::move(points), color) {}

Model Bezier::de_casteljau(int n) const {
    Vec p[4] = {points[0], points[1], points[2], points[3]};
    Model m;
    m.addPoint(de_casteljau(0.f, p, 4));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) p[j] = points[j]; 
        m.addPoint(de_casteljau((i + 1) * 1.f / n, p, 4));
        m.edges.emplace_back(&m, i, i + 1, color);
    }
    return m;
}

Model Bezier::by_matrix(int n) const {
    Model m;
    m.addPoint(by_matrix(0.f));
    for (int i = 0; i < n; i++) {
        m.addPoint(by_matrix((i + 1) * 1.f / n));
        m.edges.emplace_back(&m, i, i + 1, color);
    }
    return m;
}

Model Bezier::forward_diff(int n) const {
    Model m;

    float dx = 1.0f / n;
    float d2x = dx * dx;
    float d3x = dx * dx * dx;

    Vec A1 = 3 * (points[1] - points[0]);
    Vec A2 = 3 * (points[2] - 2 * points[1] + points[0]);
    Vec A3 = points[3] - 3 * points[2] + 3 * points[1] - points[0];
    

    Vec p = points[0];
    Vec d1 = d3x * A3 + d2x * A2 + dx * A1;
    Vec d2 = 6 * d3x * A3 + 2 * d2x * A2;
    Vec d3 = 6 * d3x * A3;

    m.addPoint(p);
    for (int i = 0; i < n; i++) {
        p += d1;
        d1 += d2;
        d2 += d3;
        m.addPoint(p);
        m.edges.emplace_back(&m, i, i + 1, color);
    }
        
    return m;
}

Model Bezier::control(SDL_Color color) const {
    auto m = Model();
    m.addPoint(points[0]);
    for (int i = 0; i < 3; i++) {
        m.addPoint(points[i + 1]);
        m.edges.emplace_back(&m, i, i + 1, color);
    }
    return m;
}

Vec Bezier::de_casteljau(float t, Vec* points, int num_points) const {
    if (num_points == 1)
        return points[0];
    for (int i = 0; i < num_points - 1; i++) {
        points[i] *= t;
        points[i] += (1 - t) * points[i + 1];
    }
    return de_casteljau(t, points, num_points - 1);
}

Vec Bezier::by_matrix(float t) const {
    float M[4][4] = {
        {-1,  3, -3, 1},
        { 3, -6,  3, 0},
        {-3,  3,  0, 0},
        { 1,  0,  0, 0}
    };
    float T[4] = { t * t * t, t * t, t, 1 };

    float coefficients[4] = {0};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                coefficients[i] += T[j] * M[j][i];
            }
        }
        
    Vec result(0, 0, 0);
    for (int i = 0; i < 4; ++i) {
        result += coefficients[i] * points[i];
    }

    return result;
}