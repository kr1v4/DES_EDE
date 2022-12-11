#include "bitarray/bitarray.hpp"

int main()
{
	bitarray b("1000010000100010001110101111001111");
	bitarray c("0011010010101110101110101100001011");


	bitarray d = b ^ c;
}