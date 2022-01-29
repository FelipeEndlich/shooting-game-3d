#include "head.hpp"

#include <cmath>

#include "../../../shapes/circle.hpp"

#include "../../../color/rgba.hpp"
#include "../../../../math/vector.hpp"

using ::graphics::color::RGBA;
using ::graphics::elements::character::Head;
using ::graphics::shapes::Circle;
using ::math::Vector;

Head &Head::operator=(const Head &other)
{
    Circle::operator=(other);
    return *this;
}

Head &Head::operator=(const Head &&other)
{
    Circle::operator=(other);
    return *this;
}

Vector Head::TorsoAnchorPoint() const
{
    Vector position = center_position_;
    position[0] += radius_ * cos(angle_ + M_PI / 2);
    position[1] += radius_ * sin(angle_ + M_PI / 2);
    return position;
}