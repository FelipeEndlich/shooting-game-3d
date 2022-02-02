#include "icollidable.hpp"

#include "../math/vector.hpp"

using ::math::Vector;
using ::physic::ICollidable;

bool ICollidable::IsColliding(double position_x, double position_y, double width, double height)
{
    return get_position()[0] < position_x + width && get_position()[0] + get_width() > position_x && get_position()[1] < position_y + height && get_position()[1] + get_height() > position_y;
}

bool ICollidable::IsColliding(math::Vector position, double width, double height)
{
    return IsColliding(position[0], position[1], width, height);
}

bool ICollidable::IsColliding(ICollidable *collidable)
{
    return IsColliding(collidable->get_position(), collidable->get_width(), collidable->get_height());
}