#include "torso.hpp"

#include <iostream>
#include <cmath>

#include "../../../../math/vector.hpp"

using ::graphics::elements::character::Torso;
using ::math::Vector;
using ::std::cout;
using ::std::endl;

Vector Torso::HeadAnchorPoint() const
{
    Vector position = get_center_position();

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ - M_PI / 2);
    position[1] += radius * sin(angle_ - M_PI / 2);
    return position;
}

Vector Torso::LeftArmAnchorPoint() const
{
    Vector position = get_center_position();

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ - M_PI / 2);
    position[1] += radius * sin(angle_ - M_PI / 2);

    return position;
}

Vector Torso::LeftThigAnchorPoint() const
{
    Vector position = get_center_position();

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ + M_PI / 2);
    position[1] += radius * sin(angle_ + M_PI / 2);
    return position;
}

Vector Torso::RightArmAnchorPoint() const
{
    return LeftArmAnchorPoint();
}

Vector Torso::RightThigAnchorPoint() const
{
    return LeftThigAnchorPoint();
}

void Torso::Mirror(math::Vector &mirror_point)
{
    Scale(mirror_point, -1, 1);
    angle_ *= -1;
}