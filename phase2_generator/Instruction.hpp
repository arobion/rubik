#pragma once
#include <iostream>

enum Instruction
{
	U = 1,
	D = 4,
	UR = 7,
	DR = 10,
	U2 = 13,
	R2 = 14,
	L2 = 15,
	D2 = 16,
	F2 = 17,
	B2 = 18,
	EMPTY
};

std::ostream & operator<<(std::ostream & o, Instruction const & rhs);