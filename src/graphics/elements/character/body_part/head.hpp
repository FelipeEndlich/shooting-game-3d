#pragma once

#include "../../../shapes/circle.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Head : public graphics::shapes::Circle
    {
    public:
        Head(math::Vector &origin, double radius, graphics::color::RGBA &color)
            : Circle(origin, radius, color) {};
        virtual ~Head() = default;

        math::Vector TorsoAnchorPoint() const;
    };
}