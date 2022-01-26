#pragma once

#include "../math/vector.hpp"

namespace physic
{
    class RigidBody
    {
    public:
        RigidBody(int dimension);
        virtual ~RigidBody() = default;

        virtual void Update(double delta_time);

        inline static double default_horizontal_velocity_ = 0.1;

    protected:
        math::Vector position_;
        math::Vector velocity_;
        math::Vector acceleration_;
    };
}