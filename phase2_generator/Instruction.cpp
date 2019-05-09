#include "Instruction.hpp"
#include <map>
#include <string>

std::ostream & operator<<(std::ostream & o, Instruction const & rhs)
{
    std::map<Instruction, std::string> instruction_map;
    instruction_map[U] = "U";
    instruction_map[UR] = "U'";
    instruction_map[U2] = "U2";
    instruction_map[D] = "D";
    instruction_map[DR] = "D'";
    instruction_map[D2] = "D2";
    instruction_map[R2] = "R2";
    instruction_map[L2] = "L2";
    instruction_map[F2] = "F2";
    instruction_map[B2] = "B2";
    instruction_map[EMPTY] = "Empty";
    o << instruction_map[rhs];
	return o;
}