#include <fstream>
#include <iostream>
#include <bitset>
#include <unordered_map>

#define BUFF_SIZE 100000

class TableLoader
{
public:
	TableLoader(std::string file_name);
	void	openFile();
	void 	bitset_to_string(char* buffer, int, std::bitset<72>);
	void 	bitset_to_string(char* buffer, int, std::bitset<28>);
	void 	bitset_to_string(char* buffer, int, std::bitset<16>);

	void 	string_to_bitset(char*, std::unordered_map<std::bitset<72>, char> *, int);
	void 	string_to_bitset(char*, std::unordered_map<std::bitset<28>, char>, int);
	void 	string_to_bitset(char*, std::unordered_map<std::bitset<16>, char>, int);

	void 	get_key_from_bin(char*, int, std::bitset<72> *);
	void 	get_key_from_bin(char*, int, std::bitset<28> *);
	void 	get_key_from_bin(char*, int, std::bitset<16> *);
	
	void 	load_map(std::unordered_map<std::bitset<72>, char> *);
	void 	load_map(std::unordered_map<std::bitset<28>, char> *);
	void 	load_map(std::unordered_map<std::bitset<16>, char> *);

	void 	dump_map(std::unordered_map<std::bitset<72>, char> *);
	void 	dump_map(std::unordered_map<std::bitset<28>, char> *);
	void 	dump_map(std::unordered_map<std::bitset<16>, char> *);

	std::string		file_name;
	std::fstream	file;

};
