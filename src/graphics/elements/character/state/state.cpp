#include "state.hpp"

using ::graphics::elements::state::BaseState;
using ::std::string;

string BaseState::get_name() const
{
    return name_;
}

std::string BaseState::to_string() const
{
    return "State: " + name_;
}