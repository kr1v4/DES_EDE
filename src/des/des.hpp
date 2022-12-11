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

	public:
		des(const des& other) = delete;
		des(des&& other) = delete;

		des& operator = (const des& other) = delete;
		des& operator = (des& other) = delete;


	private:

		des() = default;

};




#endif // !DES_HPP