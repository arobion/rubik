#pragma once
#include "Instruction.hpp"
#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>

struct State
{
	inline static std::unordered_map<Instruction, std::vector<Instruction>> moves_map{
		{U, {D, DR, D2, L2, R2, F2, B2}},
		{UR, {D, DR, D2, L2, R2, F2, B2}},
		{U2, {D, DR, D2, L2, R2, F2, B2}},
		{D, {U, UR, U2, L2, R2, F2, B2}},
		{DR, {U, UR, U2, L2, R2, F2, B2}},
		{D2, {U, UR, U2, L2, R2, F2, B2}},
		{L2, {U, UR, U2, D, DR, D2, R2, F2, B2}},
		{R2, {U, UR, U2, D, DR, D2, L2, F2, B2}},
		{F2, {U, UR, U2, D, DR, D2, L2, R2, B2}},
		{B2, {U, UR, U2, D, DR, D2, L2, R2, F2}},
		{EMPTY, {U, UR, U2, D, DR, D2, L2, R2, F2, B2}}
	};

	State();
	State(State const & state);
	State(State const & origin, Instruction instruction);
	State & operator=(State const &);
	
	std::vector<State *>	get_nexts();
    std::bitset<16>         get_corners_orientation();
    std::bitset<12>         get_edges_orientation();
    std::bitset<16>         get_UD_slice_permutation();

	char				g;
	Instruction			instruction;
	std::bitset<72>		compressed;
    std::bitset<28>     orientation;

};

std::ostream & operator<<(std::ostream & o, State const & rhs);
