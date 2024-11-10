#pragma once

class Vec;
#include "imgui.h"
#include "matrix.hpp"

class Vec {
public:
    float x, y, z;

    Vec(float x, float y, float z);
    Vec(const ImVec4& vec);

    float mag() const;                                      // Magnitude
    Vec normal() const;                                     // Normalize
    Vec operator+ (const Vec& other) const;
    Vec operator- (const Vec& other) const;
    friend Vec operator* (float scalar, const Vec& vector); // Scalar Product
    float operator* (const Vec& other) const;               // Dot Product
    Vec operator^ (const Vec& other) const;                 // Cross Product
    void operator+= (const Vec& other);
    void operator-= (const Vec& other);
    template<typename T>
    void operator*= (const T& transf) {                      // Matrix Transformation
        *this = transf * *this;
    }                       

    operator ImVec4() const;
};