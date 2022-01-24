#include "rgbaFactory.hpp"
#include <algorithm>
using namespace graphics::color;

RGBA RGBAFactory::getColor(Color color)
{
    switch (color)
    {
    case BLACK:
        return RGBA(0, 0, 0);
    case BLUE:
        return RGBA(0, 0, 255);
    case RED:
        return RGBA(255, 0, 0);
    case GREEN:
        return RGBA(0, 255, 0);
    default:
        return RGBA(0, 0, 0);
    }
}

RGBA RGBAFactory::getColor(std::string strColor)
{
    strColor.erase(std::remove(strColor.begin(), strColor.end(), ' '), strColor.end());
    std::transform(strColor.begin(), strColor.end(), strColor.begin(), ::tolower);

    Color color = BLACK;
    if (strColor == "black")
        color = BLACK;
    else if (strColor == "blue")
        color = BLUE;
    else if (strColor == "red")
        color = RED;
    else if (strColor == "green")
        color = GREEN;

    return getColor(color);
}
