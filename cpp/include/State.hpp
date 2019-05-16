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
	State(std::string);
	State(State const & state);
	State(State const & origin, Instruction instruction);
	State & operator=(State const &);
	
	std::vector<std::shared_ptr<State>>	get_nexts_1();
	std::vector<std::shared_ptr<State>>	get_nexts_2();
    std::bitset<16>         get_UD_slice_permutation();
	std::bitset<100>		get_bitset();
	std::bitset<32>			get_full_orientation();
	float					heuristic_dummy();

	char				g;
	static int			tot;
	Instruction			instruction;
	std::bitset<72>		compressed;
    std::bitset<16>     corners_orientation;
    std::bitset<12>     edges_orientation;

};

std::ostream & operator<<(std::ostream & o, State const & rhs);
