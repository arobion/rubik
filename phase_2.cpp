/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:15:12 by arobion           #+#    #+#             */
/*   Updated: 2019/05/09 14:12:14 by arobion          ###   ########.fr       */
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
}
