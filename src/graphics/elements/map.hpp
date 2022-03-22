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

        void set_height(double height);
        void set_width(double width);

        double get_width() const;
        double get_height() const;
        double get_depth() const;

        double get_x() const;
        double get_y() const;
        double get_z() const;

        void AddObstacle(Obstacle *obstacle);
        void Render();

    private:
        double width_;
        double height_;
        double depth_;
        std::vector<Obstacle *> obstacles_;
    };
}