#include "rgba_factory.hpp"

#include <algorithm>

using ::graphics::color::ColorOption;
using ::graphics::color::RGBA;
using ::graphics::color::RGBAFactory;

RGBA RGBAFactory::get_color(ColorOption color)
{
    switch (color)
    {
    case kBlack:
        return RGBA(0, 0, 0);
    case kBlue:
        return RGBA(0, 0, 255);
    case kRed:
        return RGBA(255, 0, 0);
    case kGreen:
        return RGBA(0, 255, 0);
    case kWhite:
        return RGBA(255, 255, 255);
    default:
        return RGBA(0, 0, 0);
    }
}

RGBA RGBAFactory::get_color(std::string str_color)
{
    str_color.erase(std::remove(str_color.begin(), str_color.end(), ' '), str_color.end());
    std::transform(str_color.begin(), str_color.end(), str_color.begin(), ::tolower);

    ColorOption color = kBlack;
    if (str_color == "black")
        color = kBlack;
    else if (str_color == "blue")
        color = kBlue;
    else if (str_color == "red")
        color = kRed;
    else if (str_color == "green")
        color = kGreen;
    else if (str_color == "white")
        color = kWhite;

    return get_color(color);
}
