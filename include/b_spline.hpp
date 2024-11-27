#pragma once

#include "model.hpp"
#include "curve.hpp"

class BSpline : public Curve {
public:
    BSpline(std::array<Vec, 4> points, SDL_Color color = {255, 255, 255});
    Model by_matrix(int n) const override;
    Model control(SDL_Color color) const override;

private:
    Model by_matrix_segment(Model& m, const std::array<Vec, 4>& points) const;
    Vec by_matrix(float t, const std::array<Vec, 4>& points) const;
    
};