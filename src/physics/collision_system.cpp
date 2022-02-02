#include "collision_system.hpp"

#include <algorithm>
#include <vector>

#include "icollidable.hpp"

using ::physic::CollisionSystem;
using ::physic::ICollidable;
using ::std::tuple;
using ::std::vector;

void CollisionSystem::AddToCollisionSystem(ICollidable *collidable)
{
    m_collidables_.push_back(collidable);
}

void CollisionSystem::RemoveFromCollisionSystem(ICollidable *collidable)
{
    m_collidables_.erase(std::remove(m_collidables_.begin(), m_collidables_.end(), collidable), m_collidables_.end());
}

#include <iostream>
using namespace std;
void CollisionSystem::ProcessCollisions()
{
    for (auto &collidable : m_collidables_)
        for (auto &other_collidable : m_collidables_)
            if (collidable != other_collidable)
                if (collidable->IsColliding(other_collidable))
                    collidable->ProcessCollision(other_collidable);
    // if (collidable->get_position()[0] < other_collidable->get_position()[0] + other_collidable->get_width() &&
    //     collidable->get_position()[0] + collidable->get_width() > other_collidable->get_position()[0] &&
    //     collidable->get_position()[1] < other_collidable->get_position()[1] + other_collidable->get_height() &&
    //     collidable->get_position()[1] + collidable->get_height() > other_collidable->get_position()[1])
    //     collidable->ProcessCollision(other_collidable);
}