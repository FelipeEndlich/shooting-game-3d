#include "walking_animation_system.hpp"

#include <map>
#include <tuple>

#include "../character.hpp"

using graphics::elements::character::Character;
using ::graphics::elements::character::WalkingAnimationSystem;
using ::std::get;
using ::std::tuple;

WalkingAnimationSystem::WalkingAnimationSystem(Character *character)
    : character_(character)
{
    character_ = character;
    phase_ = WalkPhase::kStarting;

    phase_info_["head"] = {
        {WalkPhase::kStarting, {0.0, 0.15}},
    };

    phase_info_["torso"] = {
        {WalkPhase::kStarting, {0.0, 0.15}},
    };

    phase_info_["back_thig"] = {
        {WalkPhase::kStarting, {0.0, 0.25}},
        {WalkPhase::kAir, {0.25, 0.45}},
        {WalkPhase::kContact, {0.45, 0.55}},
        {WalkPhase::kPassing, {0.55, -0.35}},
        {WalkPhase::kUp, {-0.15, 0.25}}};

    phase_info_["back_calf"] = {
        {WalkPhase::kStarting, {0.0, 0.45}},
        {WalkPhase::kAir, {0.45, 0.75}},
        {WalkPhase::kContact, {0.75, 1.55}},
        {WalkPhase::kDown, {1.55, 1.85}},
        {WalkPhase::kUp, {0.25, 0.45}}};

    phase_info_["front_thig"] = {
        {WalkPhase::kStarting, {0.0, -0.55}},
        {WalkPhase::kAir, {-0.55, -0.65}},
        {WalkPhase::kPassing, {-0.65, -0.15}},
        {WalkPhase::kUp, {-0.35, -0.55}}};

    phase_info_["front_calf"] = {
        {WalkPhase::kStarting, {0.0, 0.25}},
        {WalkPhase::kAir, {0.25, 0.1}},
        {WalkPhase::kContact, {0.1, -0.65}},
        {WalkPhase::kDown, {-0.65, 0.25}},
        {WalkPhase::kUp, {0.95, 0.25}}};

    if (!character->looking_right_)
    {
        for (auto &[key, value] : phase_info_)
        {
            for (auto &[phase, angle] : value)
            {
                get<0>(angle) *= -1;
                get<1>(angle) *= -1;
            }
        }
    }
}

