#include "IDA.hpp"
#include <iostream>

IDA::IDA(std::shared_ptr<State> start) :
	start(start),
	bound(start->heuristic_dummy())
{
	path.push_back(start);
}

void IDA::run()
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

char IDA::search()
{
	auto current = path.back();
	float h = current->heuristic_dummy();
	float f = float(current->g) + h;
	if (f > bound)
		return f;
	if (h == 0)
		return 0;
	char min = BOUND_INF;

	for (auto next : current->get_nexts_2())
	{
		if (visited.find(next->get_bitset()) == visited.end())
		{
			path.push_back(next);
			auto tmp = search();
			if (tmp == 0)
				return 0;
			if (tmp < min)
			{
				min = tmp;
				current = next;
			}
			path.pop_back();
			current = path.back();
		}
	}
	return min;
}
