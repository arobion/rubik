#include "TableLoader.hpp"

void TableLoader::bitset_to_string(char* buffer, int buffer_index, std::bitset<72> set)
{
	for (auto i = 0; i < 9; i++)
	{
		buffer[buffer_index + i] = 0;
		for (auto j = 7; j >= 0; j--)
		{
			buffer[buffer_index + i] |= set[(8 - i) * 8 + j] << j;
		}
	}
}

void TableLoader::get_key_from_bin(char* buffer, int start_index, std::bitset<72> *ret)
{
	for (auto i = 0; i < 9; i++)
	{
		for (auto j = 7; j >= 0; j--)
			(*ret)[(8 - i) * 8 + j] = (buffer[start_index + i] & (1 << j)) >> j;
	}
}

void TableLoader::string_to_bitset(char* buffer, std::unordered_map<std::bitset<72>, char> *map, int len)
{
	(void)buffer;
	(void)map;
	int i = 0;
	while (i < len)
	{
		//(*map)[get_key_from_bin(buffer, i)] = buffer[i + 9];
		i += 10;
	}
}

void load_map(std::string file_name, std::unordered_map<std::bitset<72>, char> *map)
{
	(void)file_name;
	(void)map;
	/*
	//write in file
	std::ofstream phase2FileW ("phase2File.bin", std::ofstream::binary);
	char buffer[10000];
	int i = 0;
	for (auto data : bfs_map)
	{
		bitset_to_string(buffer, i, data.first);
		buffer[i + 9] = data.second;
		i += 10;
		if (i == BUFF_SIZE)
		{
			i = 0;
			phase2FileW.write(buffer, BUFF_SIZE);
		}
	}
	phase2FileW.write(buffer, i);
	phase2FileW.close();
	//read in file
	std::unordered_map<std::bitset<72>, char> test;
	std::ifstream phase2FileR ("phase2File.bin", std::ofstream::binary);

	while (phase2FileR.read(buffer, BUFF_SIZE))
		string_to_bitset(buffer, &test, phase2FileR.gcount());
	string_to_bitset(buffer, &test, phase2FileR.gcount());
	phase2FileR.close();
	*/

}
