#include "State.hpp"
#include "move.hpp"
#include "Solver.hpp"
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

int main()
{
	Solver solver;
	
	while(true)
	{
		std::string input;
		std::getline(std::cin, input);
		auto s1 = std::make_shared<State>(input);
		solver.solve(s1);
	}
}

