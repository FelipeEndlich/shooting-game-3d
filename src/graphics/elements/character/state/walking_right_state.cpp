#include "./walking_right_state.hpp"

#include <cmath>

#include "../character.hpp"
#include "walk_phase.hpp"
#include "../../../../math/vector.hpp"
#include "../../../../physics/rigid_body.hpp"
#include "../../../../physics/direction.hpp"
#include "../../../../physics/icollidable.hpp"

using graphics::elements::character::BaseState;
using graphics::elements::character::Character;
using graphics::elements::character::WalkingLeftState;
using graphics::elements::character::WalkingRightState;
using graphics::elements::character::WalkPhase;
using math::Vector;
using physic::Direction;
using physic::ICollidable;
using physic::RigidBody;

#include <iostream>
using namespace std;

WalkingRightState::WalkingRightState(WalkingRightState &state)
    : BaseState(state)
{
    name_ = "WalkingRightState";
    phase_ = WalkPhase::kStarting;
}

WalkingRightState::WalkingRightState(Character *character)
    : BaseState(character)
{
    character->velocity_[0] = Character::default_horizontal_velocity_;
    character->velocity_[1] = 0;

    character->acceleration_ = Vector::Zero(2);
    character->external_force_ = character->get_weight() * -1;

    phase_ = WalkPhase::kStarting;

    name_ = "WalkingRightState";

    character_->ResetAnimation();
}

BaseState *WalkingRightState::Clone()
{
    return new WalkingRightState(*this);
}

void WalkingRightState::Jump(double delta_time, physic::Direction direction)
{
    if (direction == Direction::kRight)
        character_->set_state(new JumpingRightState(character_));
}

void WalkingRightState::Stop(double delta_time)
{
    character_->set_state(new GroundedState(character_));
}

void WalkingRightState::Move(double delta_time, Direction direction)
{
    //TODO: if direction is different than current direction then mirror the character
    if (direction == Direction::kLeft)
        character_->set_state(new WalkingLeftState(character_));
    else
    {
        character_->ProcessMove(delta_time);
        Animate();
    }
}

void WalkingRightState::ProcessCollision(ICollidable *collidable)
{
    character_->ProcessCollisionByRight(collidable);
    character_->set_state(new GroundedState(character_));
}

void WalkingRightState::ProcessGravity()
{
    character_->set_state(new FallingRightState(character_));
}

void WalkingRightState::Animate()
{
    Head *head = character_->head_;
    Torso *torso = character_->torso_;
    Arm *left_arm = character_->left_arm_;
    Arm *right_arm = character_->right_arm_;

    Thig *back_thig = right_front_leg_ ? character_->left_thig_ : character_->right_thig_;
    Thig *front_thig = right_front_leg_ ? character_->right_thig_ : character_->left_thig_;

    Calf *back_calf = right_front_leg_ ? character_->left_calf_ : character_->right_calf_;
    Calf *front_calf = right_front_leg_ ? character_->right_calf_ : character_->left_calf_;

    double angle_increment = 0.3;

    if (phase_ == WalkPhase::kContact)
    {
        if (front_thig->get_angle() < front_calf->get_angle())
        {
            front_calf->Rotate(front_calf->ThigAnchorPoint(), -angle_increment);
            back_calf->Rotate(back_calf->ThigAnchorPoint(), angle_increment / 2);
        }
        else
        {
            phase_ = WalkPhase::kDown;
        }
    }
    else if (phase_ == WalkPhase::kDown)
    {
        double max_front_calf_angle = M_PI / 12;

        if (front_calf->get_angle() < max_front_calf_angle)
        {
            front_calf->Rotate(front_calf->ThigAnchorPoint(), angle_increment);

            back_thig->Rotate(back_thig->TorsoAnchorPoint(), -angle_increment / 3);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), -angle_increment / 3);

            back_calf->Rotate(back_calf->ThigAnchorPoint(), angle_increment / 6);
        }
        else
        {
            phase_ = WalkPhase::kPassing;
        }
    }
    else if (phase_ == WalkPhase::kPassing)
    {
        double min_back_thig_angle = -M_PI / 12;

        if (back_thig->get_angle() > min_back_thig_angle)
        {
            back_thig->Rotate(back_thig->TorsoAnchorPoint(), -angle_increment / 2);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), -angle_increment / 2);

            front_thig->Rotate(front_thig->TorsoAnchorPoint(), angle_increment / 2);
            front_calf->Rotate(front_thig->TorsoAnchorPoint(), angle_increment / 2);

            front_calf->Rotate(front_calf->ThigAnchorPoint(), -angle_increment / 2);
        }
        else
        {
            phase_ = WalkPhase::kUp;
            right_front_leg_ = !right_front_leg_;
        }
    }
    else if (phase_ == WalkPhase::kStarting)
    {
        double max_body_angle = M_PI / 24;

        if (head->get_angle() < max_body_angle)
        {
            head->Rotate(head->get_center_position(), angle_increment);
            torso->Rotate(head->get_center_position(), angle_increment);
            back_thig->Rotate(head->get_center_position(), angle_increment);
            back_calf->Rotate(head->get_center_position(), angle_increment);
            front_thig->Rotate(head->get_center_position(), angle_increment);
            front_calf->Rotate(head->get_center_position(), angle_increment);
            left_arm->Rotate(head->get_center_position(), angle_increment);
            right_arm->Rotate(head->get_center_position(), angle_increment);

            back_thig->Rotate(back_thig->TorsoAnchorPoint(), -angle_increment);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), -angle_increment);

            back_calf->Rotate(back_calf->ThigAnchorPoint(), angle_increment);

            front_thig->Rotate(front_thig->TorsoAnchorPoint(), -angle_increment * 3);
            front_calf->Rotate(front_thig->TorsoAnchorPoint(), -angle_increment * 3);

            front_calf->Rotate(front_calf->ThigAnchorPoint(), angle_increment * 9);
        }
        else
        {
            phase_ = WalkPhase::kUp;
        }
    }
    else if (phase_ == WalkPhase::kUp)
    {
        double min_front_leg_angle = -M_PI / 4;

        if (front_thig->get_angle() > min_front_leg_angle)
        {
            front_thig->Rotate(front_thig->TorsoAnchorPoint(), -angle_increment);
            front_calf->Rotate(front_thig->TorsoAnchorPoint(), -angle_increment);

            front_calf->Rotate(front_calf->ThigAnchorPoint(), -angle_increment);

            back_thig->Rotate(back_thig->TorsoAnchorPoint(), angle_increment);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), angle_increment);
        }
        else
        {
            phase_ = WalkPhase::kAir;
        }
    }
    else if (phase_ == WalkPhase::kAir)
    {
        double min_front_calf_angle = 0;
        if (front_calf->get_angle() > min_front_calf_angle)
        {
            front_calf->Rotate(front_calf->ThigAnchorPoint(), -angle_increment);

            back_thig->Rotate(back_thig->TorsoAnchorPoint(), angle_increment / 3);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), angle_increment / 3);

            back_calf->Rotate(back_calf->ThigAnchorPoint(), angle_increment);
        }
        else
        {
            phase_ = WalkPhase::kContact;
        }
    }
}