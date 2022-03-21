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
        virtual void Rotate(physic::Direction direction, double increment) = 0;
        void Run();

        double get_x() const;
        double get_y() const;
        double get_z() const;

    protected:
        math::Vector eye_;
        math::Vector center_;
        math::Vector up_;

        double angle_ = 0;
    };
}