#pragma once
#include <string>

namespace game
{
    class Game
    {
    public:
        Game(std::string path);
        virtual ~Game();

        virtual void update(double deltaTime);
        virtual void render(int argc, char **argv);

    private:
        double deltaTime;
    };
}