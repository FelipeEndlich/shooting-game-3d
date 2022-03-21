#pragma once

#include "./camera.hpp"
#include "../math/vector.hpp"
#include "../physics/direction.hpp"

namespace shoot_and_jump
{
    class FirstPersonCamera : public Camera
    {
    public:
        FirstPersonCamera() : Camera() {}
        FirstPersonCamera(const math::Vector &character_position);

        virtual void Move(physic::Direction direction, double increment);
        virtual void Rotate(physic::Direction direction, double increment);
    };
}