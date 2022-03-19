#pragma once

#include "../../../shapes/cuboid.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Torso : public graphics::shapes::Cuboid
    {
    public:
        Torso(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color)
            : Cuboid(origin, width, height, color){};
        ~Torso() = default;

        math::Vector HeadAnchorPoint() const;
        math::Vector LeftArmAnchorPoint() const;
        math::Vector LeftThigAnchorPoint() const;
        math::Vector RightArmAnchorPoint() const;
        math::Vector RightThigAnchorPoint() const;

        void Mirror(math::Vector &mirror_point);
    };
}