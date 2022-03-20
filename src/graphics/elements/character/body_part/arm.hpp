#pragma once

#include "../../../shapes/cuboid.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Arm : public graphics::shapes::Cuboid
    {
    public:
        Arm(const math::Vector &origin, double width, double height, double depth, const graphics::color::RGBA &color)
            : Cuboid(origin, width, height, depth, color){};
        ~Arm() = default;

        math::Vector TorsoAnchorPoint() const;
        void Mirror(math::Vector &mirror_point);
    };
}