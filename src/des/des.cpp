#include "des.hpp"

std::string des::process(std::string data_string, std::string key_string, DES_MODE mode)
{
	bitarray data_bin = utils::string_to_bitarray(data_string);

	std::cout << data_bin << "\n";

	std::string data_str = utils::bitarray_to_string(data_bin);


	std::cout << data_str << "\n";
	return std::string();
}