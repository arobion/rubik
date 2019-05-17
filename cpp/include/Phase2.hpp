#pragma once

#include "State.hpp"
#include "TableLoader.hpp"
#include "type.hpp"
#include <list>
#include <unordered_set>

class Phase2
{
public:
	Phase2(P2Table & p2_table, StatePtr start, float max_depth);

	std::list<StatePtr>					path;
	static std::vector<StatePtr>		get_nexts(StatePtr current);
	bool								run();
	void								run_from_pruning();

private:
	P2Table &							p2_table;
	StatePtr							start;
	float								max_depth;
	float								bound;
	std::unordered_set<std::bitset<72>>	visited;

	float								heuristic(StatePtr state);
	float 								heuristic_moves(StatePtr state);
	float 								search();
	void 								search_with_table(char cost, StatePtr current);


	static inline std::unordered_map<Instruction, std::vector<Instruction>> moves_map_2{
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
};
