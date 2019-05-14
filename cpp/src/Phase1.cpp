#include "Phase1.hpp"
#include "move.hpp"
#include <iostream>
#include <algorithm>

Phase1::Phase1(std::shared_ptr<State> start) :
	start(start)
{
	generate_co_map();
	generate_eo_map();
	generate_slice_map();

	std::cout << "Generate phase 1 maps\n";
	std::cout << "corners: " << co_map.size() << std::endl;
	std::cout << "edges: " << eo_map.size() << std::endl;
	std::cout << "slices: " << slice_map.size() << std::endl;
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

/*
void Phase1::generate_eo_map()
{
	auto current = solved;
	std::list<std::shared_ptr<State>> queue;

	eo_map[current->get_full_orientation()] = current->g;
	queue.push_back(current);

	while (queue.size())
	{
		current = queue.front();
		queue.pop_front();
		auto nexts = get_nexts(current);
		for (auto next : nexts)
		{
			if (eo_map.find(next->get_full_orientation()) == eo_map.end())
			{
				eo_map[next->get_full_orientation()] = next->g;
				queue.push_back(next);
			}
		}
	}
}
*/
std::bitset<8>	Phase1::get_edges_around_slice(std::shared_ptr<State> curr, char pos1, char pos2)
{
	std::bitset<8> ret;

	ret[7] = curr->compressed[((11 - pos1) * 4) + 3];
	ret[6] = curr->compressed[((11 - pos1) * 4) + 2];
	ret[5] = curr->compressed[((11 - pos1) * 4) + 1];
	ret[4] = curr->compressed[((11 - pos1) * 4)];

	
	ret[3] = curr->compressed[((11 - pos2) * 4) + 3];
	ret[2] = curr->compressed[((11 - pos2) * 4) + 2];
	ret[1] = curr->compressed[((11 - pos2) * 4) + 1];
	ret[0] = curr->compressed[((11 - pos2) * 4)];

	return ret;
}

void	Phase1::add_new_entry_permuted(int to_perm[4], std::list<std::shared_ptr<State>> queue)
{
	auto s1 = std::make_shared<State>();
	s1->compressed[31] = to_perm[0] >> 3;
	s1->compressed[30] = (to_perm[0] & 4) >> 2;
	s1->compressed[29] = (to_perm[0] & 2) >> 1;
	s1->compressed[28] = (to_perm[0] & 1);

	s1->compressed[27] = to_perm[1] >> 3;
	s1->compressed[26] = (to_perm[1] & 4) >> 2;
	s1->compressed[25] = (to_perm[1] & 2) >> 1;
	s1->compressed[24] = (to_perm[1] & 1);

	s1->compressed[23] = to_perm[2] >> 3;
	s1->compressed[22] = (to_perm[2] & 4) >> 2;
	s1->compressed[21] = (to_perm[2] & 2) >> 1;
	s1->compressed[20] = (to_perm[2] & 1);

	s1->compressed[19] = to_perm[3] >> 3;
	s1->compressed[18] = (to_perm[3] & 4) >> 2;
	s1->compressed[17] = (to_perm[3] & 2) >> 1;
	s1->compressed[16] = (to_perm[3] & 1);
	slice_map[s1->get_UD_slice_permutation()] = s1->g;
	queue.push_back(s1);
}

void Phase1::generate_slice_map()
{
	auto current = solved;
	std::list<std::shared_ptr<State>> queue;

	slice_map[current->get_UD_slice_permutation()] = current->g;
	queue.push_back(current);
	
	/*
	int to_perm[] = {4, 5, 6, 7};
	while (std::next_permutation(to_perm, to_perm + 4))
		add_new_entry_permuted(to_perm, queue);

	std::unordered_set<std::bitset<8>> set1;
	std::unordered_set<std::bitset<8>> set2;
	std::unordered_set<std::bitset<8>> set3;
	std::unordered_set<std::bitset<8>> set4;
	*/
	
	while (queue.size())
	{
		current = queue.front();
		queue.pop_front();
		auto nexts = get_nexts(current);
		for (auto next : nexts)
		{
			if (slice_map.find(next->get_UD_slice_permutation()) == slice_map.end())
			{
				slice_map[next->get_UD_slice_permutation()] = next->g;
				queue.push_back(next);
/*
				set1.insert(get_edges_around_slice(next, 2, 10));
				set2.insert(get_edges_around_slice(next, 10, 2));
				set3.insert(get_edges_around_slice(next, 2, 11));
				set4.insert(get_edges_around_slice(next, 11, 2));
				*/
			}
			/*
			else if (set1.find(get_edges_around_slice(next, 2, 10)) == set1.end())
			{
				queue.push_back(next);
				set1.insert(get_edges_around_slice(next, 2, 10));
			}
			else if (set2.find(get_edges_around_slice(next, 10, 2)) == set2.end())
			{
				queue.push_back(next);
				set2.insert(get_edges_around_slice(next, 10, 2));
			}
			else if (set3.find(get_edges_around_slice(next, 2, 11)) == set3.end())
			{
				queue.push_back(next);
				set3.insert(get_edges_around_slice(next, 2, 11));
			}
			else if (set4.find(get_edges_around_slice(next, 11, 2)) == set4.end())
			{
				queue.push_back(next);
				set4.insert(get_edges_around_slice(next, 11, 2));
			}
			*/
		}
	}
	/*
	std::unordered_map<int, char> resume_map;
	for (auto elem : slice_map)
	{
		if (resume_map.find(slice_map.find(elem)) == resume_map.end())
			resume_map[slice_map[elem]] = 0;
		else
			resume_map[slice_map[elem]] += 1;
	}
	for (auto elem : resume_map)
		std::cout << elem << resume_map[elem] << std::endl;
		*/
}

float Phase1::heuristic(std::shared_ptr<State> state)
{
	return std::max(std::max(co_map[state->corners_orientation], eo_map[state->edges_orientation]), slice_map[state->get_UD_slice_permutation()]);
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
		std::cout << "update bound: " << bound << std::endl;
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
