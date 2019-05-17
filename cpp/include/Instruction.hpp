#pragma once

#include <iostream>

enum Instruction
{
	U, UR, U2,
	D, DR, D2,
	R, RR, R2,
	L, LR, L2,
	F, FR, F2,
	B, BR, B2,
	EMPTY
};

std::ostream & operator<<(std::ostream & o, Instruction const & rhs);