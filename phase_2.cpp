/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:15:12 by arobion           #+#    #+#             */
/*   Updated: 2019/05/09 14:44:29 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

struct State
{
	State();
	State(State const & state);

	std::vector<char>	corners;
	std::vector<char>	edges;
	char				g;
	char				instruction;

	//State *				get_nexts();
};

State::State() :
	g(0),
	instruction(0)
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

std::ostream & operator<<(std::ostream & o, State const & rhs)
{
	o << "instruction : " << int(rhs.instruction) << std::endl;
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



/*
   std::vector<State *> State::get_nexts()
   {
   return
   }
   */

/*
void mov(State & state, char instruction)
{

}
*/

State & u(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 1;

	char tmp = state->corners[0];
	state->corners[0] = state->corners[3];
	state->corners[3] = state->corners[2];
	state->corners[2] = state->corners[1];
	state->corners[1] = tmp;
	tmp = state->edges[0];
	state->edges[0] = state->edges[3];
	state->edges[3] = state->edges[2];
	state->edges[2] = state->edges[1];
	state->edges[1] = tmp;

	return *state;
}

State & ur(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 7;

	char tmp = state->corners[0];
	state->corners[0] = state->corners[1];
	state->corners[1] = state->corners[2];
	state->corners[2] = state->corners[3];
	state->corners[3] = tmp;
	tmp = state->edges[0];
	state->edges[0] = state->edges[1];
	state->edges[1] = state->edges[2];
	state->edges[2] = state->edges[3];
	state->edges[3] = tmp;

	return *state;
}

State & u2(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 13;

	char tmp = state->corners[0];
	state->corners[0] = state->corners[2];
	state->corners[2] = tmp;

	tmp = state->corners[1];
	state->corners[1] = state->corners[3];
	state->corners[3] = tmp;

	tmp = state->edges[0];
	state->edges[0] = state->edges[2];
	state->edges[2] = tmp;

	tmp = state->edges[1];
	state->edges[1] = state->edges[3];
	state->edges[3] = tmp;

	return *state;
}

State & d(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 4;

	char tmp = state->corners[4];
	state->corners[4] = state->corners[5];
	state->corners[5] = state->corners[6];
	state->corners[6] = state->corners[7];
	state->corners[7] = tmp;
	tmp = state->edges[8];
	state->edges[8] = state->edges[9];
	state->edges[9] = state->edges[10];
	state->edges[10] = state->edges[11];
	state->edges[11] = tmp;

	return *state;
}

State & dr(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 10;

	char tmp = state->corners[4];
	state->corners[4] = state->corners[7];
	state->corners[7] = state->corners[6];
	state->corners[6] = state->corners[5];
	state->corners[5] = tmp;
	tmp = state->edges[8];
	state->edges[8] = state->edges[11];
	state->edges[11] = state->edges[10];
	state->edges[10] = state->edges[9];
	state->edges[9] = tmp;

	return *state;
}

State & d2(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 16;

	char tmp = state->corners[4];
	state->corners[4] = state->corners[6];
	state->corners[6] = tmp;

	tmp = state->corners[5];
	state->corners[5] = state->corners[7];
	state->corners[7] = tmp;

	tmp = state->edges[8];
	state->edges[8] = state->edges[10];
	state->edges[10] = tmp;

	tmp = state->edges[9];
	state->edges[9] = state->edges[11];
	state->edges[11] = tmp;

	return *state;
}

State & r2(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 14;

	char tmp = state->corners[0];
	state->corners[0] = state->corners[5];
	state->corners[5] = tmp;

	tmp = state->corners[1];
	state->corners[1] = state->corners[4];
	state->corners[4] = tmp;

	tmp = state->edges[1];
	state->edges[1] = state->edges[9];
	state->edges[9] = tmp;

	tmp = state->edges[5];
	state->edges[5] = state->edges[4];
	state->edges[4] = tmp;

	return *state;
}

State & l2(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 15;

	char tmp = state->corners[3];
	state->corners[3] = state->corners[6];
	state->corners[6] = tmp;

	tmp = state->corners[2];
	state->corners[2] = state->corners[7];
	state->corners[7] = tmp;

	tmp = state->edges[3];
	state->edges[3] = state->edges[11];
	state->edges[11] = tmp;

	tmp = state->edges[6];
	state->edges[6] = state->edges[7];
	state->edges[7] = tmp;

	return *state;
}

State & f2(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 17;

	char tmp = state->corners[1];
	state->corners[1] = state->corners[6];
	state->corners[6] = tmp;

	tmp = state->corners[2];
	state->corners[2] = state->corners[5];
	state->corners[5] = tmp;

	tmp = state->edges[2];
	state->edges[2] = state->edges[10];
	state->edges[10] = tmp;

	tmp = state->edges[6];
	state->edges[6] = state->edges[5];
	state->edges[5] = tmp;

	return *state;
}


State & b2(State & origin)
{ 
	State * state = new State(origin);
	state->instruction = 18;

	char tmp = state->corners[0];
	state->corners[0] = state->corners[7];
	state->corners[7] = tmp;

	tmp = state->corners[3];
	state->corners[3] = state->corners[4];
	state->corners[4] = tmp;

	tmp = state->edges[0];
	state->edges[0] = state->edges[8];
	state->edges[8] = tmp;

	tmp = state->edges[4];
	state->edges[4] = state->edges[7];
	state->edges[7] = tmp;

	return *state;
}

int main(void)
{
	/*
	State state1 = State();
	State state2 = State(state1);
	state1.corners[0] = 10;
	std::cout << state1;
	std::cout << state2;
	*/

	State s{};
	std::cout << s << std::endl;
	auto s2 = u(s);
	std::cout << s2<< std::endl;
	s2 = u2(s);
	std::cout << s2<< std::endl;
	s2 = ur(s);
	std::cout << s2<< std::endl;
	s2 = d(s);
	std::cout << s2<< std::endl;
	s2 = dr(s);
	std::cout << s2<< std::endl;
	s2 = d2(s);
	std::cout << s2<< std::endl;
	s2 = r2(s);
	std::cout << s2<< std::endl;
	s2 = l2(s);
	std::cout << s2<< std::endl;
	s2 = f2(s);
	std::cout << s2<< std::endl;
	s2 = b2(s);
	std::cout << s2<< std::endl;
}
