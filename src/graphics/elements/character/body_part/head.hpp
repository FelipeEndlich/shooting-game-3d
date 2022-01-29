#pragma once

#include "../../../shapes/circle.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

namespace graphics::elements::character
{
    class Head : public graphics::shapes::Circle
    {
    public:
        Head()
            : graphics::shapes::Circle(){};
        Head(const math::Vector &origin, double radius)
            : graphics::shapes::Circle(origin, radius){};
        Head(const math::Vector &origin, double radius, const graphics::color::RGBA &color)
            : graphics::shapes::Circle(origin, radius, color){};
        Head(const Head &other)
            : graphics::shapes::Circle(other){};
        Head(const Head &&other)
            : graphics::shapes::Circle(other){};
        virtual ~Head() = default;

        Head &operator=(const Head &other);
        Head &operator=(const Head &&other);

        math::Vector TorsoAnchorPoint() const;
    };
}