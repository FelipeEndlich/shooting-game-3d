#pragma once

#include "../../physics/rigid_body.hpp"
#include "../../math/vector.hpp"
#include "../color/rgba.hpp"
#include "../shapes/cuboid.hpp"
#include "./character/character.hpp"
#include "bullet.hpp"

namespace graphics::elements
{
    class Gun : public physic::RigidBody
    {
    public:
        Gun() = default;
        Gun(math::Vector &initial_position, double width, double height, double depth);
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

        graphics::shapes::Cuboid *body_;
        graphics::shapes::Cuboid *barrel_;
        graphics::shapes::Cuboid *grip_;
        graphics::shapes::Cuboid *magazine_;

        friend graphics::elements::character::Character;
    };
}