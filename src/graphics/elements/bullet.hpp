#pragma once

#include "../../physics/rigid_body.hpp"
#include "../../math/vector.hpp"
#include "../shapes/circle.hpp"
#include "../../physics/icollidable.hpp"

namespace graphics::elements
{
    class Bullet : public physic::RigidBody, public physic::ICollidable
    {
    public:
        Bullet() = default;
        Bullet(const math::Vector &initial_position, const math::Vector &initial_velocity, double radius);
        ~Bullet();

        void Render();
        void Update(double delta_time) override;

        math::Vector get_position() override;
        double get_width() override;
        double get_height() override;

        void ProcessCollision(ICollidable *collidable) override;

    private:
        shapes::Circle *shape_;
    };
}