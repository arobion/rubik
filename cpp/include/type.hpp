#pragma once

#include <bitset>
#include <limits>
#include <unordered_map>

#define BOUND_INF std::numeric_limits<float>::max()

typedef std::unordered_map<std::bitset<32>, char> P1OrientationTable;
typedef std::unordered_map<std::bitset<16>, char> P1SliceTable;
typedef std::unordered_map<std::bitset<72>, char> P2Table;