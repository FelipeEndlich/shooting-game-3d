#pragma once
#include "rgba.hpp"
#include <string>

namespace graphics
{
    namespace color
    {
        class RGBAFactory
        {
        public:
            enum Color
            {
                BLACK
            };

            static RGBA getColor(Color color);
            static RGBA getColor(std::string color);
        };
    }
}