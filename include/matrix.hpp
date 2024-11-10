#pragma once

class Matrix;
#include <array>
#include "vec.hpp"

class Matrix {
public:
    std::array<std::array<float, 4>, 4> data;

    Matrix(std::array<std::array<float, 4>, 4> data);
    
    std::array<float, 4>& operator[] (int index);
    const std::array<float, 4>& operator[] (int index) const;
    Matrix operator* (const Matrix& other) const;
    Vec operator* (const Vec& vec) const;

    static Matrix zero();
    static Matrix identity();
    static Matrix translate(float x, float y, float z);
    static Matrix scale(float x, float y, float z);
    static Matrix rotateX(float radians);
    static Matrix rotateY(float radians);
    static Matrix rotateZ(float radians);
    static Matrix perspective(float fov, float aspect, float near, float far);
};