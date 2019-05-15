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

void TableLoader::bitset_to_string(char* buffer, int buffer_index, std::bitset<32> set)
{
	/*
	buffer[buffer_index] = 0;
	buffer[buffer_index] |= set[27] << 3;
	buffer[buffer_index] |= set[26] << 2;
	buffer[buffer_index] |= set[25] << 1;
	buffer[buffer_index] |= set[24];
	*/
	for (auto i = 0; i < 4; i++)
	{
		buffer[buffer_index + i] = 0;
		for (auto j = 7; j >= 0; j--)
		{
			buffer[buffer_index + i] |= set[(3 - i) * 8 + j] << j;
		}
	}
}

void TableLoader::get_key_from_bin(char* buffer, int start_index, std::bitset<72> *ret)
{
	(*ret)[71] = (buffer[start_index]) >> 7;
	(*ret)[70] = (buffer[start_index] & 64) >> 6;
	(*ret)[69] = (buffer[start_index] & 32) >> 5;
	(*ret)[68] = (buffer[start_index] & 16) >> 4;
	(*ret)[67] = (buffer[start_index] & 8) >> 3;
	(*ret)[66] = (buffer[start_index] & 4) >> 2;
	(*ret)[65] = (buffer[start_index] & 2) >> 1;
	(*ret)[64] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[63] = (buffer[start_index]) >> 7;
	(*ret)[62] = (buffer[start_index] & 64) >> 6;
	(*ret)[61] = (buffer[start_index] & 32) >> 5;
	(*ret)[60] = (buffer[start_index] & 16) >> 4;
	(*ret)[59] = (buffer[start_index] & 8) >> 3;
	(*ret)[58] = (buffer[start_index] & 4) >> 2;
	(*ret)[57] = (buffer[start_index] & 2) >> 1;
	(*ret)[56] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[55] = (buffer[start_index]) >> 7;
	(*ret)[54] = (buffer[start_index] & 64) >> 6;
	(*ret)[53] = (buffer[start_index] & 32) >> 5;
	(*ret)[52] = (buffer[start_index] & 16) >> 4;
	(*ret)[51] = (buffer[start_index] & 8) >> 3;
	(*ret)[50] = (buffer[start_index] & 4) >> 2;
	(*ret)[49] = (buffer[start_index] & 2) >> 1;
	(*ret)[48] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[47] = (buffer[start_index]) >> 7;
	(*ret)[46] = (buffer[start_index] & 64) >> 6;
	(*ret)[45] = (buffer[start_index] & 32) >> 5;
	(*ret)[44] = (buffer[start_index] & 16) >> 4;
	(*ret)[43] = (buffer[start_index] & 8) >> 3;
	(*ret)[42] = (buffer[start_index] & 4) >> 2;
	(*ret)[41] = (buffer[start_index] & 2) >> 1;
	(*ret)[40] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[39] = (buffer[start_index]) >> 7;
	(*ret)[38] = (buffer[start_index] & 64) >> 6;
	(*ret)[37] = (buffer[start_index] & 32) >> 5;
	(*ret)[36] = (buffer[start_index] & 16) >> 4;
	(*ret)[35] = (buffer[start_index] & 8) >> 3;
	(*ret)[34] = (buffer[start_index] & 4) >> 2;
	(*ret)[33] = (buffer[start_index] & 2) >> 1;
	(*ret)[32] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[31] = (buffer[start_index]) >> 7;
	(*ret)[30] = (buffer[start_index] & 64) >> 6;
	(*ret)[29] = (buffer[start_index] & 32) >> 5;
	(*ret)[28] = (buffer[start_index] & 16) >> 4;
	(*ret)[27] = (buffer[start_index] & 8) >> 3;
	(*ret)[26] = (buffer[start_index] & 4) >> 2;
	(*ret)[25] = (buffer[start_index] & 2) >> 1;
	(*ret)[24] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[23] = (buffer[start_index]) >> 7;
	(*ret)[22] = (buffer[start_index] & 64) >> 6;
	(*ret)[21] = (buffer[start_index] & 32) >> 5;
	(*ret)[20] = (buffer[start_index] & 16) >> 4;
	(*ret)[19] = (buffer[start_index] & 8) >> 3;
	(*ret)[18] = (buffer[start_index] & 4) >> 2;
	(*ret)[17] = (buffer[start_index] & 2) >> 1;
	(*ret)[16] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[15] = (buffer[start_index]) >> 7;
	(*ret)[14] = (buffer[start_index] & 64) >> 6;
	(*ret)[13] = (buffer[start_index] & 32) >> 5;
	(*ret)[12] = (buffer[start_index] & 16) >> 4;
	(*ret)[11] = (buffer[start_index] & 8) >> 3;
	(*ret)[10] = (buffer[start_index] & 4) >> 2;
	(*ret)[9] = (buffer[start_index] & 2) >> 1;
	(*ret)[8] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[7] = (buffer[start_index]) >> 7;
	(*ret)[6] = (buffer[start_index] & 64) >> 6;
	(*ret)[5] = (buffer[start_index] & 32) >> 5;
	(*ret)[4] = (buffer[start_index] & 16) >> 4;
	(*ret)[3] = (buffer[start_index] & 8) >> 3;
	(*ret)[2] = (buffer[start_index] & 4) >> 2;
	(*ret)[1] = (buffer[start_index] & 2) >> 1;
	(*ret)[0] = (buffer[start_index] & 1);
}

