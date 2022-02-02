#pragma once

#include <vector>

#include "bullet.hpp"
#include "../../physics/icollidable.hpp"

namespace graphics::elements
{
    class ShootingSystem
    {
    public:
        void AddBullet(physic::ICollidable *bullet);
        void RemoveBullet(physic::ICollidable *bullet);

        void AddObstacle(physic::ICollidable *obstacle);
        void RemoveObstacle(physic::ICollidable *obstacle);

        void AddEnemy(physic::ICollidable *enemy);
        void RemoveEnemy(physic::ICollidable *enemy);

        void set_player(physic::ICollidable *player);

        void ProcessShoots();

        std::vector<physic::ICollidable *> hit_bullets_;
        std::vector<physic::ICollidable *> hit_enemies_;
        bool player_hit_ = false;

    private:
        std::vector<physic::ICollidable *> bullets_;
        std::vector<physic::ICollidable *> obstacles_;
        std::vector<physic::ICollidable *> enemies_;
        physic::ICollidable *player_;
    };
}