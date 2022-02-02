#pragma once

#include "../../../shapes/rectangle.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Calf : public graphics::shapes::Rectangle
    {
    public:
        Calf(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color)
            : Rectangle(origin, width, height, color){};
        ~Calf() = default;

        math::Vector ThigAnchorPoint() const;
        void Mirror(math::Vector &mirror_point);
    };
}