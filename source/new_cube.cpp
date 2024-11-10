#include "new_cube.hpp"

#include <SDL2/SDL_opengl.h>
#include "edge.hpp"
#include <iostream>
#include "viewport.hpp"

_CubeTest::_CubeTest() : Graphics(), circle(Vec(0, 0, 0), 1, camera.orientation) {
    cube.addPoint({-0.5f, -0.5f, -0.5f});
    cube.addPoint({ 0.5f, -0.5f, -0.5f});
    cube.addPoint({ 0.5f,  0.5f, -0.5f});
    cube.addPoint({-0.5f,  0.5f, -0.5f});
    cube.addPoint({-0.5f, -0.5f,  0.5f});
    cube.addPoint({ 0.5f, -0.5f,  0.5f});
    cube.addPoint({ 0.5f,  0.5f,  0.5f});
    cube.addPoint({-0.5f,  0.5f,  0.5f});
    std::array<std::pair<int, int>, 12> edges = {{
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7},
    }};
    for (auto edge : edges)
        cube.edges.emplace_back(&cube, edge.first, edge.second);
    
}
#include "circle.hpp"
void _CubeTest::update() {
    circle.draw(*this);
    circle.direction.value() *= Matrix::rotateY(0.005);
    circle.direction.value() *= Matrix::rotateZ(0.01);

    cube.homogenous_tranf(Matrix::rotateY(0.002));
    cube.homogenous_tranf(Matrix::rotateX(0.001));
    cube.draw(*this, Edge::Bresenham);
}

_CubeTest::~_CubeTest() {

}