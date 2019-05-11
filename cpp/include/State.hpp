#pragma once
#include "Instruction.hpp"
#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <memory>

struct State
{

	State();
	State(State const & state);
	State(State const & origin, Instruction instruction);
	State & operator=(State const &);
	
	std::vector<std::shared_ptr<State>>	get_nexts_1();
	std::vector<std::shared_ptr<State>>	get_nexts_2();
    std::bitset<16>         get_corners_orientation();
    std::bitset<12>         get_edges_orientation();
    std::bitset<16>         get_UD_slice_permutation();

	char				g;
	Instruction			instruction;
	std::bitset<72>		compressed;
    std::bitset<28>     orientation;

};

std::ostream & operator<<(std::ostream & o, State const & rhs);
