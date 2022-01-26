#pragma once

#include "../../physics/rigidBody.hpp"
#include "../../math/vector.hpp"
#include "../color/rgba.hpp"
#include "../shapes/rectangle.hpp"

namespace graphics::elements
{
    class Obstacle : public physic::RigidBody
    {
    public:
        Obstacle() = default;
        Obstacle(math::Vector &initial_position, double width, double height, graphics::color::RGBA &color);

        void Render();

    private:
        graphics::shapes::Rectangle shape_;
    };
}