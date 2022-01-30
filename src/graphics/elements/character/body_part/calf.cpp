#include "calf.hpp"

#include <cmath>

#include "../../../../math/vector.hpp"

using ::graphics::elements::character::Calf;
using ::math::Vector;

Vector Calf::ThigAnchorPoint() const
{
    Vector position = get_center_position();

    double radius = height_ / 2;

    position[0] += radius * cos(angle_ - M_PI / 2);
    position[1] += radius * sin(angle_ - M_PI / 2);

    return position;
}

void Calf::Mirror(math::Vector &mirror_point)
{
    Scale(mirror_point, -1, 1);
    angle_ *= -1;
}