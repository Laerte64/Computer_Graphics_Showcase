#pragma once

#include "graphics.hpp"
#include <vector>
#include "camera.hpp"
#include "model.hpp"
#include "circle.hpp"

class _CubeTest : public Graphics {
public:
    _CubeTest();
    ~_CubeTest();

private:
    Circle circle;
    void input(SDL_Event event) override;
    void update() override;
};