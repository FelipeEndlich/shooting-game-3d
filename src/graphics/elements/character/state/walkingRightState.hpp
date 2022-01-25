#pragma once

#include "state.hpp"

namespace graphics::elements::character
{
    class Character;

    class WalkingRightState : public State
    {
    public:
        WalkingRightState(WalkingRightState &state);
        WalkingRightState(Character *character);
        ~WalkingRightState() {}

        virtual State *clone() override;
        virtual void fall() override;
        virtual void jump() override;
        virtual void stop() override;
        virtual void move(Direction direction) override;
    };
}
