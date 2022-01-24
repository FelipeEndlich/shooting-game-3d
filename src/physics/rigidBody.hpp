#pragma once

#include "../math/vector.hpp"

namespace physics
{
    class RigidBody
    {
    public:
        RigidBody(int dimension, double width, double height);
        virtual ~RigidBody() = default;

        void update(double dt);

    protected:
        math::Vector position;
        math::Vector velocity;
        math::Vector acceleration;
    };
}