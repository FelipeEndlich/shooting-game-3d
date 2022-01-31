#pragma once

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include "../ext/tinyxml2.hpp"
#include "../graphics/elements/map.hpp"
#include "../graphics/elements/character/character.hpp"
#include "../physics/collision_system.hpp"
#include "../physics/gravity_constraint_system.hpp"

namespace shoot_and_jump
{
    class Game
    {
    public:
        Game(std::string path);
        virtual ~Game();

        void Update(double delta_time);
        void Run(int argc, char **argv);

        void Idle();
        void Display();
        void KeyPressed(unsigned char key, int x, int y);
        void KeyReleased(unsigned char key, int x, int y);
        void BindMouseButton(int button, int state, int x, int y);
        void BindMouseMotion(int x, int y);

    private:
        double delta_time_;
        double current_time_;

        graphics::elements::Map map_;
        graphics::elements::character::Character *player_;
        std::vector<graphics::elements::character::Character *> enemies_;

        std::map<char, bool> keys_;
        std::map<int, bool> mouse_;
        std::tuple<int, int> mouse_position_;

        double ortho_left_;
        double ortho_right_;
        double ortho_bottom_;
        double ortho_top_;
        double ortho_near_;
        double ortho_far_;

        double window_width_;
        double window_height_;

        physic::CollisionSystem collision_system_;
        physic::GravityConstraintSystem gravity_constraint_system_;

        void Allocate();
        void Deallocate();

        void LoadMap(std::string path);
        void LoadBackground(tinyxml2::XMLElement *background);
        void LoadObstacle(tinyxml2::XMLElement *obstacle);
        void LoadPlayer(tinyxml2::XMLElement *player);
        void LoadEnemy(tinyxml2::XMLElement *enemy);

        void CheckKeys();
    };
}