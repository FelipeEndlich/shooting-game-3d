#include "arm.hpp"

#include <cmath>

#include "../../../../math/vector.hpp"

using ::graphics::elements::character::Arm;
using ::math::Vector;

Vector Arm::TorsoAnchorPoint() const
{
    Vector position = center_position_;

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ - M_PI / 2);
    position[1] += radius * sin(angle_ - M_PI / 2);

    return position;
}