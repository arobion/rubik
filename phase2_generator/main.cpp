#include "State.hpp"
#include "move.hpp"
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <list>

typedef std::unordered_map<std::bitset<72>, char> map_t;

map_t bfs(State & start)
{
    map_t map;
	map[start.compressed] = start.g;

	std::list<State> queue;
	queue.push_back(start);

	while (queue.size())
	{
		auto current = queue.front();
		queue.pop_front();
		if (current.g >= 7)
			continue;
		for (auto next : current.get_nexts())
		{
			if (map.find(next->compressed) != map.end())
				continue;
			map[next->compressed] = next->g;
			queue.push_back(*next);
		}
	}
	return map;
}

int main(void)
{
	State s1{};
	auto map = bfs(s1);
	std::cout << map.size() << std::endl;
}
