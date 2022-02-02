#include "shooting_system.hpp"

#include <vector>
#include <algorithm>

#include "bullet.hpp"
#include "../../physics/icollidable.hpp"

using ::graphics::elements::ShootingSystem;
using ::physic::ICollidable;
using ::std::remove;
using ::std::vector;

void ShootingSystem::AddBullet(ICollidable *bullet)
{
    bullets_.push_back(bullet);
}

void ShootingSystem::RemoveBullet(ICollidable *bullet)
{
    bullets_.erase(remove(bullets_.begin(), bullets_.end(), bullet), bullets_.end());
}

void ShootingSystem::AddObstacle(ICollidable *obstacle)
{
    obstacles_.push_back(obstacle);
}

void ShootingSystem::RemoveObstacle(ICollidable *obstacle)
{
    obstacles_.erase(remove(obstacles_.begin(), obstacles_.end(), obstacle), obstacles_.end());
}

void ShootingSystem::AddEnemy(ICollidable *enemy)
{
    enemies_.push_back(enemy);
}

void ShootingSystem::RemoveEnemy(ICollidable *enemy)
{
    enemies_.erase(remove(enemies_.begin(), enemies_.end(), enemy), enemies_.end());
}

void ShootingSystem::set_player(ICollidable *player)
{
    player_ = player;
}

void ShootingSystem::ProcessShoots()
{
    for (auto &bullet : bullets_)
    {
        bool hit = false;

        for (auto &obstacle : obstacles_)
        {
            if (bullet->IsColliding(obstacle))
            {
                hit = true;
                hit_bullets_.push_back(bullet);
                break;
            }
        }

        if (!hit)
        {
            for (auto &enemy : enemies_)
            {
                if (bullet->IsColliding(enemy))
                {
                    hit = true;
                    hit_enemies_.push_back(enemy);
                    hit_bullets_.push_back(bullet);
                    break;
                }
            }
        }

        if (!hit && bullet->IsColliding(player_))
        {
            hit_bullets_.push_back(bullet);
            player_hit_ = true;
        }
    }

    for (auto &bullet : hit_bullets_)
        RemoveBullet(bullet);

    for (auto &enemy : hit_enemies_)
        RemoveEnemy(enemy);
}