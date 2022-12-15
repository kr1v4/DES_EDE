#include "keygen.hpp"


std::vector<bitarray> keygen::generate_round_keys(const bitarray& key64)
{
    if (key64.size() == m_input_key_length)
    {
        std::vector<bitarray> generated_keys;

        std::cout << "Input Key:" << key64 << "\n";

        bitarray permutated_key56 = PC1(key64);

        std::cout << "Permutated Key: " << permutated_key56 << "\n";

        bitarray left_block28;
        bitarray right_block28;

        split_permutated_key(permutated_key56, left_block28, right_block28);

        for (size_t i = 0; i < m_amount_of_keys; ++i)
        {
            std::cout << "Current L: " << left_block28 << "\n";
            std::cout << "Current R: " << right_block28 << "\n";
            bitarray current_key48;
            left_rotate_blocks(left_block28, right_block28, i);

            std::cout << "Rotate n = " << i << "\n";

            std::cout << "Rotated L: " << left_block28 << "\n";
            std::cout << "Rotated R: " << right_block28 << "\n";

            bitarray joined_block56 = join_blocks(left_block28, right_block28);

            bitarray round_key48 = PC2(joined_block56);

            std::cout << "generated key: " << round_key48 << "\n";
            generated_keys.push_back(round_key48);
        }
        return generated_keys;
    }
    return std::vector<bitarray>();
}

bitarray keygen::PC1(const bitarray& key64)
{
    if (key64.size() == m_input_key_length)
    {
        int pc1[64] = {

            57  , 49  , 41  , 33  , 25  , 17  , 9   ,

            1   , 58  , 50  , 42  , 34  , 26  , 18  ,

            10  , 2   , 59  , 51  , 43  , 35  , 27  ,

            19  , 11  , 3   , 60  , 52  , 44  , 36  ,

            63  , 55  , 47  , 39  , 31  , 23  , 15  ,

            7   , 62  , 54  , 46  , 38  , 30  , 22  ,

            14  , 6   , 61  , 53  , 45  , 37  , 29  ,

            21  , 13  , 5   , 28  , 20  , 12  , 4

        };
        bitarray permutated_key56;
        for (size_t i = 0; i < m_permutated_key_length; ++i)
        {
            permutated_key56.push_back(key64.test(pc1[i] - 1));
        }

        return permutated_key56;
    }
    return bitarray();
}

bitarray keygen::PC2(const bitarray& key56)
{
    if (key56.size() == m_permutated_key_length)
    {
        int pc2[48] =
        {
            14  , 17    , 11    , 24    , 1     , 5     ,
                                                        
            3   , 28    , 15    , 6     , 21    , 10    ,
                                                        
            23  , 19    , 12    , 4     , 26    , 8     ,
                                                        
            16  , 7     , 27    , 20    , 13    , 2     ,
                                                        
            41  , 52    , 31    , 37    , 47    , 55    ,
                                                        
            30  , 40    , 51    , 45    , 33    , 48    ,
                                                        
            44  , 49    , 39    , 56    , 34    , 53    ,
                                                        
            46  , 42    , 50    , 36    , 29    , 32    
        };

        bitarray permuted_key48;

        for (size_t i = 0; i < m_round_key_length; ++i)
        {
            permuted_key48.push_back(key56.test(pc2[i]-1));
        }

        return permuted_key48;
    }
    return bitarray();
}

void keygen::split_permutated_key(const bitarray & permutated_key56, bitarray& left_block28, bitarray& right_block28)
{
    left_block28 = permutated_key56.sub_bitarray(0, 28);
    right_block28 = permutated_key56.sub_bitarray(28, 28);
}

void keygen::left_rotate_blocks(bitarray& left_block28, bitarray& right_block28, size_t iteration_number)
{
    if (!(iteration_number > 15))
    {
        int rotate_schedule[16] =
        {
            1,  1,  2,  2,  2,  2,  2,  2,  1,  2,  2,  2,  2,  2,  2,  1
        };

        left_block28.cyclic_rotate(rotate_schedule[iteration_number]);
        right_block28.cyclic_rotate(rotate_schedule[iteration_number]);
    }

}

bitarray keygen::join_blocks(const bitarray& left_block28, const bitarray& right_block28)
{
    bitarray joined_block;
   
    size_t left_block_size = left_block28.size();
    size_t right_block_size = right_block28.size();

    for (size_t i = 0; i < left_block_size; ++i)
    {
        joined_block.push_back(left_block28.test(i));
    }
    for (size_t i = 0; i < right_block_size; ++i)
    {
        joined_block.push_back(right_block28.test(i));
    }
    return joined_block;
}
