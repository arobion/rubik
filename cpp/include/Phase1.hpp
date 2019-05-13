#pragma once

#include "State.hpp"
#include <list>
#include <limits>
#include <unordered_set>

#define BOUND_INF std::numeric_limits<float>::max()

class Phase1
{
public:
	Phase1(std::shared_ptr<State> start);
	std::list<std::shared_ptr<State>> path;
	void run();

private:
	std::unordered_map<Instruction, std::vector<Instruction>> moves_map_1{
		{U, {D, DR, D2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{UR, {D, DR, D2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{U2, {D, DR, D2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},

		{D, {U, UR, U2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{DR, {U, UR, U2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{D2, {U, UR, U2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},

		{L, {U, UR, U2, D, DR, D2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{LR, {U, UR, U2, D, DR, D2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{L2, {U, UR, U2, D, DR, D2, R, RR, R2, F, FR, F2, B, BR, B2}},

		{R, {U, UR, U2, D, DR, D2, L, LR, L2, F, FR, F2, B, BR, B2}},
		{RR, {U, UR, U2, D, DR, D2, L, LR, L2, F, FR, F2, B, BR, B2}},
		{R2, {U, UR, U2, D, DR, D2, L, LR, L2, F, FR, F2, B, BR, B2}},

		{F, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, B, BR, B2}},
		{FR, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, B, BR, B2}},
		{F2, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, B, BR, B2}},

		{B, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, F, FR, F2}},
		{BR, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, F, FR, F2}},
		{B2, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, F, FR, F2}},

		{EMPTY, {U, UR, U2, D, DR, D2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}}
	};
	std::shared_ptr<State> solved = std::make_shared<State>();

	std::shared_ptr<State> start;
	std::unordered_map<std::bitset<16>, char> co_map;
	std::unordered_map<std::bitset<12>, char> eo_map;
	std::unordered_map<std::bitset<16>, char> slice_map;

	float bound;
	std::unordered_set<std::bitset<100>> visited;

	std::vector<std::shared_ptr<State>> get_nexts(std::shared_ptr<State>);
	void generate_co_map();
	void generate_eo_map();
	//void generate_slice_map();
	float heuristic(std::shared_ptr<State> state);
	float search();
};