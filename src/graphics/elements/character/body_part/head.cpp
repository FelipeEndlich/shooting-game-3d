#include "head.hpp"

#include <cmath>

#include "../../../../math/vector.hpp"

using ::graphics::elements::character::Head;
using ::math::Vector;

Vector Head::TorsoAnchorPoint() const
{
    Vector position = center_position_;
    position[0] += radius_ * cos(angle_ + M_PI / 2);
    position[1] += radius_ * sin(angle_ + M_PI / 2);
    return position;
}