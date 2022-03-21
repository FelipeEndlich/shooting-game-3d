#include "map.hpp"

#include "../shapes/cuboid.hpp"
#include "../elements/obstacle.hpp"

using ::graphics::elements::Map;
using ::graphics::elements::Obstacle;
using ::graphics::shapes::Cuboid;

void Map::set_right_wall(Cuboid *background)
{
    right_wall_ = background;
}

void Map::set_left_wall(shapes::Cuboid *background)
{
    left_wall_ = background;
}

void Map::set_front_wall(shapes::Cuboid *background)
{
    front_wall_ = background;
}

void Map::set_back_wall(shapes::Cuboid *background)
{
    back_wall_ = background;
}

void Map::set_floor(shapes::Cuboid *background)
{
    floor_ = background;
}

void Map::set_ceil(shapes::Cuboid *background)
{
    ceil_ = background;
}

Map::~Map()
{
    delete right_wall_;
    for (auto obstacle : obstacles_)
        delete obstacle;
}

void Map::Render()
{
    front_wall_->Draw();
    back_wall_->Draw();
    right_wall_->Draw();
    left_wall_->Draw();
    floor_->Draw();
    ceil_->Draw();

    for (auto &obstacle : obstacles_)
        obstacle->Render();
}

double Map::get_width() const
{
    return right_wall_->get_width();
}

double Map::get_height() const
{
    return right_wall_->get_height();
}

void Map::AddObstacle(Obstacle *obstacle)
{
    obstacles_.push_back(obstacle);
}