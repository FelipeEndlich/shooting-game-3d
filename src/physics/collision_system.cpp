#include "collision_system.hpp"

#include <algorithm>

#include "icollidable.hpp"

using ::physic::CollisionSystem;
using ::physic::ICollidable;

void CollisionSystem::AddToCollisionSystem(ICollidable *collidable)
{
    m_collidables_.push_back(collidable);
}

void CollisionSystem::RemoveFromCollisionSystem(ICollidable *collidable)
{
    m_collidables_.erase(std::remove(m_collidables_.begin(), m_collidables_.end(), collidable), m_collidables_.end());
}

void CollisionSystem::ProcessCollisions()
{
    for (auto &collidable : m_collidables_)
        for (auto &other : m_collidables_)
            if (collidable != other)
                if (collidable->get_position()[0] + collidable->get_width() > other->get_position()[0] &&
                    collidable->get_position()[0] < other->get_position()[0] + other->get_width() &&
                    collidable->get_position()[1] + collidable->get_height() > other->get_position()[1] &&
                    collidable->get_position()[1] < other->get_position()[1] + other->get_height())
                    collidable->ProcessCollision(other);
}