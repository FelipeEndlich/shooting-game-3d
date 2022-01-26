#pragma once

#include "../math/vector.hpp"

namespace physic
{
    class RigidBody
    {
    public:
        RigidBody(int dimension);
        virtual ~RigidBody() = default;

        virtual void update(double dt);

        inline static double DEFAULT_HORIZONTAL_VELOCITY = 0.1;

    protected:
        math::Vector position;
        math::Vector velocity;
        math::Vector acceleration;
    };
}