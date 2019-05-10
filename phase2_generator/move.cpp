#include "move.hpp"
#include "Instruction.hpp"
#include <map>

State & u(State & origin)
{ 
	State * state = new State(origin, U);

	char tmp = 0;
	tmp |= state->compressed[71] << 2;
	tmp |= state->compressed[70] << 1;
	tmp |= state->compressed[69];

	state->compressed[71] = state->compressed[62];
	state->compressed[70] = state->compressed[61];
	state->compressed[69] = state->compressed[60];

	state->compressed[62] = state->compressed[65];
	state->compressed[61] = state->compressed[64];
	state->compressed[60] = state->compressed[63];

	state->compressed[65] = state->compressed[68];
	state->compressed[64] = state->compressed[67];
	state->compressed[63] = state->compressed[66];

	state->compressed[68] = tmp >> 2;
	state->compressed[67] = (tmp & 2) >> 1;
	state->compressed[66] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[47] << 3;
	tmp |= state->compressed[46] << 2;
	tmp |= state->compressed[45] << 1;
	tmp |= state->compressed[44];
	
	state->compressed[47] = state->compressed[35];
	state->compressed[46] = state->compressed[34];
	state->compressed[45] = state->compressed[33];
	state->compressed[44] = state->compressed[32];
	
	state->compressed[35] = state->compressed[39];
	state->compressed[34] = state->compressed[38];
	state->compressed[33] = state->compressed[37];
	state->compressed[32] = state->compressed[36];

	state->compressed[39] = state->compressed[43];
	state->compressed[38] = state->compressed[42];
	state->compressed[37] = state->compressed[41];
	state->compressed[36] = state->compressed[40];

	state->compressed[43] = tmp >> 3;
	state->compressed[42] = (tmp & 4) >> 2;
	state->compressed[41] = (tmp & 2) >> 1;
	state->compressed[40] = tmp & 1;

	return *state;
}

State & ur(State & origin)
{ 
	State * state = new State(origin, UR);

	char tmp = 0;
	tmp |= state->compressed[71] << 2;
	tmp |= state->compressed[70] << 1;
	tmp |= state->compressed[69];

	state->compressed[71] = state->compressed[68];
	state->compressed[70] = state->compressed[67];
	state->compressed[69] = state->compressed[66];

	state->compressed[68] = state->compressed[65];
	state->compressed[67] = state->compressed[64];
	state->compressed[66] = state->compressed[63];

	state->compressed[65] = state->compressed[62];
	state->compressed[64] = state->compressed[61];
	state->compressed[63] = state->compressed[60];

	state->compressed[62] = tmp >> 2;
	state->compressed[61] = (tmp & 2) >> 1;
	state->compressed[60] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[47] << 3;
	tmp |= state->compressed[46] << 2;
	tmp |= state->compressed[45] << 1;
	tmp |= state->compressed[44];
	
	state->compressed[47] = state->compressed[43];
	state->compressed[46] = state->compressed[42];
	state->compressed[45] = state->compressed[41];
	state->compressed[44] = state->compressed[40];
	
	state->compressed[43] = state->compressed[39];
	state->compressed[42] = state->compressed[38];
	state->compressed[41] = state->compressed[37];
	state->compressed[40] = state->compressed[36];

	state->compressed[39] = state->compressed[35];
	state->compressed[38] = state->compressed[34];
	state->compressed[37] = state->compressed[33];
	state->compressed[36] = state->compressed[32];

	state->compressed[35] = tmp >> 3;
	state->compressed[34] = (tmp & 4) >> 2;
	state->compressed[33] = (tmp & 2) >> 1;
	state->compressed[32] = tmp & 1;

	return *state;
}

