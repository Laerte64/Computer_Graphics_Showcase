#include "matrix.hpp"

#include <cmath>

Matrix::Matrix(std::array<std::array<float, 4>, 4> data) : data(data) {}

std::array<float, 4>& Matrix::operator[] (int index) {
    return data[index];
}

const std::array<float, 4>& Matrix::operator[] (int index) const {
    return data[index];
}

Matrix Matrix::operator* (const Matrix& other) const {
    Matrix result = zero();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; ++k)
                result[i][j] += (*this)[i][k] * other[k][j];
    return result;
}

Vec Matrix::operator* (const Vec& vec) const {
    std::array<float, 4> op = {vec.x, vec.y, vec.z, 1};
    std::array<float, 4> result = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i] += (*this)[i][j] * op[j];
        }
    }
    return 1 / result[3] * Vec(result[0], result[1], result[2]);
}

Matrix Matrix::zero() {
    return Matrix({{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }});
}

Matrix Matrix::identity() {
    return Matrix({{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }});
}

Matrix Matrix::translate(float x, float y, float z) {
    Matrix mat = identity();
    mat[0][3] = x;
    mat[1][3] = y;
    mat[2][3] = z;
    return mat;
}

Matrix Matrix::scale(float x, float y, float z) {
    Matrix mat = identity();
    mat[0][0] = x;
    mat[1][1] = y;
    mat[2][2] = z;
    return mat;
}

Matrix Matrix::rotateX(float radians) {
    Matrix mat = identity();
    mat[1][1] = std::cos(radians);
    mat[1][2] = -std::sin(radians);
    mat[2][1] = std::sin(radians);
    mat[2][2] = std::cos(radians);
    return mat;
}

Matrix Matrix::rotateY(float radians) {
    Matrix mat = identity();
    mat[2][2] = std::cos(radians);
    mat[2][0] = -std::sin(radians);
    mat[0][2] = std::sin(radians);
    mat[0][0] = std::cos(radians);
    return mat;
}

Matrix Matrix::rotateZ(float radians) {
    Matrix mat = identity();
    mat[0][0] = std::cos(radians);
    mat[0][1] = -std::sin(radians);
    mat[1][0] = std::sin(radians);
    mat[1][1] = std::cos(radians);
    return mat;
}

Matrix Matrix::perspective(float fov, float aspect, float near, float far) {
    Matrix mat = zero();
    float tanHalfFOV = tan(fov / 2);

    mat[0][0] = 1 / (aspect * tanHalfFOV);
    mat[1][1] = 1 / tanHalfFOV;
    mat[2][2] = -(far + near) / (far - near);
    mat[2][3] = -(2 * far * near) / (far - near);
    mat[3][2] = -1;
    return mat;
}