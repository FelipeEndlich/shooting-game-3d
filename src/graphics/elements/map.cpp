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
}