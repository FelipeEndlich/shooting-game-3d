#include "torso.hpp"

#include <cmath>

#include "../../../../math/vector.hpp"

using ::graphics::elements::character::Torso;
using ::math::Vector;

Vector Torso::HeadAnchorPoint() const
{
    Vector position = center_position_;

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ - M_PI / 2);
    position[1] += radius * sin(angle_ - M_PI / 2);
    return position;
}

Vector Torso::LeftArmAnchorPoint() const
{
    Vector position = center_position_;

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ - M_PI / 2);
    position[1] += radius * sin(angle_ - M_PI / 2);
    return position;
}

Vector Torso::LeftThighAnchorPoint() const
{
    Vector position = center_position_;

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ + M_PI / 2);
    position[1] += radius * sin(angle_ + M_PI / 2);
    return position;
}

Vector Torso::RightArmAnchorPoint() const
{
    return LeftArmAnchorPoint();
}

Vector Torso::RightThighAnchorPoint() const
{
    return LeftThighAnchorPoint();
}