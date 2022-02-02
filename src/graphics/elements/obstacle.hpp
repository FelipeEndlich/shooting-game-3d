#pragma once

#include "../../physics/rigid_body.hpp"
#include "../../math/vector.hpp"
#include "../color/rgba.hpp"
#include "../shapes/rectangle.hpp"
#include "../../physics/icollidable.hpp"

namespace graphics::elements
{
    class Obstacle : public physic::RigidBody, public physic::ICollidable
    {
    public:
        Obstacle() = default;
        Obstacle(math::Vector &initial_position, double width, double height, graphics::color::RGBA &color);
        ~Obstacle();

        void Render();

        math::Vector get_position() override;
        double get_width() override;
        double get_height() override;
        void ProcessCollision(ICollidable *collidable) override;

    private:
        graphics::shapes::Rectangle* shape_;
    };
}