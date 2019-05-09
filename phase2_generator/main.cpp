#include "State.hpp"
#include "move.hpp"
#include <iostream>

int main(void)
{
	State s1{};
	std::cout << s1 << std::endl;

	auto s2 = move(s1, U);
	std::cout << s2 << std::endl;

	auto s3 = move(s1, UR);
	std::cout << s3 << std::endl;

	s2 = move(s1, U2);
	std::cout << s2 << std::endl;

	s2 = move(s1, D);
	std::cout << s2 << std::endl;

	s2 = move(s1, DR);
	std::cout << s2 << std::endl;

	s2 = move(s1, D2);
	std::cout << s2 << std::endl;

	s2 = move(s1, R2);
	std::cout << s2 << std::endl;

	s2 = move(s1, L2);
	std::cout << s2 << std::endl;

	s2 = move(s1, F2);
	std::cout << s2 << std::endl;

	s2 = move(s1, B2);
	std::cout << s2 << std::endl;
}
