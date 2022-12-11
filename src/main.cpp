#include "des/des.hpp"

int main()
{

	std::string pt = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
	std::string key = "Lorem ";

	std::string enc_pt = des::process(pt, key);

	std::cout << "Plain Text: " << pt << "\n";
	std::cout << "Key: " << key << "\n";

	std::cout << "Encrypted: " << enc_pt << "\n";

	std::string dec_pt = des::process(enc_pt, key, DES_MODE::DECRYPT);

	std::cout << "Decrypted: " << dec_pt << "\n";


	return 0;
}