#include "Phase1.hpp"
#include "move.hpp"
#include <iostream>

Phase1::Phase1(std::shared_ptr<State> start) :
	start(start)
{
	generate_co_map();
	generate_eo_map();
	//generate_slice_map();

	std::cout << "Generate phase 1 maps\n";
	std::cout << "corners: " << co_map.size() << std::endl;
	std::cout << "edges: " << eo_map.size() << std::endl;
	//std::cout << "slices: " << slice_map.size() << std::endl;
	std::cout << std::endl;

	bound = heuristic(start);
	path.push_back(start);
}

std::vector<std::shared_ptr<State>> Phase1::get_nexts(std::shared_ptr<State> current)
{
	std::vector<std::shared_ptr<State>> nexts;
	for (auto next_instruction : moves_map_1[current->instruction])
		nexts.push_back(move(*current, next_instruction));
	return nexts;
}

void Phase1::generate_co_map()
{
	auto current = solved;
	std::list<std::shared_ptr<State>> queue;

	co_map[current->corners_orientation] = current->g;
	queue.push_back(current);

	while (queue.size())
	{
		current = queue.front();
		queue.pop_front();
		auto nexts = get_nexts(current);
		for (auto next : nexts)
		{
			if (co_map.find(next->corners_orientation) == co_map.end())
			{
				co_map[next->corners_orientation] = next->g;
				queue.push_back(next);
			}
		}
	}
}

void Phase1::generate_eo_map()
{
	auto current = solved;
	std::list<std::shared_ptr<State>> queue;

	eo_map[current->edges_orientation] = current->g;
	queue.push_back(current);

	while (queue.size())
	{
		current = queue.front();
		queue.pop_front();
		auto nexts = get_nexts(current);
		for (auto next : nexts)
		{
			if (eo_map.find(next->edges_orientation) == eo_map.end())
			{
				eo_map[next->edges_orientation] = next->g;
				queue.push_back(next);
			}
		}
	}
}

float Phase1::heuristic(std::shared_ptr<State> state)
{
	return std::max(co_map[state->corners_orientation], eo_map[state->edges_orientation]);
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
	}
}

char Phase1::search()
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