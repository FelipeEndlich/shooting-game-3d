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
        virtual void fall() override;
        virtual void jump() override;
        virtual void stop() override;
        virtual void move(Direction direction) override;
    };
}
