#pragma once

#include "../../../shapes/rectangle.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Arm : public graphics::shapes::Rectangle
    {
    public:
        Arm(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color)
            : Rectangle(origin, width, height, color){};
        ~Arm() = default;

        math::Vector TorsoAnchorPoint() const;
    };
}