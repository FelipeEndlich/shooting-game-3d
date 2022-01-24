#pragma once

namespace game
{
    class Game
    {
    public:
        Game();
        virtual ~Game();

        virtual void update(double deltaTime);
        virtual void render();

    private:
        double deltaTime;
    };
}