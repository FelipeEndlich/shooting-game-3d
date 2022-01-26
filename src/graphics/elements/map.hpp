#pragma once

#include "../shapes/rectangle.hpp"
#include "obstacle.hpp"
#include <vector>

namespace graphics::elements
{
        class Map
        {
        public:
            Map() = default;
            virtual ~Map() = default;

            void setBackground(const shapes::Rectangle &background);
            void addObstacle(const Obstacle &obstacle);
            double getWidth() const;
            double getHeight() const;

            void render();

        private:
            shapes::Rectangle background;
            std::vector<Obstacle> obstacles;
        };
}