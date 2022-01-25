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
        virtual void fall() override;
        virtual void jump() override;
        virtual void stop() override;
        virtual void move(Direction direction) override;
    };
}
