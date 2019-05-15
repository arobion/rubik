#include "Phase2.hpp"
#include "move.hpp"
#include <iostream>
#include <fstream>


#define BUFF_SIZE 10000

void bitset_to_string(char* buffer, int buffer_index, std::bitset<72> set)
{
	for (auto i = 0; i < 9; i++)
	{
		buffer[buffer_index + i] = 0;
		for (auto j = 7; j >= 0; j--)
		{
			buffer[buffer_index + i] |= set[(8 - i) * 8 + j] << j;
		}
	}
}

std::bitset<72> get_key_from_bin(char* buffer, int start_index)
{
	std::bitset<72> ret;
	for (auto i = 0; i < 9; i++)
	{
		for (auto j = 7; j >= 0; j--)
			ret[(8 - i) * 8 + j] = (buffer[start_index + i] & (1 << j)) >> j;
	}

	//std::cout << ret << std::endl;
	return ret;

}

void string_to_bitset(char* buffer, std::unordered_map<std::bitset<72>, char> *test, int len)
{
	int i = 0;
	while (i < len)
	{
		(*test)[get_key_from_bin(buffer, i)] = buffer[i + 9];
		i += 10;
	}
}

Phase2::Phase2(std::shared_ptr<State> start) :
	start(start)
{
	generate_bfs_map();
	std::cout << "Generate phase 2 map" << std::endl;
	std::cout << "bfs_map: " << bfs_map.size() << std::endl;
	std::cout << std::endl;
	
	//write in file
	std::ofstream phase2FileW ("phase2File.bin", std::ofstream::binary);
	char buffer[10000];
	int i = 0;
	for (auto data : bfs_map)
	{
		bitset_to_string(buffer, i, data.first);
		buffer[i + 9] = data.second;
		i += 10;
		if (i == BUFF_SIZE)
		{
			i = 0;
			phase2FileW.write(buffer, BUFF_SIZE);
		}
	}
	phase2FileW.write(buffer, i);
	phase2FileW.close();


	//read in file
	std::unordered_map<std::bitset<72>, char> test;
	std::ifstream phase2FileR ("phase2File.bin", std::ofstream::binary);

	while (phase2FileR.read(buffer, BUFF_SIZE))
		string_to_bitset(buffer, &test, phase2FileR.gcount());
	string_to_bitset(buffer, &test, phase2FileR.gcount());
	phase2FileR.close();
	this->bound = map_heuristic(start);
	path.push_back(start);
}

void Phase2::generate_bfs_map()
{
	auto dep = std::make_shared<State>();
	bfs_map[dep->compressed] = dep->g;

	std::list<std::shared_ptr<State>> queue;
	queue.push_back(dep);

	while (queue.size())
	{
		auto current = queue.front();
		queue.pop_front();
		if (current->g < 7)
		{
			for (auto next : current->get_nexts_2())
			{
				if (bfs_map.find(next->compressed) == bfs_map.end())
				{
					bfs_map[next->compressed] = next->g;
					queue.push_back(next);
				}
			}
		}
	}
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
		std::cout << "update bound: " << bound << std::endl;
	}
}

void Phase2::run_from_pruning()
{
	auto dep = path.back();
	auto cost = bfs_map[dep->compressed];
	search_from_pruning(cost, dep);

}

void Phase2::search_from_pruning(char cost, std::shared_ptr<State> current)
{
	if (cost == 0)
		return ;
	char tmp_cost = cost;
	auto tmp_state = current;
	for (auto next : get_nexts(current))
	{
		if (bfs_map.find(next->compressed) != bfs_map.end())
		{
			if (bfs_map[next->compressed] < tmp_cost)
			{
				tmp_cost = bfs_map[next->compressed];
				tmp_state = next;
			}
		}
	}
	path.push_back(tmp_state);
	search_from_pruning(tmp_cost, tmp_state);
}

float Phase2::search()
{
	auto current = path.back();
	float h = map_heuristic(current);
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

float Phase2::map_heuristic(std::shared_ptr<State> state)
{
	if (bfs_map.find(state->compressed) == bfs_map.end())
		return heuristic(state);
	return 0;
	return bfs_map[state->compressed];
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
