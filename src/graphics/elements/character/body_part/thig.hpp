#pragma once

#include "../../../shapes/cuboid.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Thig : public graphics::shapes::Cuboid
    {
    public:
        Thig(const math::Vector &origin, double width, double height, double depth, const graphics::color::RGBA &color)
            : Cuboid(origin, width, height, depth, color){};
        ~Thig() = default;

        math::Vector TorsoAnchorPoint() const;
        math::Vector CalfAnchorPoint() const;

        void Mirror(math::Vector &mirror_point);
    };
}