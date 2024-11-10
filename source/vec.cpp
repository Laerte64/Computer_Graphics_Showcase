#include "vec.hpp"

#include <math.h>

Vec::Vec(float x, float y, float z) : x(x), y(y), z(z) {}

Vec::Vec(const ImVec4& vec) : x(vec.x), y(vec.y), z(vec.z) {}

float Vec::mag() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vec Vec::normal() const {
    return 1 / mag() * *this;
}

Vec Vec::operator+ (const Vec& other) const {
    return Vec(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vec Vec::operator- (const Vec& other) const {
    return Vec(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vec operator* (float scalar, const Vec& vector) {
    return Vec(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

float Vec::operator* (const Vec& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vec Vec::operator^ (const Vec& other) const {
    return Vec(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

void Vec::operator+= (const Vec& other) {
    *this = *this + other;
}

void Vec::operator-= (const Vec& other) {
    *this = *this - other;
}

Vec::operator ImVec4() const {
    return ImVec4(x, y, z, 1);
}