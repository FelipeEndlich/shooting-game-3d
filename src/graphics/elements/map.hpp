#pragma once

#include "obstacle.hpp"

#include <vector>

#include "../shapes/cuboid.hpp"

namespace graphics::elements
{
    class Map
    {
    public:
        Map() = default;
        virtual ~Map();

        double set_height(double height);
        double set_width(double width);

        double get_width() const;
        double get_height() const;

        void AddObstacle(Obstacle *obstacle);
        void Render();

    private:
        double width_;
        double height_;
        std::vector<Obstacle *> obstacles_;
    };
}