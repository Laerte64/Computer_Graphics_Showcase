#pragma once

#include <array>
#include "model.hpp"
#include "vec.hpp"
#include "curve.hpp"

class Bezier : public Curve {
public:
    Bezier(std::array<Vec, 4> points, SDL_Color color = {255, 255, 255});
    ~Bezier() {}

    Model de_casteljau(int n) const;
    Model by_matrix(int n) const override;
    Model forward_diff(int n) const;

    Model control(SDL_Color color) const override;

private:
    Vec de_casteljau(float t, Vec* points, int num_points) const;
    Vec by_matrix(float t) const;
};