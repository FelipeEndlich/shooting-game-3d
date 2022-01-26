#pragma once

#include "obstacle.hpp"

#include <vector>

#include "../shapes/rectangle.hpp"

namespace graphics::elements
{
    class Map
    {
    public:
        Map() = default;
        virtual ~Map() = default;

        void set_background(const shapes::Rectangle &background);
        double get_width() const;
        double get_height() const;

        void AddObstacle(const Obstacle &obstacle);
        void Render();

    private:
        shapes::Rectangle background_;
        std::vector<Obstacle> obstacles_;
    };
}