void TableLoader::get_key_from_bin(char* buffer, int start_index, std::bitset<32> *ret)
{
	(*ret)[31] = (buffer[start_index]) >> 7;
	(*ret)[30] = (buffer[start_index] & 64) >> 6;
	(*ret)[29] = (buffer[start_index] & 32) >> 5;
	(*ret)[28] = (buffer[start_index] & 16) >> 4;
	(*ret)[27] = (buffer[start_index] & 8) >> 3;
	(*ret)[26] = (buffer[start_index] & 4) >> 2;
	(*ret)[25] = (buffer[start_index] & 2) >> 1;
	(*ret)[24] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[23] = (buffer[start_index]) >> 7;
	(*ret)[22] = (buffer[start_index] & 64) >> 6;
	(*ret)[21] = (buffer[start_index] & 32) >> 5;
	(*ret)[20] = (buffer[start_index] & 16) >> 4;
	(*ret)[19] = (buffer[start_index] & 8) >> 3;
	(*ret)[18] = (buffer[start_index] & 4) >> 2;
	(*ret)[17] = (buffer[start_index] & 2) >> 1;
	(*ret)[16] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[15] = (buffer[start_index]) >> 7;
	(*ret)[14] = (buffer[start_index] & 64) >> 6;
	(*ret)[13] = (buffer[start_index] & 32) >> 5;
	(*ret)[12] = (buffer[start_index] & 16) >> 4;
	(*ret)[11] = (buffer[start_index] & 8) >> 3;
	(*ret)[10] = (buffer[start_index] & 4) >> 2;
	(*ret)[9] = (buffer[start_index] & 2) >> 1;
	(*ret)[8] = (buffer[start_index] & 1);
	start_index++;
	(*ret)[7] = (buffer[start_index]) >> 7;
	(*ret)[6] = (buffer[start_index] & 64) >> 6;
	(*ret)[5] = (buffer[start_index] & 32) >> 5;
	(*ret)[4] = (buffer[start_index] & 16) >> 4;
	(*ret)[3] = (buffer[start_index] & 8) >> 3;
	(*ret)[2] = (buffer[start_index] & 4) >> 2;
	(*ret)[1] = (buffer[start_index] & 2) >> 1;
	(*ret)[0] = (buffer[start_index] & 1);
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

void TableLoader::string_to_bitset(char* buffer, std::unordered_map<std::bitset<32>, char> *map, int len)
{
	//std::cout << buffer << std::endl;
	int i = 0;
	std::bitset<32> set;
	while (i < len)
	{
		get_key_from_bin(buffer, i, &set);
		(*map)[set] = buffer[i + 4];
		i += 5;
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

void TableLoader::load_map(std::unordered_map<std::bitset<32>, char> *map)
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

void TableLoader::dump_map(std::unordered_map<std::bitset<32>, char> *map)
{
	char buffer[BUFF_SIZE];

	std::ofstream Wfile (file_name, std::ofstream::binary);
	int i = 0;

	for (auto data : (*map))
	{
		bitset_to_string(buffer, i, data.first);
		buffer[i + 4] = data.second;
		i += 5;
		if (i == BUFF_SIZE)
		{
			i = 0;
			Wfile.write(buffer, BUFF_SIZE);
		}
	}
	Wfile.write(buffer, i);
	Wfile.close();
}
