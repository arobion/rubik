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
    corners_orientation(origin.corners_orientation),
    edges_orientation(origin.edges_orientation)
{
}

State::State(State const & origin, Instruction instruction) :
	g(origin.g + 1),
	instruction(instruction),
	compressed(origin.compressed),
    corners_orientation(origin.corners_orientation),
    edges_orientation(origin.edges_orientation)
{
}

State & State::operator=(State const & rhs)
{
	if (this != &rhs)
	{
		this->g = rhs.g;
		this->instruction = rhs.instruction;
		this->compressed = rhs.compressed;
        this->corners_orientation = rhs.corners_orientation;
        this->edges_orientation = rhs.edges_orientation;
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
        to_print |= rhs.corners_orientation[1 + ((7 - i)*2)];
        to_print <<= 1;
        to_print |= rhs.corners_orientation[(7 - i)*2];
        o << to_print << " ";
    }
    o << std::endl;
    o << "edges orientation:   ";
    for (auto i = 0; i < 12; i++)
    {
        to_print = 0;
        to_print |= rhs.edges_orientation[11- i];
        o << to_print << " ";
    }
	o << std::endl;
	o << "compressed:" << std::endl;
	o << rhs.compressed << std::endl;
	o << "orientation:" << std::endl;
	o << rhs.corners_orientation << rhs.edges_orientation << std::endl;
	o << std::endl;
	return o;
}


std::vector<std::shared_ptr<State>> State::get_nexts_1()
{
	static std::unordered_map<Instruction, std::vector<Instruction>> moves_map_1{
		{U, {D, DR, D2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{UR, {D, DR, D2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{U2, {D, DR, D2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},

		{D, {U, UR, U2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{DR, {U, UR, U2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{D2, {U, UR, U2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}},

		{L, {U, UR, U2, D, DR, D2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{LR, {U, UR, U2, D, DR, D2, R, RR, R2, F, FR, F2, B, BR, B2}},
		{L2, {U, UR, U2, D, DR, D2, R, RR, R2, F, FR, F2, B, BR, B2}},

		{L, {U, UR, U2, D, DR, D2, L, LR, L2, F, FR, F2, B, BR, B2}},
		{LR, {U, UR, U2, D, DR, D2, L, LR, L2, F, FR, F2, B, BR, B2}},
		{L2, {U, UR, U2, D, DR, D2, L, LR, L2, F, FR, F2, B, BR, B2}},

		{F, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, B, BR, B2}},
		{FR, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, B, BR, B2}},
		{F2, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, B, BR, B2}},

		{B, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, F, FR, F2}},
		{BR, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, F, FR, F2}},
		{B2, {U, UR, U2, D, DR, D2, R, RR, R2, L, LR, L2, F, FR, F2}},

		{EMPTY, {U, UR, U2, D, DR, D2, L, LR, L2, R, RR, R2, F, FR, F2, B, BR, B2}}
	};

	std::vector<std::shared_ptr<State>> nexts;
	for (auto next_instruction : moves_map_1[this->instruction])
		nexts.push_back(move(*this, next_instruction));
	return nexts;
}


std::vector<std::shared_ptr<State>> State::get_nexts_2()
{
	static std::unordered_map<Instruction, std::vector<Instruction>> moves_map_2{
		{U, {D, DR, D2, L2, R2, F2, B2}},
		{UR, {D, DR, D2, L2, R2, F2, B2}},
		{U2, {D, DR, D2, L2, R2, F2, B2}},

		{D, {U, UR, U2, L2, R2, F2, B2}},
		{DR, {U, UR, U2, L2, R2, F2, B2}},
		{D2, {U, UR, U2, L2, R2, F2, B2}},

		{L2, {U, UR, U2, D, DR, D2, R2, F2, B2}},
		{R2, {U, UR, U2, D, DR, D2, L2, F2, B2}},

		{F2, {U, UR, U2, D, DR, D2, L2, R2, B2}},
		{B2, {U, UR, U2, D, DR, D2, L2, R2, F2}},

		{EMPTY, {U, UR, U2, D, DR, D2, L2, R2, F2, B2}}
	};

	std::vector<std::shared_ptr<State>> nexts;
	for (auto next_instruction : moves_map_2[this->instruction])
		nexts.push_back(move(*this, next_instruction));
	return nexts;
}

std::bitset<16>		State::get_UD_slice_permutation(void)
{
	
	std::bitset<16> ret;

	ret[15] = this->compressed[31];
	ret[14] = this->compressed[30];
	ret[13] = this->compressed[29];
	ret[12] = this->compressed[28];

	ret[11] = this->compressed[27];
	ret[10] = this->compressed[26];
	ret[9] = this->compressed[25];
	ret[8] = this->compressed[24];

	ret[7] = this->compressed[23];
	ret[6] = this->compressed[22];
	ret[5] = this->compressed[21];
	ret[4] = this->compressed[20];

	ret[3] = this->compressed[19];
	ret[2] = this->compressed[18];
	ret[1] = this->compressed[17];
	ret[0] = this->compressed[16];

	return ret;
}
