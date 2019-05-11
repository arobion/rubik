#pragma once
#include "State.hpp"

std::shared_ptr<State> move(State & origin, Instruction instruction);