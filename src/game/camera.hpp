#pragma once

#include "../math/vector.hpp"
#include "../physics/direction.hpp"

namespace shoot_and_jump
{
    class Camera
    {
    public:
        Camera();

        virtual void Move(physic::Direction direction, double increment) = 0;
        virtual void Rotate(const math::Vector &angles) = 0;
        void Run();

    protected:
        math::Vector eye_;
        math::Vector center_;
        math::Vector up_;

        double angle_ = 0;
    };
}