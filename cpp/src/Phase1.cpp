#include "Phase1.hpp"
#include "move.hpp"
#include <iostream>
#include <algorithm>

Phase1::Phase1(P1OrientationTable & p1_orientation_table, P1SliceTable & p1_slice_table, StatePtr start) :
	p1_orientation_table(p1_orientation_table),
	p1_slice_table(p1_slice_table),
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
		auto tmp = search();
		if (tmp == 0)
			break;
		else if (tmp == BOUND_INF)
		{
			std::cerr << "Can't found the solution.";
			break;
		}
		bound = tmp;
		// std::cout << "update bound: " << bound << std::endl;
	}
}

float Phase1::search()
{
	auto current = path.back();
	float h = heuristic(current);
	float f = float(current->g) + h;
	if (f > bound)
		return f;
	if (h == 0)
		return 0;
	float min = BOUND_INF;

	for (auto next : get_nexts(current))
	{
		auto bitset = next->get_bitset();
		if (visited.find(bitset) == visited.end())
		{
			path.push_back(next);
			visited.insert(bitset);
			auto tmp = search();
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
