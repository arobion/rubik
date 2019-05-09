#include "move.hpp"
#include "Instruction.hpp"
#include <map>

State & u(State & origin)
{ 
	State * state = new State(origin, U);

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
	State * state = new State(origin, UR);

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
	State * state = new State(origin, U2);

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
	State * state = new State(origin, D);

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
	State * state = new State(origin, DR);

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
	State * state = new State(origin, D2);

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
	State * state = new State(origin, R2);

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
	State * state = new State(origin, L2);

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
	State * state = new State(origin, F2);

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
	State * state = new State(origin, B2);

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

State & move(State & origin, Instruction instruction)
{
	std::map<Instruction, State & (*)(State &)> move_ptr;
    move_ptr[U] = u;
    move_ptr[UR] = ur;
    move_ptr[U2] = u2;
    move_ptr[D] = d;
    move_ptr[DR] = dr;
    move_ptr[D2] = d2;
    move_ptr[R2] = r2;
    move_ptr[L2] = l2;
    move_ptr[F2] = f2;
    move_ptr[B2] = b2;
	return move_ptr[instruction](origin);
}