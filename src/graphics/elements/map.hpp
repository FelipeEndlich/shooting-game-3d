#pragma once

#include "../shapes/rectangle.hpp"
#include "../shapes/circle.hpp"
#include <vector>

namespace graphics
{
    namespace elements
    {
        class Map
        {
        public:
            Map() = default;
            virtual ~Map() = default;

            void setBackground(const shapes::Rectangle& background);

            void render();

        private:
            shapes::Rectangle background;
        };
    }
}