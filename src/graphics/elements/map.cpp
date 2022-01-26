#include "map.hpp"

#include "../shapes/rectangle.hpp"
#include "../elements/obstacle.hpp"

using ::graphics::elements::Map;
using ::graphics::elements::Obstacle;
using ::graphics::shapes::Rectangle;

void Map::set_background(const Rectangle &background)
{
    this->background_ = background;
}

void Map::Render()
{
    background_.draw();

    for (auto &obstacle : obstacles_)
        obstacle.Render();
}

double Map::get_width() const
{
    return background_.getWidth();
}

double Map::get_height() const
{
    return background_.getHeight();
}

void Map::AddObstacle(const Obstacle &obstacle)
{
    obstacles_.push_back(obstacle);
}