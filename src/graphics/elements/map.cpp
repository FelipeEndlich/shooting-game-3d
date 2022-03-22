#include "map.hpp"

#include "../shapes/cuboid.hpp"
#include "../elements/obstacle.hpp"

using ::graphics::elements::Map;
using ::graphics::elements::Obstacle;
using ::graphics::shapes::Cuboid;

Map::~Map()
{
    for (auto obstacle : obstacles_)
        delete obstacle;
}

void Map::Render()
{
    for (auto &obstacle : obstacles_)
        obstacle->Render();
}

void Map::set_height(double height)
{
    this->height_ = height;
}
void Map::set_width(double width)
{
    this->width_ = width;
}

double Map::get_width() const
{
    return width_;
}

double Map::get_height() const
{
    return height_;
}

double Map::get_depth() const
{
    return depth_;
}

void Map::AddObstacle(Obstacle *obstacle)
{
    obstacles_.push_back(obstacle);
}