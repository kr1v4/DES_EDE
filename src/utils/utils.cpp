#include "utils.hpp"

bitarray utils::string_to_bitarray(const std::string& string)
{
    size_t string_length = string.length();
    std::stringstream strings_bin;
    for (size_t i = 0; i < string_length; ++i)
    {
        std::bitset<8> current_letter(string[i]);
        strings_bin << current_letter.to_string();
    }
    bitarray generated_bitarray(strings_bin.str());
    return generated_bitarray;
}

std::string utils::bitarray_to_string(const bitarray& _bitarray)
{
    if (_bitarray.size() >= 8 || _bitarray.size() % 8 == 0)
    {
        size_t bitarray_length = _bitarray.size();
        std::string string_from_bin;

        size_t amount_of_letters = static_cast<size_t>(std::ceil(bitarray_length / 8.0));

        for (size_t i = 0; i < amount_of_letters; ++i)
        {
            bitarray letter_bits = _bitarray.sub_bitarray(i * 8, 8);
            std::string letter_bits_string = letter_bits.to_string();
            std::bitset<8> letter_bitset(letter_bits_string);
            char letter = static_cast<char>(letter_bitset.to_ulong() + 256);
            string_from_bin.push_back(letter);
        }
        return string_from_bin;
    }
    return std::string();
}
