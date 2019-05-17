#include "State.hpp"
#include "Solver.hpp"
#include <iostream>
#include <memory>
#include <string>

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

