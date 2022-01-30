#pragma once

#include "../../physics/rigid_body.hpp"
#include "../../math/vector.hpp"
#include "../color/rgba.hpp"
#include "../shapes/rectangle.hpp"
#include "./character/character.hpp"

namespace graphics::elements
{
    class Gun : public physic::RigidBody
    {
    public:
        Gun() = default;
        Gun(math::Vector &initial_position, double width, double height);
        ~Gun();

        void Shoot();
        void Render();
        void Translate(math::Vector &translation, bool translate_position);
        void Scale(math::Vector &scale, double sx, double sy);

        math::Vector get_position();
        double get_width();
        double get_height();

    private:
        double width_;
        double height_;

        graphics::shapes::Rectangle *body_;
        graphics::shapes::Rectangle *barrel_;
        graphics::shapes::Rectangle *grip_;
        graphics::shapes::Rectangle *magazine_;

        friend graphics::elements::character::Character;
    };
}