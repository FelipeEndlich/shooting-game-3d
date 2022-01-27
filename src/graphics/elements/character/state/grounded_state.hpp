#pragma once

#include "base_state.hpp"

#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"

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
        virtual void Jump(double delta_time) override;
        virtual void Stop(double delta_time) override;
        virtual void Move(double delta_time, physic::Direction direction) override;
        virtual void ProcessCollision(physic::ICollidable *collidable) override;
    };
}
