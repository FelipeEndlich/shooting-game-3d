#pragma once

#include "state.hpp"

namespace graphics::elements::state
{
    class Character;

    class GroundedState : public BaseState
    {
    public:
        GroundedState(GroundedState &state);
        GroundedState(Character *character);
        virtual ~GroundedState();

        virtual BaseState *Clone() override;
        virtual void Fall(double delta_time) override;
        virtual void Jump(double delta_time) override;
        virtual void Stop(double delta_time) override;
        virtual void Move(double delta_time, Direction direction) override;
    };
}
