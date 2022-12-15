#ifndef DES_HPP
#define DES_CPP
#include "../keygen/keygen.hpp"
#include "../utils/utils.hpp"

enum class DES_MODE{
	ENCRYPT,
	DECRYPT
};

class des
{
	public:

		static std::string process(std::string data_string, std::string key_string, DES_MODE mode = DES_MODE::ENCRYPT);
		static std::string EDE(std::string data_string, std::string key_strin, std::string key_string2, DES_MODE mode = DES_MODE::ENCRYPT);

	public:

		des(const des& other) = delete;
		des(des&& other) = delete;

		des& operator = (const des& other) = delete;
		des& operator = (des& other) = delete;

	private:

		static void fit_string(std::string &data_string);
		static bitarray IP1(const bitarray& block64);
		static bitarray FP1(const bitarray& block64);
		static bitarray f(const bitarray& right_block32, const bitarray& round_key48);
		static bitarray E(const bitarray& right_block32);
		static bitarray P(const bitarray& joined_blocks_d);
		static void split_permutated_block(const bitarray & permutated_block64, bitarray & left_block32, bitarray & right_block32);
		static bitarray join_blocks(const bitarray& left_block32, const bitarray& right_block32);


		static bitarray substitude(const bitarray& xor_result_block48);

	private:

		static const size_t m_block_size = 64;
		static const size_t m_ip_block_size = 64;
		static const size_t m_amount_of_rounds = 16;
		static const size_t m_e_block_size = 48;

	private:

		des() = default;

};




#endif // !DES_HPP