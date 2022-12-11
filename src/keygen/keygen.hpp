#ifndef KEYGEN_HPP
#define KEYGEN_HPP
#include "../bitarray/bitarray.hpp"

class keygen
{
	public:
		static std::vector<bitarray> generate_round_keys(const bitarray& key64);

	public:

		keygen(const keygen& other) = delete;
		keygen(keygen&& other) = delete;

		keygen& operator = (const keygen& other) = delete;
		keygen& operator = (keygen& other) = delete;

	private:
		static const size_t m_input_key_length = 64;
		static const size_t m_permutated_key_length = 56;
		static const size_t m_amount_of_keys = 16;
		static const size_t m_round_key_length = 48;
	private:
		static bitarray PC1(const bitarray& key64);
		static bitarray PC2(const bitarray& key56);
		static void split_permutated_key(const bitarray & permutated_key56, bitarray& left_block28, bitarray& right_block28);
		static void left_rotate_blocks(bitarray& left_block28, bitarray& right_block28, size_t iteration_number);
		static bitarray join_blocks(const bitarray& left_block28, const bitarray& right_block28);

	private:

		keygen() = default;


};


#endif // !KEYGEN_HPP