#include "des/des.hpp"

int main()
{

	std::string pt = "Some little plain text for test.";
	std::string key = "$îöşN6$1";
	std::string key2 = "3òóF%ğòô";

	std::string enc_pt_key = des::process(pt, key);
	std::string dec_pt_key2 = des::process(enc_pt_key, key2, DES_MODE::DECRYPT);
	std::string enc_pt_key_finish = des::process(dec_pt_key2, key);


	std::cout << "Plain Text: " << pt << "\n";
	std::cout << "Key: " << key << "\n";
	std::cout << "Key2: " << key2 << "\n";



	std::cout << "Encrypted text: " << enc_pt_key_finish << "\n";

	std::string dec_pt_key = des::process(enc_pt_key_finish, key, DES_MODE::DECRYPT);
	std::string enc_pt_key2 = des::process(dec_pt_key, key2);
	std::string dec_pt_key_finish = des::process(enc_pt_key2, key, DES_MODE::DECRYPT);


	std::cout << "Decrypted Text: " << dec_pt_key_finish << "\n";

	return 0;
}