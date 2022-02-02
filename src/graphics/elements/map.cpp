#include "map.hpp"

#include "../shapes/rectangle.hpp"
#include "../elements/obstacle.hpp"

using ::graphics::elements::Map;
using ::graphics::elements::Obstacle;
using ::graphics::shapes::Rectangle;

void Map::set_background(Rectangle *background)
{
    background_ = background;
}

Map::~Map()
{
    delete background_;
    for (auto obstacle : obstacles_)
        delete obstacle;
}

void Map::Render()
{
    background_->Draw();

    for (auto &obstacle : obstacles_)
        obstacle->Render();
}

double Map::get_width() const
{
    return background_->get_width();
}

double Map::get_height() const
{
    return background_->get_height();
}

void Map::AddObstacle(Obstacle *obstacle)
{
    obstacles_.push_back(obstacle);
}