#pragma once
#include "Instruction.hpp"
#include <iostream>
#include <vector>

struct State
{
	State();
	State(State const & state);
	State(State const & origin, Instruction instruction);

	std::vector<char>	corners;
	std::vector<char>	edges;
	char				g;
	Instruction			instruction;
};

std::ostream & operator<<(std::ostream & o, State const & rhs);