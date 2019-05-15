#include "TableLoader.hpp"

TableLoader::TableLoader(std::string file_name):
	file_name(file_name)
{
	openFile();
}

void TableLoader::openFile()
{
	file.open(file_name);
}

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
	int i = 0;
	std::bitset<72> set;
	while (i < len)
	{
		get_key_from_bin(buffer, i, &set);
		(*map)[set] = buffer[i + 9];
		i += 10;
	}
}

void TableLoader::load_map(std::unordered_map<std::bitset<72>, char> *map)
{
	char buffer[BUFF_SIZE];
	
	while (file.read(buffer, BUFF_SIZE))
		string_to_bitset(buffer, map, file.gcount());
	string_to_bitset(buffer, map, file.gcount());
	file.close();
}

void TableLoader::dump_map(std::unordered_map<std::bitset<72>, char> *map)
{
	char buffer[BUFF_SIZE];

	std::ofstream Wfile (file_name, std::ofstream::binary);
	int i = 0;

	for (auto data : (*map))
	{
		bitset_to_string(buffer, i, data.first);
		buffer[i + 9] = data.second;
		i += 10;
		if (i == BUFF_SIZE)
		{
			i = 0;
			Wfile.write(buffer, BUFF_SIZE);
		}
	}
	Wfile.write(buffer, i);
	Wfile.close();
}
