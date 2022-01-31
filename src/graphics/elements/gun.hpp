#pragma once

#include "../../physics/rigid_body.hpp"
#include "../../math/vector.hpp"
#include "../color/rgba.hpp"
#include "../shapes/rectangle.hpp"
#include "./character/character.hpp"
#include "bullet.hpp"

namespace graphics::elements
{
    class Gun : public physic::RigidBody
    {
    public:
        Gun() = default;
        Gun(math::Vector &initial_position, double width, double height);
        ~Gun();

        Bullet *Shoot(bool invert);

        void Render();
        void Translate(const math::Vector &translation, bool translate_position);
        void Scale(const math::Vector &center, double sx, double sy);
        void Rotate(const math::Vector &center, double angle);

        void Mirror(math::Vector &mirror_point);

        math::Vector get_position();
        double get_width();
        double get_height();
        double get_angle();

    private:
        double width_;
        double height_;
        double angle_;

        graphics::shapes::Rectangle *body_;
        graphics::shapes::Rectangle *barrel_;
        graphics::shapes::Rectangle *grip_;
        graphics::shapes::Rectangle *magazine_;

        friend graphics::elements::character::Character;
    };
}