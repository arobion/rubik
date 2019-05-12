#include "Phase2.hpp"
#include "move.hpp"
#include <iostream>

Phase2::Phase2(std::shared_ptr<State> start) :
	start(start),
	bound(heuristic(start))
{
	path.push_back(start);
}

void Phase2::run()
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
	}
}

char Phase2::search()
{
	auto current = path.back();
	float h = heuristic(current);
	float f = float(current->g) + h;
	if (f > bound)
		return f;
	if (h == 0)
		return 0;
	char min = BOUND_INF;

	for (auto next : get_nexts(current))
	{
		if (visited.find(next->compressed) == visited.end())
		{
			path.push_back(next);
			visited.insert(next->compressed);
			auto tmp = search();
			if (tmp == 0)
				return 0;
			if (tmp < min)
			{
				min = tmp;
				current = next;
			}
			path.pop_back();
			visited.erase(next->compressed);
			current = path.back();
		}
	}
	return min;
}

float Phase2::heuristic(std::shared_ptr<State> state)
{
	// compare edges
	float sum_edges = 0;
	for (auto i = 0; i < 12; ++i)
	{
		std::bitset<4> num(i);
		for (auto j = 0; j < 4; ++j)
		{
			if (num[j] != state->compressed[(11-i)*4 + j])
			{
				++sum_edges;
				break;
			}
		}
	}
	// compare corners
	float sum_corners = 0;
	for (auto i = 0; i < 8; ++i)
	{
		std::bitset<3> num(i);
		for (auto j = 0; j < 3; ++j)
		{
			if (num[j] != state->compressed[48+(7-i)*3 + j])
			{
				++sum_corners;
				break;
			}
		}
	}
	return std::max(sum_edges / 4, sum_corners / 4);
}

std::vector<std::shared_ptr<State>> Phase2::get_nexts(std::shared_ptr<State> current)
{
	std::vector<std::shared_ptr<State>> nexts;
	for (auto next_instruction : moves_map[current->instruction])
		nexts.push_back(move(*current, next_instruction));
	return nexts;
}