State & u2(State & origin)
{ 
	State * state = new State(origin, U2);

	char tmp = 0;
	tmp |= state->compressed[71] << 2;
	tmp |= state->compressed[70] << 1;
	tmp |= state->compressed[69];

	state->compressed[71] = state->compressed[65];
	state->compressed[70] = state->compressed[64];
	state->compressed[69] = state->compressed[63];

	state->compressed[65] = tmp >> 2;
	state->compressed[64] = (tmp & 2) >> 1;
	state->compressed[63] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[68] << 2;
	tmp |= state->compressed[67] << 1;
	tmp |= state->compressed[66];

	state->compressed[68] = state->compressed[62];
	state->compressed[67] = state->compressed[61];
	state->compressed[66] = state->compressed[60];

	state->compressed[62] = tmp >> 2;
	state->compressed[61] = (tmp & 2) >> 1;
	state->compressed[60] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[47] << 3;
	tmp |= state->compressed[46] << 2;
	tmp |= state->compressed[45] << 1;
	tmp |= state->compressed[44];
	
	state->compressed[47] = state->compressed[39];
	state->compressed[46] = state->compressed[38];
	state->compressed[45] = state->compressed[37];
	state->compressed[44] = state->compressed[36];
	
	state->compressed[39] = tmp >> 3;
	state->compressed[38] = (tmp & 4) >> 2;
	state->compressed[37] = (tmp & 2) >> 1;
	state->compressed[36] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[43] << 3;
	tmp |= state->compressed[42] << 2;
	tmp |= state->compressed[41] << 1;
	tmp |= state->compressed[40];

	state->compressed[43] = state->compressed[35];
	state->compressed[42] = state->compressed[34];
	state->compressed[41] = state->compressed[33];
	state->compressed[40] = state->compressed[32];

	state->compressed[35] = tmp >> 3;
	state->compressed[34] = (tmp & 4) >> 2;
	state->compressed[33] = (tmp & 2) >> 1;
	state->compressed[32] = tmp & 1;

	return *state;
}


State & d(State & origin)
{ 
	State * state = new State(origin, D);

	char tmp = 0;
	tmp |= state->compressed[59] << 2;
	tmp |= state->compressed[58] << 1;
	tmp |= state->compressed[57];

	state->compressed[59] = state->compressed[56];
	state->compressed[58] = state->compressed[55];
	state->compressed[57] = state->compressed[54];

	state->compressed[56] = state->compressed[53];
	state->compressed[55] = state->compressed[52];
	state->compressed[54] = state->compressed[51];

	state->compressed[53] = state->compressed[50];
	state->compressed[52] = state->compressed[49];
	state->compressed[51] = state->compressed[48];

	state->compressed[50] = tmp >> 2;
	state->compressed[49] = (tmp & 2) >> 1;
	state->compressed[48] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[15] << 3;
	tmp |= state->compressed[14] << 2;
	tmp |= state->compressed[13] << 1;
	tmp |= state->compressed[12];
	
	state->compressed[15] = state->compressed[11];
	state->compressed[14] = state->compressed[10];
	state->compressed[13] = state->compressed[9];
	state->compressed[12] = state->compressed[8];
	
	state->compressed[11] = state->compressed[7];
	state->compressed[10] = state->compressed[6];
	state->compressed[9] = state->compressed[5];
	state->compressed[8] = state->compressed[4];

	state->compressed[7] = state->compressed[3];
	state->compressed[6] = state->compressed[2];
	state->compressed[5] = state->compressed[1];
	state->compressed[4] = state->compressed[0];

	state->compressed[3] = tmp >> 3;
	state->compressed[2] = (tmp & 4) >> 2;
	state->compressed[1] = (tmp & 2) >> 1;
	state->compressed[0] = tmp & 1;

	return *state;
}

