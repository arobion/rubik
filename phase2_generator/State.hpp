#pragma once
#include "Instruction.hpp"
#include <iostream>
#include <vector>

struct State
{
	State();
	State(State const & state);
	State(State const & origin, Instruction instruction);
	State & operator=(State const &);
	
	std::bitset<72>		compress(void) const;

	std::vector<char>	corners;
	std::vector<char>	edges;
	char				g;
	Instruction			instruction;
	std::bitset<72>		compressed;
};

std::ostream & operator<<(std::ostream & o, State const & rhs);
