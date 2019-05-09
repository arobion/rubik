#include "State.hpp"

State::State() :
	g(0),
	instruction(EMPTY)
{
	corners.reserve(8);
	for (auto i = 0; i < 8; ++i)
		corners.push_back(i);
	edges.reserve(12);
	for (auto i = 0; i < 12; ++i)
		edges.push_back(i);
}

State::State(State const & origin) :
	corners(origin.corners),
	edges(origin.edges),
	g(origin.g),
	instruction(origin.instruction)
{}

State::State(State const & origin, Instruction instruction) :
	corners(origin.corners),
	edges(origin.edges),
	g(origin.g),
	instruction(instruction)
{}

std::ostream & operator<<(std::ostream & o, State const & rhs)
{
	o << "instruction : " << rhs.instruction << std::endl;
	o << "corners: ";
	for (auto i = 0; i < 8; ++i)
		o << int(rhs.corners[i]) << " ";
	o << std::endl;

	o << "edges:   ";
	for (auto i = 0; i < 12; ++i)
		o << int(rhs.edges[i]) << " ";
	o << std::endl;
	return o;
}