#pragma once
#include <string>
#include "../ext/tinyxml2.hpp"
#include "../graphics/elements/map.hpp"
#include "../graphics/elements/character.hpp"
#include <vector>

namespace game
{
    class Game
    {
    public:
        Game(std::string path);
        virtual ~Game() = default;

        virtual void update(double deltaTime);
        virtual void render(int argc, char **argv);

    private:
        double deltaTime;
        graphics::elements::Map map;
        graphics::elements::Character player;
        std::vector<graphics::elements::Character> enemies;

        double orthoLeft;
        double orthoRight;
        double orthoBottom;
        double orthoTop;
        double orthoNear;
        double orthoFar;

        void loadMap(std::string path);
        void loadBackground(tinyxml2::XMLElement *background);
        void loadObstacle(tinyxml2::XMLElement *obstacle);
        void loadPlayer(tinyxml2::XMLElement *player);
        void loadEnemy(tinyxml2::XMLElement *enemy);
    };
}