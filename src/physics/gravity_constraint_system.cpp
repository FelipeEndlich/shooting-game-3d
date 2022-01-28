#include "gravity_constraint_system.hpp"

#include <algorithm>

#include "icollidable.hpp"

using ::physic::GravityConstraintSystem;
using ::physic::ICollidable;

void GravityConstraintSystem::AddSurface(ICollidable *surface)
{
    surfaces_.push_back(surface);
}

void GravityConstraintSystem::RemoveSurface(ICollidable *surface)
{
    surfaces_.erase(std::remove(surfaces_.begin(), surfaces_.end(), surface), surfaces_.end());
}

void GravityConstraintSystem::AddCorp(IGravityAffectable *corp)
{
    corps_.push_back(corp);
}

void GravityConstraintSystem::RemoveCorp(IGravityAffectable *corp)
{
    corps_.erase(std::remove(corps_.begin(), corps_.end(), corp), corps_.end());
}

void GravityConstraintSystem::ProcessGravityEffects()
{
    bool floating = true;
    for (auto &corp : corps_)
    {
        for (auto &surface : surfaces_)
        {
            if (corp->get_position()[1] + corp->get_height() == surface->get_position()[1] && corp->get_position()[0] + corp->get_width() > surface->get_position()[0] && corp->get_position()[0] < surface->get_position()[0] + surface->get_width())
            {
                floating = false;
                break;
            }
        }

        if (floating)
            corp->ProcessGravity();
    }
}