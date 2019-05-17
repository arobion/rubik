#include "Phase1.hpp"
#include "Phase2.hpp"
#include "move.hpp"
#include <iostream>
#include <algorithm>

Phase1::Phase1(P1OrientationTable & p1_orientation_table, P1SliceTable & p1_slice_table, P2Table & p2_table, StatePtr start) :
	p1_orientation_table(p1_orientation_table),
	p1_slice_table(p1_slice_table),
	p2_table(p2_table),
	start(start),
	bound(heuristic(start))
{
	path.push_back(start);
}

std::vector<StatePtr> Phase1::get_nexts(StatePtr current)
{
	std::vector<StatePtr> nexts;
	for (auto next_instruction : moves_map_1[current->instruction])
		nexts.push_back(move(*current, next_instruction));
	return nexts;
}

float Phase1::heuristic(StatePtr state)
{
	return std::max(p1_orientation_table[state->get_full_orientation()], p1_slice_table[state->get_UD_slice_permutation()]);
}

void Phase1::run()
{
	while (1)
	{
		auto tmp = search(BOUND_INF);
		if (tmp == 0)
			break;
		else if (tmp == BOUND_INF)
		{
			std::cerr << "Can't found the solution.";
			break;
		}
		bound = tmp;
	}
}

float Phase1::search(float prev_min)
{
	auto current = path.back();
	float h = heuristic(current);
	float f = float(current->g) + h;
	if (f > bound)
		return f;
	if (h == 0)
		return (run_phase2()) ? 0 : prev_min;
	float min = BOUND_INF;

	for (auto next : get_nexts(current))
	{
		auto bitset = next->get_bitset();
		if (visited.find(bitset) == visited.end())
		{
			path.push_back(next);
			visited.insert(bitset);
			auto tmp = search(min);
			if (tmp == 0)
				return 0;
			if (tmp < min)
			{
				min = tmp;
				current = next;
			}
			path.pop_back();
			visited.erase(bitset);
			current = path.back();
		}
	}
	return min;
}

bool Phase1::run_phase2()
{
	// prepare strarting state for phase 2
	auto s2 = std::make_shared<State>(*(path.back()));
	s2->g = 0;
	s2->instruction = EMPTY;

	// phase 2
	Phase2 phase2(p2_table, s2, MAX_DEPTH - path.back()->g);
	if (phase2.run())
	{
		phase2.path.pop_front();
		for (auto elem : phase2.path)
			path.push_back(elem);
		return true;
	}
	return false;
}
