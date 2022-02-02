#include "arm.hpp"

#include <cmath>

#include <iostream>
#include "../../../../math/vector.hpp"

using ::graphics::elements::character::Arm;
using ::math::Vector;
using ::std::cout;
using ::std::endl;

Vector Arm::TorsoAnchorPoint() const
{
    Vector position = get_center_position();

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ - M_PI / 2);
    position[1] += radius * sin(angle_ - M_PI / 2);

    return position;
}

void Arm::Mirror(math::Vector &mirror_point)
{
    Scale(mirror_point, -1, 1);
    angle_ *= -1;
}