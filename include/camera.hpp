#pragma once

#include "vec.hpp"
#include "matrix.hpp"

class Camera {
public:
    Vec pos;            
    Vec orientation;
    float fov, aspect;  
    float near, far;    
    float dist;

    Camera(Vec pos, Vec orientation, std::array<float, 4> perspective, float dist = 3);
    Matrix projection();
    
    float get_theta() const;
    float get_phi() const;
    float get_zoom(bool first_p = false) const;
    void set_theta(float t, bool first_p = false);
    void set_phi(float p, bool first_p = false);
    void set_zoom(float x, bool first_p = false);
    void add_theta(float t, bool first_p = false);
    void add_phi(float p, bool first_p = false);
    void add_zoom(float s, bool first_p = false);
};