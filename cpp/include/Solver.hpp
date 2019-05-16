#pragma once

#include "type.hpp"
#include <bitset>
#include <string>
#include <unordered_map>

#define MAP_DEPTH 8

class Solver
{
public:
	Solver();
	void				solve(StatePtr state);

private:
	P1OrientationTable	p1_orientation_table;
	P1SliceTable		p1_slice_table;
	P2Table				p2_table;

	void				prepare_p1_table();
	void				prepare_p2_table();

	void				generate_p1_orientation_table();
	void				generate_p1_slice_table();
	void				generate_p2_table();
};
