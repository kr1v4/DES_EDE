#include "keygen/keygen.hpp"

int main()
{

	bitarray input_key("0001001100110100010101110111100110011011101111001101111111110001");

	std::vector<bitarray> temp = keygen::generate_round_keys(input_key);

	for (auto& key : temp)
	{
		std::cout << key << "\n";
	}
}