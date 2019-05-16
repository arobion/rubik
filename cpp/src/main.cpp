#include "State.hpp"
#include "move.hpp"
#include "Phase1.hpp"
#include "Phase2.hpp"
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <list>
#include <memory>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>

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

/*
void solve(std::shared_ptr<State> s1)
{
	std::stringstream result;
	std::cout << "**************************\nPhase 1\n**************************\n";
	Phase1 phase1(s1);
	
	phase1.run();
	for (auto state : phase1.path)
	{
	//	std::cout << *state;
		if (state->instruction != EMPTY)
			result << state->instruction << " ";
	}
	std::cout << s1->tot << std::endl;

	
	std::cout << "**************************\nPhase 2\n**************************\n";
	auto s2 = phase1.path.back();
	s2->g = 0;
	s2->instruction = EMPTY;

	Phase2 phase2(s2);
	phase2.run();
	phase2.run_from_pruning();
	
	for (auto state : phase2.path)
	{
	//	std::cout << *state;
		if (state->instruction != EMPTY)
			result << state->instruction << " ";
	}
		
	std::cout << "nb moves: " << phase1.path.size() + phase2.path.size() - 2 << std::endl;
	std::cout << "solution: ";
	std::cout << result.str();
	std::cout << std::endl;
	

}*/
void solve(std::shared_ptr<State> s1, Phase1 phase1, Phase2 phase2)
{
	std::stringstream result;

	phase1.set_start(s1);
	phase1.run();
	for (auto state : phase1.path)
		if (state->instruction != EMPTY)
			result << state->instruction << " ";
	auto s2 = phase1.path.back();
	s2->g = 0;
	s2->instruction = EMPTY;
	phase2.set_start(s2);
	phase2.run();
	phase2.run_from_pruning();
	for (auto state : phase2.path)
		if (state->instruction != EMPTY)
			result << state->instruction << " ";
	std::cout << result.str() << std::endl;
}

int main()
{
	std::string input;
	Phase1 phase1{};
	Phase2 phase2{};
	std::cout << "Ready" << std::endl;
	
	while(true)
	{
		std::getline(std::cin, input);
		auto s1 = std::make_shared<State>(input);
		solve(s1, phase1, phase2);
	}
}

