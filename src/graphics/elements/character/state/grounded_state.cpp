#include "./grounded_state.hpp"

#include "../character.hpp"
#include "./walking_left_state.hpp"
#include "./jumping_state.hpp"
#include "./jumping_right_state.hpp"
#include "./jumping_left_state.hpp"
#include "./walking_right_state.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"
#include "../../../../physics/rigid_body.hpp"

using ::graphics::elements::character::BaseState;
using ::graphics::elements::character::Character;
using ::graphics::elements::character::GroundedState;
using ::graphics::elements::character::JumpingLeftState;
using ::graphics::elements::character::JumpingRightState;
using ::graphics::elements::character::JumpingState;
using ::graphics::elements::character::WalkingLeftState;
using ::graphics::elements::character::WalkingRightState;
using ::math::Vector;
using ::physic::Direction;
using ::physic::ICollidable;
using ::physic::RigidBody;

GroundedState::GroundedState(GroundedState &state)
    : BaseState(state)
{
    name_ = "GroundedState";
}

#include <iostream>
using namespace std;

GroundedState::GroundedState(Character *character)
    : BaseState(character)
{
    character->velocity_ = Vector::Zero(2);
    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = character->get_weight() * -1;

    name_ = "GroundedState";
}

BaseState *GroundedState::Clone()
{
    return new GroundedState(*this);
}

void GroundedState::Jump(double delta_time)
{
    character_->set_state(new JumpingState(character_));
}

void GroundedState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kRight)
        character_->set_state(new JumpingRightState(character_));
    else if (direction == Direction::kLeft)
        character_->set_state(new JumpingLeftState(character_));
}

void GroundedState::Move(double delta_time, Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::kLeft)
    {
        character_->set_state(new WalkingLeftState(character_));
    }
    else if (direction == Direction::kRight)
    {
        character_->set_state(new WalkingRightState(character_));
    }
}