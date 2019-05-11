#include "State.hpp"
#include "move.hpp"
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <list>
#include <memory>

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
		if (current->g < 9)
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

int main(void)
{
	auto s1 = std::make_shared<State>();
	auto map = bfs(s1);
	std::cout << map.size() << std::endl;
//    std::cout << *s1 << std::endl;
}

