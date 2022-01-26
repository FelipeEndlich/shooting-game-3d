#pragma once

#include "icollidable.hpp"

#include <vector>

namespace physic
{
    class CollisionSystem
    {
    public:
        void AddToCollisionSystem(ICollidable* collidable);
        void RemoveFromCollisionSystem(ICollidable* collidable);
        void ProcessCollisions();

    private:
        std::vector<ICollidable*> m_collidables_;
    };
}