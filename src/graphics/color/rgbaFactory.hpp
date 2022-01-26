#pragma once
#include "rgba.hpp"
#include <string>

namespace graphics::color
{
    class RGBAFactory
    {
    public:
        enum Color
        {
            BLACK,
            BLUE,
            RED,
            GREEN
        };

        static RGBA getColor(Color color);
        static RGBA getColor(std::string color);
    };
}