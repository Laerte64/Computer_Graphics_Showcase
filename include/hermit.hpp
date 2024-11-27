#pragma once

#include "model.hpp"
#include "curve.hpp"

class Hermit : public Curve {
public:
    Hermit(std::array<Vec, 4> points, SDL_Color color = {255, 255, 255});
    ~Hermit() {}
    Model by_matrix(int n) const override;
    Model control(SDL_Color color) const override;

private:
    Vec by_matrix(float t) const;
};