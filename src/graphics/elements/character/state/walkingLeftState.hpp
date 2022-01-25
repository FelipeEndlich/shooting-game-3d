#pragma once

#include "state.hpp"

namespace graphics::elements::character
{
    class Character;

    class WalkingLeftState : public State
    {
    public:
        WalkingLeftState(WalkingLeftState &state);
        WalkingLeftState(Character *character);
        ~WalkingLeftState() {}

        virtual State *clone() override;
        virtual void fall(double deltaTime) override;
        virtual void jump(double deltaTime) override;
        virtual void stop(double deltaTime) override;
        virtual void move(double deltaTime, Direction direction) override;
    };
}
