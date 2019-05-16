#include "Phase2.hpp"
#include "move.hpp"

Phase2::Phase2(P2Table & p2_table, StatePtr start) :
	p2_table(p2_table),
	start(start),
	bound(heuristic(start))
{
	path.push_back(start);
}

std::vector<StatePtr> Phase2::get_nexts(StatePtr current)
{
	std::vector<StatePtr> nexts;
	for (auto next_instruction : moves_map_2[current->instruction])
		nexts.push_back(move(*current, next_instruction));
	return nexts;
}

float Phase2::heuristic(StatePtr state)
{
	if (p2_table.find(state->compressed) == p2_table.end())
		return heuristic_moves(state);
	return 0;
}

float Phase2::heuristic_moves(StatePtr state)
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

	auto dep = path.back();
	auto cost = p2_table[dep->compressed];
	search_with_table(cost, dep);
}

float Phase2::search()
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

void Phase2::search_with_table(char cost, StatePtr current)
{
	if (cost == 0)
		return ;
	char tmp_cost = cost;
	auto tmp_state = current;
	for (auto next : get_nexts(current))
	{
		if (p2_table.find(next->compressed) != p2_table.end())
		{
			if (p2_table[next->compressed] < tmp_cost)
			{
				tmp_cost = p2_table[next->compressed];
				tmp_state = next;
			}
		}
	}
	path.push_back(tmp_state);
	search_with_table(tmp_cost, tmp_state);
}
