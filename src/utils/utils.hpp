#ifndef UTILS_HPP
#define UTILS_HPP
#include "../bitarray/bitarray.hpp"
#include <sstream>
#include <bitset>

class utils
{

	public:
		static bitarray string_to_bitarray(const std::string& string);
		static std::string bitarray_to_string(const bitarray& bitarray);


	public:
		utils(const utils& other) = delete;
		utils(utils&& other) = delete;

		utils& operator = (const utils& other) = delete;
		utils& operator = (utils& other) = delete;
	private:

		utils() = default;
};


#endif // !UTILS_HPP
