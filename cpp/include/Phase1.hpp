#pragma once

#include "State.hpp"
#include "TableLoader.hpp"
#include "type.hpp"
#include <list>
#include <unordered_set>

#define MAX_DEPTH 24

class Phase1
{
public:
	Phase1(P1OrientationTable & p1_orientation_table, P1SliceTable & p1_slice_table, P2Table & p2_table, StatePtr start);

	std::list<StatePtr>						path;

	void									run();
	static std::vector<StatePtr>			get_nexts(StatePtr current);

private:
	P1OrientationTable &					p1_orientation_table;
	P1SliceTable &							p1_slice_table;
	P2Table &								p2_table;
	StatePtr								start;
	float									bound;
	std::unordered_set<std::bitset<100>>	visited;

	float									heuristic(StatePtr state);
	float									search(float prev_min);
	bool									run_phase2();

	static inline std::unordered_map<Instruction, std::vector<Instruction>> moves_map_1{
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
};
