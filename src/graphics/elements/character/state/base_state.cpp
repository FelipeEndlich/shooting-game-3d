#include "base_state.hpp"

using ::graphics::elements::character::BaseState;
using ::std::string;

string BaseState::get_name() const
{
    return name_;
}

std::string BaseState::to_string() const
{
    return "State: " + name_;
}