void WalkingAnimationSystem::Animate()
{
    Head *head = character_->head_;
    Torso *torso = character_->torso_;
    Arm *left_arm = character_->left_arm_;
    Arm *right_arm = character_->right_arm_;

    Thig *back_thig = right_front_leg_ ? character_->left_thig_ : character_->right_thig_;
    Thig *front_thig = right_front_leg_ ? character_->right_thig_ : character_->left_thig_;

    Calf *back_calf = right_front_leg_ ? character_->left_calf_ : character_->right_calf_;
    Calf *front_calf = right_front_leg_ ? character_->right_calf_ : character_->left_calf_;

    double angle_increment = 0.01;

    if (phase_ == WalkPhase::kContact)
    {
        double front_calf_final_angle = std::get<1>(phase_info_["front_calf"][WalkPhase::kContact]);
        double front_calf_increment = CalculateIncrement(phase_info_["front_calf"][WalkPhase::kContact]);

        if (!IsDoubleEq(front_calf->get_angle(), front_calf_final_angle, 0.01))
        {
            front_calf->Rotate(front_calf->ThigAnchorPoint(), front_calf_increment);

            double back_thig_increment = CalculateIncrement(phase_info_["back_thig"][WalkPhase::kContact]);
            back_thig->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);

            double back_calf_increment = CalculateIncrement(phase_info_["back_calf"][WalkPhase::kContact]) - back_thig_increment;
            back_calf->Rotate(back_calf->ThigAnchorPoint(), back_calf_increment);
        }
        else
        {
            phase_ = WalkPhase::kDown;
        }
    }
    else if (phase_ == WalkPhase::kDown)
    {
        double front_calf_final_angle = std::get<1>(phase_info_["front_calf"][WalkPhase::kDown]);
        double front_calf_increment = CalculateIncrement(phase_info_["front_calf"][WalkPhase::kDown]);

        if (!IsDoubleEq(front_calf->get_angle(), front_calf_final_angle, 0.01))
        {
            front_calf->Rotate(front_calf->ThigAnchorPoint(), front_calf_increment);

            double back_thig_increment = CalculateIncrement(phase_info_["back_thig"][WalkPhase::kDown]);
            back_thig->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);

            double back_calf_increment = CalculateIncrement(phase_info_["back_calf"][WalkPhase::kDown]) - back_thig_increment;
            back_calf->Rotate(back_calf->ThigAnchorPoint(), back_calf_increment);
        }
        else
        {
            phase_ = WalkPhase::kPassing;
        }
    }
    else if (phase_ == WalkPhase::kPassing)
    {
        double front_thig_final_angle = std::get<1>(phase_info_["front_thig"][WalkPhase::kPassing]);
        double front_thig_increment = CalculateIncrement(phase_info_["front_thig"][WalkPhase::kPassing]);

        if (!IsDoubleEq(front_thig->get_angle(), front_thig_final_angle, 0.01))
        {
            front_thig->Rotate(front_thig->TorsoAnchorPoint(), front_thig_increment);
            front_calf->Rotate(front_thig->TorsoAnchorPoint(), front_thig_increment);

            double front_calf_increment = -front_thig_increment;
            front_calf->Rotate(front_calf->ThigAnchorPoint(), front_calf_increment);

            double back_thig_increment = CalculateIncrement(phase_info_["back_thig"][WalkPhase::kPassing]);
            back_thig->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);
        }
        else
        {
            phase_ = WalkPhase::kUp;
            right_front_leg_ = !right_front_leg_;
        }
    }

    else if (phase_ == WalkPhase::kUp)
    {
        double front_thig_final_angle = std::get<1>(phase_info_["front_thig"][WalkPhase::kUp]);
        double front_thig_increment = CalculateIncrement(phase_info_["front_thig"][WalkPhase::kUp]);

        if (!IsDoubleEq(front_thig->get_angle(), front_thig_final_angle, 0.01))
        {
            front_thig->Rotate(front_thig->TorsoAnchorPoint(), front_thig_increment);
            front_calf->Rotate(front_thig->TorsoAnchorPoint(), front_thig_increment);

            double front_calf_increment = CalculateIncrement(phase_info_["front_calf"][WalkPhase::kUp]) - front_thig_increment;
            front_calf->Rotate(front_calf->ThigAnchorPoint(), front_calf_increment);

            double back_thig_increment = CalculateIncrement(phase_info_["back_thig"][WalkPhase::kUp]);
            back_thig->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);

            double back_calf_increment = CalculateIncrement(phase_info_["back_calf"][WalkPhase::kUp]) - back_thig_increment;
            back_calf->Rotate(back_calf->ThigAnchorPoint(), back_calf_increment);
        }
        else
        {
            phase_ = WalkPhase::kAir;
        }
    }
    else if (phase_ == WalkPhase::kStarting)
    {
        double head_final_angle = std::get<1>(phase_info_["head"][WalkPhase::kStarting]);
        double head_increment = CalculateIncrement(phase_info_["head"][WalkPhase::kStarting]);

        if (!IsDoubleEq(head->get_angle(), head_final_angle, 0.01))
        {
            head->Rotate(head->get_center_position(), head_increment);
            torso->Rotate(head->get_center_position(), head_increment);
            back_thig->Rotate(head->get_center_position(), head_increment);
            back_calf->Rotate(head->get_center_position(), head_increment);
            front_thig->Rotate(head->get_center_position(), head_increment);
            front_calf->Rotate(head->get_center_position(), head_increment);

            double back_thig_increment = CalculateIncrement(phase_info_["back_thig"][WalkPhase::kStarting]) - head_increment;
            back_thig->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);

            double back_calf_increment = CalculateIncrement(phase_info_["back_calf"][WalkPhase::kStarting]) - back_thig_increment - head_increment;
            back_calf->Rotate(back_calf->ThigAnchorPoint(), back_calf_increment);

            double front_thig_increment = CalculateIncrement(phase_info_["front_thig"][WalkPhase::kStarting]) - head_increment;
            front_thig->Rotate(front_thig->TorsoAnchorPoint(), front_thig_increment);
            front_calf->Rotate(front_thig->TorsoAnchorPoint(), front_thig_increment);

            double front_calf_increment = CalculateIncrement(phase_info_["front_calf"][WalkPhase::kStarting]) - front_thig_increment - head_increment;
            front_calf->Rotate(front_calf->ThigAnchorPoint(), front_calf_increment);
        }
        else
        {
            phase_ = WalkPhase::kAir;
        }
    }
    else if (phase_ == WalkPhase::kAir)
    {
        double back_thig_final_angle = std::get<1>(phase_info_["back_thig"][WalkPhase::kAir]);
        double back_thig_increment = CalculateIncrement(phase_info_["back_thig"][WalkPhase::kAir]);

        if (!IsDoubleEq(back_thig->get_angle(), back_thig_final_angle, 0.01))
        {
            back_thig->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);
            back_calf->Rotate(back_thig->TorsoAnchorPoint(), back_thig_increment);

            double back_calf_increment = CalculateIncrement(phase_info_["back_calf"][WalkPhase::kAir]) - back_thig_increment;
            back_calf->Rotate(back_calf->ThigAnchorPoint(), back_calf_increment);

            double front_thig_increment = CalculateIncrement(phase_info_["front_thig"][WalkPhase::kAir]);
            front_thig->Rotate(front_thig->TorsoAnchorPoint(), front_thig_increment);
            front_calf->Rotate(front_thig->TorsoAnchorPoint(), front_thig_increment);

            double front_calf_increment = CalculateIncrement(phase_info_["front_calf"][WalkPhase::kAir]) - front_thig_increment;
            front_calf->Rotate(front_calf->ThigAnchorPoint(), front_calf_increment);
        }
        else
        {
            phase_ = WalkPhase::kContact;
        }
    }
}

bool WalkingAnimationSystem::IsDoubleEq(double a, double b, double epsilon)
{
    return ((a - b) < epsilon) && ((b - a) < epsilon);
}

double WalkingAnimationSystem::CalculateIncrement(tuple<double, double> angles)
{
    double initial_angle = std::get<0>(angles);
    double final_angle = std::get<1>(angles);
    double time_factor = 2;
    return (final_angle - initial_angle) / time_factor;
}