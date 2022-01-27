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
        virtual ~Map();

        void set_background(shapes::Rectangle *background);
        double get_width() const;
        double get_height() const;

        void AddObstacle(Obstacle *obstacle);
        void Render();

    private:
        shapes::Rectangle* background_;
        std::vector<Obstacle*> obstacles_;
    };
}