State & dr(State & origin)
{ 
	State * state = new State(origin, DR);

	char tmp = 0;
	tmp |= state->compressed[59] << 2;
	tmp |= state->compressed[58] << 1;
	tmp |= state->compressed[57];

	state->compressed[59] = state->compressed[50];
	state->compressed[58] = state->compressed[49];
	state->compressed[57] = state->compressed[48];

	state->compressed[50] = state->compressed[53];
	state->compressed[49] = state->compressed[52];
	state->compressed[48] = state->compressed[51];

	state->compressed[53] = state->compressed[56];
	state->compressed[52] = state->compressed[55];
	state->compressed[51] = state->compressed[54];

	state->compressed[56] = tmp >> 2;
	state->compressed[55] = (tmp & 2) >> 1;
	state->compressed[54] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[15] << 3;
	tmp |= state->compressed[14] << 2;
	tmp |= state->compressed[13] << 1;
	tmp |= state->compressed[12];
	
	state->compressed[15] = state->compressed[3];
	state->compressed[14] = state->compressed[2];
	state->compressed[13] = state->compressed[1];
	state->compressed[12] = state->compressed[0];
	
	state->compressed[3] = state->compressed[7];
	state->compressed[2] = state->compressed[6];
	state->compressed[1] = state->compressed[5];
	state->compressed[0] = state->compressed[4];

	state->compressed[7] = state->compressed[11];
	state->compressed[6] = state->compressed[10];
	state->compressed[5] = state->compressed[9];
	state->compressed[4] = state->compressed[8];

	state->compressed[11] = tmp >> 3;
	state->compressed[10] = (tmp & 4) >> 2;
	state->compressed[9] = (tmp & 2) >> 1;
	state->compressed[8] = tmp & 1;

	return *state;
}

State & d2(State & origin)
{ 
	State * state = new State(origin, D2);

	char tmp = 0;
	tmp |= state->compressed[59] << 2;
	tmp |= state->compressed[58] << 1;
	tmp |= state->compressed[57];

	state->compressed[59] = state->compressed[53];
	state->compressed[58] = state->compressed[52];
	state->compressed[57] = state->compressed[51];

	state->compressed[53] = tmp >> 2;
	state->compressed[52] = (tmp & 2) >> 1;
	state->compressed[51] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[56] << 2;
	tmp |= state->compressed[55] << 1;
	tmp |= state->compressed[54];

	state->compressed[56] = state->compressed[50];
	state->compressed[55] = state->compressed[49];
	state->compressed[54] = state->compressed[48];

	state->compressed[50] = tmp >> 2;
	state->compressed[49] = (tmp & 2) >> 1;
	state->compressed[48] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[15] << 3;
	tmp |= state->compressed[14] << 2;
	tmp |= state->compressed[13] << 1;
	tmp |= state->compressed[12];
	
	state->compressed[15] = state->compressed[7];
	state->compressed[14] = state->compressed[6];
	state->compressed[13] = state->compressed[5];
	state->compressed[12] = state->compressed[4];
	
	state->compressed[7] = tmp >> 3;
	state->compressed[6] = (tmp & 4) >> 2;
	state->compressed[5] = (tmp & 2) >> 1;
	state->compressed[4] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[11] << 3;
	tmp |= state->compressed[10] << 2;
	tmp |= state->compressed[9] << 1;
	tmp |= state->compressed[8];

	state->compressed[11] = state->compressed[3];
	state->compressed[10] = state->compressed[2];
	state->compressed[9] = state->compressed[1];
	state->compressed[8] = state->compressed[0];

	state->compressed[3] = tmp >> 3;
	state->compressed[2] = (tmp & 4) >> 2;
	state->compressed[1] = (tmp & 2) >> 1;
	state->compressed[0] = tmp & 1;

	return *state;
}

