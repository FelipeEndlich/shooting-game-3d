#pragma once
#include <string>
#include "../ext/tinyxml2.hpp"
#include "../graphics/elements/map.hpp"
#include "../graphics/elements/character.hpp"
#include <vector>
#include <map>

namespace game
{
    class Game
    {
    public:
        Game(std::string path);
        virtual ~Game() = default;

        void update(double deltaTime);
        void run(int argc, char **argv);

        void idle();
        void display();
        void keyPressed(unsigned char key, int x, int y);
        void keyReleased(unsigned char key, int x, int y);
        void bindMouse(int button, int state, int x, int y);

    private:
        double deltaTime;
        graphics::elements::Map map;
        graphics::elements::Character player;
        std::vector<graphics::elements::Character> enemies;

        std::map<char, bool> keys;
        std::map<int, bool> mouse;

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

        void checkKeys();
    };
}