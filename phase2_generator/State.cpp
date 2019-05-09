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
	this->compressed = this->compress();
}

State::State(State const & origin) :
	corners(origin.corners),
	edges(origin.edges),
	g(origin.g),
	instruction(origin.instruction),
	compressed(this->compress())
{}

State::State(State const & origin, Instruction instruction) :
	corners(origin.corners),
	edges(origin.edges),
	g(origin.g),
	instruction(instruction),
	compressed(this->compress())
{}

State & State::operator=(State const & rhs)
{
	if (this != &rhs)
	{
		this->corners = rhs.corners;
		this->edges = rhs.edges;
		this->g = rhs.g;
		this->instruction = rhs.instruction;
		this->compressed = rhs.compress();
	}
	return *this;
}

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
	o << "compressed:" << std::endl;
	o << rhs.compressed << std::endl;
	o << std::endl;
	return o;
}

std::bitset<72> State::compress() const
{
	std::bitset<72> ret;
	for(char i = 0;i < 8; i++)
	{
		ret <<= 3;
		ret |= this->corners[i];
	}
	for(char i = 0;i < 12; i++)
	{
		ret <<= 4;
		ret |= this->edges[i];
	}
	return ret;
}