State & r2(State & origin)
{ 
	State * state = new State(origin, R2);

	char tmp = 0;
	tmp |= state->compressed[71] << 2;
	tmp |= state->compressed[70] << 1;
	tmp |= state->compressed[69];

	state->compressed[71] = state->compressed[56];
	state->compressed[70] = state->compressed[55];
	state->compressed[69] = state->compressed[54];

	state->compressed[56] = tmp >> 2;
	state->compressed[55] = (tmp & 2) >> 1;
	state->compressed[54] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[68] << 2;
	tmp |= state->compressed[67] << 1;
	tmp |= state->compressed[66];

	state->compressed[68] = state->compressed[59];
	state->compressed[67] = state->compressed[58];
	state->compressed[66] = state->compressed[57];

	state->compressed[59] = tmp >> 2;
	state->compressed[58] = (tmp & 2) >> 1;
	state->compressed[57] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[43] << 3;
	tmp |= state->compressed[42] << 2;
	tmp |= state->compressed[41] << 1;
	tmp |= state->compressed[40];
	
	state->compressed[43] = state->compressed[11];
	state->compressed[42] = state->compressed[10];
	state->compressed[41] = state->compressed[9];
	state->compressed[40] = state->compressed[8];
	
	state->compressed[11] = tmp >> 3;
	state->compressed[10] = (tmp & 4) >> 2;
	state->compressed[9] = (tmp & 2) >> 1;
	state->compressed[8] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[27] << 3;
	tmp |= state->compressed[26] << 2;
	tmp |= state->compressed[25] << 1;
	tmp |= state->compressed[24];

	state->compressed[27] = state->compressed[31];
	state->compressed[26] = state->compressed[30];
	state->compressed[25] = state->compressed[29];
	state->compressed[24] = state->compressed[28];

	state->compressed[31] = tmp >> 3;
	state->compressed[30] = (tmp & 4) >> 2;
	state->compressed[29] = (tmp & 2) >> 1;
	state->compressed[28] = tmp & 1;

	return *state;
}

State & l2(State & origin)
{ 
	State * state = new State(origin, L2);

	char tmp = 0;
	tmp |= state->compressed[62] << 2;
	tmp |= state->compressed[61] << 1;
	tmp |= state->compressed[60];

	state->compressed[62] = state->compressed[53];
	state->compressed[61] = state->compressed[52];
	state->compressed[60] = state->compressed[51];

	state->compressed[53] = tmp >> 2;
	state->compressed[52] = (tmp & 2) >> 1;
	state->compressed[51] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[65] << 2;
	tmp |= state->compressed[64] << 1;
	tmp |= state->compressed[63];

	state->compressed[65] = state->compressed[50];
	state->compressed[64] = state->compressed[49];
	state->compressed[63] = state->compressed[48];

	state->compressed[50] = tmp >> 2;
	state->compressed[49] = (tmp & 2) >> 1;
	state->compressed[48] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[35] << 3;
	tmp |= state->compressed[34] << 2;
	tmp |= state->compressed[33] << 1;
	tmp |= state->compressed[32];
	
	state->compressed[35] = state->compressed[3];
	state->compressed[34] = state->compressed[2];
	state->compressed[33] = state->compressed[1];
	state->compressed[32] = state->compressed[0];
	
	state->compressed[3] = tmp >> 3;
	state->compressed[2] = (tmp & 4) >> 2;
	state->compressed[1] = (tmp & 2) >> 1;
	state->compressed[0] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[23] << 3;
	tmp |= state->compressed[22] << 2;
	tmp |= state->compressed[21] << 1;
	tmp |= state->compressed[20];

	state->compressed[23] = state->compressed[19];
	state->compressed[22] = state->compressed[18];
	state->compressed[21] = state->compressed[17];
	state->compressed[20] = state->compressed[16];

	state->compressed[19] = tmp >> 3;
	state->compressed[18] = (tmp & 4) >> 2;
	state->compressed[17] = (tmp & 2) >> 1;
	state->compressed[16] = tmp & 1;

	return *state;
}

