#pragma once

#include "../../../shapes/cuboid.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Calf : public graphics::shapes::Cuboid
    {
    public:
        Calf(const math::Vector &origin, double width, double height, const graphics::color::RGBA &color)
            : Cuboid(origin, width, height, color){};
        ~Calf() = default;

        math::Vector ThigAnchorPoint() const;
        void Mirror(math::Vector &mirror_point);
    };
}