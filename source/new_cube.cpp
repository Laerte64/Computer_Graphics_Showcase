#include "new_cube.hpp"

#include <SDL2/SDL_opengl.h>
#include "edge.hpp"
#include "viewport.hpp"
#include "circle.hpp"

#include <iostream>

_CubeTest::_CubeTest() : Graphics(), circle(Vec(0, 0, 0), 1, std::nullopt, {200, 150, 100}) {
    models.emplace_back(std::make_unique<Model>());
    Model& cube = *models[models.size() - 1];
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

    {
        models.emplace_back(std::make_unique<Model>());
            Model& m = *models[models.size() - 1]; 
            m.addPoint(Vec(0, 0, 0));
            m.addPoint(Vec(0, 1, 1));
            m.edges.emplace_back(&m, 0, 1);
    }
}

void _CubeTest::input(SDL_Event event) {
    
};

#include "b_spline.hpp"
void _CubeTest::update() {
    circle.draw(*this);

    auto b = BSpline({Vec(-1, 0, 0), Vec(0, 1, 0), Vec(0, -1, 0), Vec(0, 0, 1)}, {200, 150, 100});
    b.control({255, 100, 50}).draw(*this);
    b.by_matrix(30).draw(*this);    
}

_CubeTest::~_CubeTest() {
    
}