State & f2(State & origin)
{ 
	State * state = new State(origin, F2);

	char tmp = 0;
	tmp |= state->compressed[68] << 2;
	tmp |= state->compressed[67] << 1;
	tmp |= state->compressed[66];

	state->compressed[68] = state->compressed[53];
	state->compressed[67] = state->compressed[52];
	state->compressed[66] = state->compressed[51];

	state->compressed[53] = tmp >> 2;
	state->compressed[52] = (tmp & 2) >> 1;
	state->compressed[51] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[65] << 2;
	tmp |= state->compressed[64] << 1;
	tmp |= state->compressed[63];

	state->compressed[65] = state->compressed[56];
	state->compressed[64] = state->compressed[55];
	state->compressed[63] = state->compressed[54];

	state->compressed[56] = tmp >> 2;
	state->compressed[55] = (tmp & 2) >> 1;
	state->compressed[54] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[39] << 3;
	tmp |= state->compressed[38] << 2;
	tmp |= state->compressed[37] << 1;
	tmp |= state->compressed[36];
	
	state->compressed[39] = state->compressed[7];
	state->compressed[38] = state->compressed[6];
	state->compressed[37] = state->compressed[5];
	state->compressed[36] = state->compressed[4];
	
	state->compressed[7] = tmp >> 3;
	state->compressed[6] = (tmp & 4) >> 2;
	state->compressed[5] = (tmp & 2) >> 1;
	state->compressed[4] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[23] << 3;
	tmp |= state->compressed[22] << 2;
	tmp |= state->compressed[21] << 1;
	tmp |= state->compressed[20];

	state->compressed[23] = state->compressed[27];
	state->compressed[22] = state->compressed[26];
	state->compressed[21] = state->compressed[25];
	state->compressed[20] = state->compressed[24];

	state->compressed[27] = tmp >> 3;
	state->compressed[26] = (tmp & 4) >> 2;
	state->compressed[25] = (tmp & 2) >> 1;
	state->compressed[24] = tmp & 1;

	return *state;
}


State & b2(State & origin)
{ 
	State * state = new State(origin, B2);

	char tmp = 0;
	tmp |= state->compressed[71] << 2;
	tmp |= state->compressed[70] << 1;
	tmp |= state->compressed[69];

	state->compressed[71] = state->compressed[50];
	state->compressed[70] = state->compressed[49];
	state->compressed[69] = state->compressed[48];

	state->compressed[50] = tmp >> 2;
	state->compressed[49] = (tmp & 2) >> 1;
	state->compressed[48] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[62] << 2;
	tmp |= state->compressed[61] << 1;
	tmp |= state->compressed[60];

	state->compressed[62] = state->compressed[59];
	state->compressed[61] = state->compressed[58];
	state->compressed[60] = state->compressed[57];

	state->compressed[59] = tmp >> 2;
	state->compressed[58] = (tmp & 2) >> 1;
	state->compressed[57] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[47] << 3;
	tmp |= state->compressed[46] << 2;
	tmp |= state->compressed[45] << 1;
	tmp |= state->compressed[44];
	
	state->compressed[47] = state->compressed[15];
	state->compressed[46] = state->compressed[14];
	state->compressed[45] = state->compressed[13];
	state->compressed[44] = state->compressed[12];
	
	state->compressed[15] = tmp >> 3;
	state->compressed[14] = (tmp & 4) >> 2;
	state->compressed[13] = (tmp & 2) >> 1;
	state->compressed[12] = tmp & 1;

	tmp = 0;
	tmp |= state->compressed[31] << 3;
	tmp |= state->compressed[30] << 2;
	tmp |= state->compressed[29] << 1;
	tmp |= state->compressed[28];

	state->compressed[31] = state->compressed[19];
	state->compressed[30] = state->compressed[18];
	state->compressed[29] = state->compressed[17];
	state->compressed[28] = state->compressed[16];

	state->compressed[19] = tmp >> 3;
	state->compressed[18] = (tmp & 4) >> 2;
	state->compressed[17] = (tmp & 2) >> 1;
	state->compressed[16] = tmp & 1;

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
