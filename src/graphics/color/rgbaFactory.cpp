#include "rgbaFactory.hpp"
#include <algorithm>
using namespace graphics::color;

RGBA RGBAFactory::getColor(Color color)
{
    switch (color)
    {
    case BLACK:
        return RGBA(0, 0, 0);
    default:
        return RGBA(0, 0, 0);
    }
}

RGBA RGBAFactory::getColor(std::string color)
{
    color.erase(std::remove(color.begin(), color.end(), ' '), color.end());
    std::transform(color.begin(), color.end(), color.begin(), ::tolower);

    if (color == "black")
    {
        return RGBA(0, 0, 0);
    }
    else
    {
        return RGBA(0, 0, 0);
    }
}
