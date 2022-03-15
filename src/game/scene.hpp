#pragma once

#include <vector>
#include "../graphics/shapes/cuboid.hpp"

namespace game {
    class GameScene {
        public:
            GameScene(char const* scene_path);
            ~GameScene() {}

            void Draw();

        private:
            graphics::shapes::Cuboid* hero;
            graphics::shapes::Cuboid* background;
            std::vector<graphics::shapes::Cuboid*> obstacles;
            std::vector<graphics::shapes::Cuboid*> enemies;
    };
}