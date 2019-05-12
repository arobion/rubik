#include "State.hpp"
#include "move.hpp"
#include "Phase2.hpp"
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <list>
#include <memory>
#include <stdlib.h>

typedef std::unordered_map<std::bitset<72>, char> map_t;

map_t bfs(std::shared_ptr<State> start)
{
    map_t map;
	map[start->compressed] = start->g;

	std::list<std::shared_ptr<State>> queue;
	queue.push_back(start);

	while (queue.size())
	{
		auto current = queue.front();
		queue.pop_front();
		if (current->g < 7)
		{
			for (auto next : current->get_nexts_2())
			{
				if (map.find(next->compressed) == map.end())
				{
					map[next->compressed] = next->g;
					queue.push_back(next);
				}
			}
		}
	}
	return map;
}

int main(/*int argc, char **argv*/)
{
	/* python wrap
	if (argc == 41)
	{
		auto s1 = std::make_shared<State>(argv);
		std::cout << *s1 << std::endl;
	}
	else
	{
		auto s1 = std::make_shared<State>();
		std::cout << *s1 << std::endl;
	}
	*/

	/* bfs
	auto map = bfs(s1);
	std::cout << map.size() << std::endl;
	std::cout << *s1 << std::endl;
	*/

	auto s1 = std::make_shared<State>();
	auto s2 = move(*s1, U);
	auto s3 = move(*s2, R2);
	s3->g = 0;
	s3->instruction = EMPTY;
	Phase2 phase2(s3);
	phase2.run();
	for (auto state : phase2.path)
		std::cout << *state;
}

