#include "State.hpp"
#include "move.hpp"

State::State() :
	g(0),
	instruction(EMPTY)
{
	for (char i = 0; i < 8; ++i)
	{
		this->compressed <<= 3;
		this->compressed |= i;
	}
	for (char i = 0; i < 12; ++i)
	{
		this->compressed <<= 4;
		this->compressed |= i;
	}
}

State::State(State const & origin) :
	g(origin.g),
	instruction(origin.instruction),
	compressed(origin.compressed),
    orientation(origin.orientation)
{
}

State::State(State const & origin, Instruction instruction) :
	g(origin.g + 1),
	instruction(instruction),
	compressed(origin.compressed),
    orientation(origin.orientation)
{
}

State & State::operator=(State const & rhs)
{
	if (this != &rhs)
	{
		this->g = rhs.g;
		this->instruction = rhs.instruction;
		this->compressed = rhs.compressed;
        this->orientation = rhs.orientation;
	}
	return *this;
}

std::ostream & operator<<(std::ostream & o, State const & rhs)
{
	int to_print;

	o << "instruction : " << rhs.instruction << std::endl;
	o << "g: " << int(rhs.g) << std::endl;
	o << "corners position: ";
	for (auto i = 0; i < 8; i++)
	{
		to_print = 0;
		for (auto j = 2; j >= 0; j--)
		{
			to_print <<= 1;
			to_print |= rhs.compressed[48 +  j + ((7 - i)*3)];
		}
		o << to_print << " ";
	}
	o << std::endl;
	o << "edges position:   ";
	for (auto i = 0; i < 12; i++)
	{
		to_print = 0;
		for (auto j = 3; j >= 0; j--)
		{
			to_print <<= 1;
			to_print |= rhs.compressed[j + ((11 - i)*4)];
		}
		o << to_print << " ";
	}
    o << std::endl;
    o << "corners orientation: ";
    for (auto i = 0; i < 8; i++)
    {
        to_print = 0;
        to_print |= rhs.orientation[13 + ((7 - i)*2)];
        to_print <<= 1;
        to_print |= rhs.orientation[12 + ((7 - i)*2)];
        o << to_print << " ";
    }
    o << std::endl;
    o << "edges orientation:   ";
    for (auto i = 0; i < 12; i++)
    {
        to_print = 0;
        to_print |= rhs.orientation[11- i];
        o << to_print << " ";
    }
	o << std::endl;
	o << "compressed:" << std::endl;
	o << rhs.compressed << std::endl;
	o << "orientation:" << std::endl;
	o << rhs.orientation << std::endl;
	o << std::endl;
	return o;
}

std::vector<State *> State::get_nexts()
{
	std::vector<State *> nexts;
	for (auto next_instruction : moves_map[this->instruction])
		nexts.push_back(&move(*this, next_instruction));

	return nexts;
}
