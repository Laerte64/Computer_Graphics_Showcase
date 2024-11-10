#include "camera.hpp"

#include <math.h>

Camera::Camera(Vec pos, Vec orientation, std::array<float, 4> perspective, float scale) : 
    pos(pos), 
    orientation(orientation),
    fov(perspective[0]), aspect(perspective[1]), 
    near(perspective[2]), far(perspective[3]),
    dist(scale)
    {}

Matrix Camera::projection() {

    Matrix translate = Matrix::translate(-pos.x, -pos.y, -pos.z);
    Matrix rotateY = Matrix::rotateY(M_PI + std::atan2(- orientation.x, orientation.z));
    Matrix rotateX = Matrix::rotateX(- std::asin(orientation.y));
    Matrix perspective = Matrix::perspective(fov, aspect, near, far);
    return perspective * rotateX * rotateY * translate;
}

float Camera::get_theta() const {
    return - std::atan2(- orientation.x, orientation.z);
}

float Camera::get_phi() const {
    return std::asin(orientation.y);
}

void Camera::set_theta(float t, bool first_p) {
    add_theta(t - get_theta());
}

void Camera::set_phi(float p, bool first_p) {
    add_phi(p - get_phi());
}

void Camera::add_theta(float t, bool first_p) {
    if (!first_p)
        pos += dist * orientation;
    orientation *= Matrix::rotateY(t);
    if (!first_p)
        pos -= dist * orientation;
}

void Camera::add_phi(float p, bool first_p) {
    if (std::abs(p + get_phi()) >= M_PI/2 - 0.05)
        return;
    float theta = get_theta();
    set_theta(0);
    if (!first_p)
        pos += dist * orientation;
    orientation *= Matrix::rotateX(-p);
    if (!first_p)
        pos -= dist * orientation;
    set_theta(theta);
}