#pragma once

#include "../math/vector.hpp"

#include "direction.hpp"

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

        virtual void ProcessCollision(ICollidable *collidable, Direction direction) = 0;
    };
}