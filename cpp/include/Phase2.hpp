#pragma once

#include "State.hpp"
#include <list>
#include <limits>
#include <unordered_set>

#define BOUND_INF std::numeric_limits<float>::max()

class Phase2
{
public:
	Phase2(std::shared_ptr<State> start);

	std::list<std::shared_ptr<State>> path;

	void run();
	void run_from_pruning();

private:
	std::shared_ptr<State> start;
	float bound;
	std::unordered_set<std::bitset<72>> visited;

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

	std::unordered_map<std::bitset<72>, char> bfs_map;
	void	generate_bfs_map();
	float 	search();
	void	search_from_pruning(char, std::shared_ptr<State>);
	float 	heuristic(std::shared_ptr<State> state);
	float 	map_heuristic(std::shared_ptr<State> state);
	std::vector<std::shared_ptr<State>> get_nexts(std::shared_ptr<State>);
};
