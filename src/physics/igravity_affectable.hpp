#pragma once

#include "icollidable.hpp"

namespace physic
{
    class IGravityAffectable : public ICollidable
    {
    public:
        IGravityAffectable() = default;
        virtual ~IGravityAffectable() = default;

        virtual void ProcessGravity() = 0;
    };
}