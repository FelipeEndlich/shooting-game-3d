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
        inline static double kGravityAcceleration = 0.001;

        double get_mass() const;

    protected:
        double mass_;
        math::Vector weight_;
        math::Vector external_force_;
        math::Vector position_;
        math::Vector velocity_;
        math::Vector acceleration_;
    };
}