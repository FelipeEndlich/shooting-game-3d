#pragma once

#include <string>

#include "rgba.hpp"
#include "color_option.hpp"

namespace graphics::color
{
    class RGBAFactory
    {
    public:
        static RGBA get_color(ColorOption color);
        static RGBA get_color(std::string color);
    };
}