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
    Model cube;
    Circle circle;
    void update() override;
};