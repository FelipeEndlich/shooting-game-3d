#pragma once

#include "state.hpp"

namespace graphics::elements::character
{
    class Character;

    class GroundedState : public State
    {
    public:
        GroundedState(GroundedState &state);
        GroundedState(Character *character);
        virtual ~GroundedState();

        virtual State *clone() override;
        virtual void fall(double deltaTime) override;
        virtual void jump(double deltaTime) override;
        virtual void stop(double deltaTime) override;
        virtual void move(double deltaTime, Direction direction) override;
    };
}
