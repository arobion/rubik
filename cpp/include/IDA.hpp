#pragma once

#include "State.hpp"
#include <list>
#include <limits>
#include <unordered_set>

#define BOUND_INF std::numeric_limits<char>::max()

class IDA
{
public:
	IDA(std::shared_ptr<State> start);
	std::list<std::shared_ptr<State>> path;
	void run();

private:
	std::shared_ptr<State> start;
	float bound;
	std::unordered_set<std::bitset<100>> visited;

	char search();
};