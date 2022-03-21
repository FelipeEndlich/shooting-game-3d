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

        void set_right_wall(shapes::Cuboid *background);
        void set_left_wall(shapes::Cuboid *background);
        void set_front_wall(shapes::Cuboid *background);
        void set_back_wall(shapes::Cuboid *background);
        void set_floor(shapes::Cuboid *background);
        void set_ceil(shapes::Cuboid *background);
        
        double get_width() const;
        double get_height() const;

        void AddObstacle(Obstacle *obstacle);
        void Render();

    private:
        shapes::Cuboid *right_wall_;
        shapes::Cuboid *left_wall_;
        shapes::Cuboid *front_wall_;
        shapes::Cuboid *back_wall_;
        shapes::Cuboid *floor_;
        shapes::Cuboid *ceil_;
        std::vector<Obstacle *> obstacles_;
    };
}