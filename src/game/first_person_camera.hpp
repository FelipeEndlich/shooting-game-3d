#pragma once

#include "../math/vector.hpp"
#include "./camera.hpp"

namespace shoot_and_jump
{
    class FirstPersonCamera : public Camera
    {
    public:
        FirstPersonCamera() : Camera() {}
        FirstPersonCamera(const math::Vector &character_position);

        virtual void Move(const math::Vector &movement);
        virtual void Rotate(const math::Vector &angles);
    };
}