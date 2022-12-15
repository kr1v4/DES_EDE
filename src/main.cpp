#include "des/des.hpp"

int main()
{

	std::string pt = "Some little plain text for test.";
	std::string key = "$îöşN6$1";
	std::string key2 = "3òóF%ğòô";

	std::string enc_text = des::EDE(pt, key, key2);

	std::cout << "Plain Text: " << pt << "\n";
	std::cout << "Key: " << key << "\n";
	std::cout << "Key2: " << key2 << "\n";

	std::cout << "Encrypted text: " << enc_text << "\n";

	std::string dec_text = des::EDE(enc_text, key, key2, DES_MODE::DECRYPT);

	std::cout << "Decrypted Text: " << dec_text << "\n";

	return 0;
}