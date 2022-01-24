#include "map.hpp"
#include "../shapes/rectangle.hpp"

using namespace graphics::elements;
using namespace graphics::shapes;

void Map::setBackground(const Rectangle &background)
{
    this->background = background;
}

void Map::render()
{
    background.draw();

    for (auto &obstacle : obstacles)
        obstacle.render();
}

double Map::getWidth() const
{
    return background.getWidth();
}

double Map::getHeight() const
{
    return background.getHeight();
}

void Map::addObstacle(const Obstacle &obstacle)
{
    obstacles.push_back(obstacle);
}