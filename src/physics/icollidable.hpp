#pragma once

#include "../math/vector.hpp"

namespace physic
{
    class ICollidable
    {
    public:
        ICollidable() = default;
        virtual ~ICollidable() = default;

        virtual math::Vector get_position() = 0;
        virtual double get_width() = 0;
        virtual double get_height() = 0;

        bool IsColliding(double position_x, double position_y, double width, double height);
        bool IsColliding(math::Vector position, double width, double height);
        bool IsColliding(ICollidable *collidable);

        virtual void ProcessCollision(ICollidable *collidable) = 0;
        virtual void ProcessGravity() = 0;
    };
}