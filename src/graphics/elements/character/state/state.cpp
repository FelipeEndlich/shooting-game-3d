#include "state.hpp"

using namespace graphics::elements::character;
using namespace std;

string State::getName() const
{
    return this->name;
}

std::string State::toString() const
{
    return "State: " + this->name;
}