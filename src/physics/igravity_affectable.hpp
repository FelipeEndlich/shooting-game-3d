#pragma once

#include "icollidable.hpp"

namespace physic
{
    class IGravityAffectable : public ICollidable
    {
    public:
        virtual void ProcessGravity() = 0;
    };
}