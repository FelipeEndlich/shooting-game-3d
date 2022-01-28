#include "./jumping_state.hpp"

#include "../character.hpp"
#include "./grounded_state.hpp"
#include "./jumping_left_state.hpp"
#include "./jumping_right_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using graphics::elements::state::BaseState;
using graphics::elements::state::Character;
using graphics::elements::state::GroundedState;
using graphics::elements::state::JumpingLeftState;
using graphics::elements::state::JumpingRightState;
using graphics::elements::state::JumpingState;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

JumpingState::JumpingState(JumpingState &state)
    : BaseState(state)
{
    name_ = "JumpingState";
}

JumpingState::JumpingState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = 0;
    if (character->velocity_[1] == 0)
        character->velocity_ = character->initial_jump_velocity_;
    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = Vector::Zero(2);

    name_ = "JumpingState";
}

BaseState *JumpingState::Clone()
{
    return new JumpingState(*this);
}

void JumpingState::Jump(double delta_time)
{
    if (character_->velocity_[1] > 0)
        character_->set_state(new FallingState(character_));
    else
        character_->ProcessMove(delta_time);
}

void JumpingState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kRight)
        character_->set_state(new JumpingRightState(character_));
    else
        character_->set_state(new JumpingLeftState(character_));
}

void JumpingState::Stop(double delta_time)
{
    character_->set_state(new FallingState(character_));
}

void JumpingState::Move(double delta_time, Direction direction)
{
}

void JumpingState::ProcessCollision(ICollidable *collidable)
{
    character_->ProcessCollisionByTop(collidable);
    character_->set_state(new FallingState(character_));
}

void JumpingState::ProcessGravity()
{
}
