#pragma once

#include "../../physics/rigid_body.hpp"
#include "../../math/vector.hpp"
#include "../shapes/circle.hpp"

namespace graphics::elements
{
    class Bullet : public physic::RigidBody
    {
    public:
        Bullet() = default;
        Bullet(const math::Vector &initial_position, const math::Vector &initial_velocity, double radius);
        ~Bullet();

        void Render();
        void Update(double delta_time) override;

    private:
        shapes::Circle *shape_;
    };
}