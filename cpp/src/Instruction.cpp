#include "Instruction.hpp"
#include <string>
#include <unordered_map>

std::ostream & operator<<(std::ostream & o, Instruction const & rhs)
{
    static std::unordered_map<Instruction, std::string> instruction_map{
        {U, "U"}, {UR, "U'"}, {U2, "U2"},
        {D, "D"}, {DR, "D'"}, {D2, "D2"},
        {L, "L"}, {LR, "L'"}, {L2, "L2"},
        {R, "R"}, {RR, "R'"}, {R2, "R2"},
        {F, "F"}, {FR, "F'"}, {F2, "F2"},
        {B, "B"}, {BR, "B'"}, {B2, "B2"},
        {EMPTY, "Empty"}
    };
    o << instruction_map[rhs];
	return o;
}
