#pragma once

#include <classes/vec.hpp>

class Camera {
public:
    Vec3f pos;

    Camera(Vec3f pos) : pos(pos) {}
};
