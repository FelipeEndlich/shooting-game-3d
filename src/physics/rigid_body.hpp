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

        double get_mass() const;
        math::Vector get_gravity_acceleration() const;
        math::Vector get_weight() const;

        void set_gravity_acceleration(math::Vector gravity_acceleration);

    protected:
        double mass_;
        math::Vector gravity_acceleration_;
        math::Vector weight_;
        math::Vector external_force_;
        math::Vector position_;
        math::Vector velocity_;
        math::Vector acceleration_;
    };
}