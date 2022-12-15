#include "des.hpp"

std::string des::process(std::string data_string, std::string key_string, DES_MODE mode)
{
	fit_string(data_string);
	fit_string(key_string);

	size_t amount_of_plain_text_blocks = static_cast<size_t>(std::ceil(data_string.size() / 8.0));

	bitarray data_bin = utils::string_to_bitarray(data_string);
	bitarray key_bin = utils::string_to_bitarray(key_string);


	std::vector<bitarray> round_keys = keygen::generate_round_keys(key_bin);

	if (mode == DES_MODE::DECRYPT)
	{
		std::reverse(round_keys.begin(), round_keys.end());
	}

	std::string result = "";
	for (size_t i = 0; i < amount_of_plain_text_blocks; ++i)
	{
		bitarray current_data_block64 = data_bin.sub_bitarray(i * 64, 64);

		bitarray permutated_current_data_block64 = IP1(current_data_block64);

		bitarray left_block32;
		bitarray right_block32;

		split_permutated_block(permutated_current_data_block64, left_block32, right_block32);

		for (size_t i = 0; i < m_amount_of_rounds; ++i)
		{
			bitarray f_result = f(right_block32, round_keys[i]);

			bitarray xor_result_f_left_block = f_result ^ left_block32;

			left_block32 = xor_result_f_left_block;

			if (i != 15)
			{
				std::swap(left_block32, right_block32);
			}
		}

		bitarray joined_blocks = join_blocks(left_block32, right_block32);

		bitarray permutated_joined_block64 = FP1(joined_blocks);

		result += utils::bitarray_to_string(permutated_joined_block64);
	}
	return result;
}

std::string des::EDE(std::string data_string, std::string key_string, std::string key_string2, DES_MODE mode)
{
	if (mode == DES_MODE::ENCRYPT)
	{
		std::string enc_pt_key = des::process(data_string, key_string);
		std::string dec_pt_key2 = des::process(enc_pt_key, key_string2, DES_MODE::DECRYPT);
		std::string enc_pt_key_finish = des::process(dec_pt_key2, key_string);

		return enc_pt_key_finish;
	}

	std::string dec_pt_key = des::process(data_string, key_string, DES_MODE::DECRYPT);
	std::string enc_pt_key2 = des::process(dec_pt_key, key_string2);
	std::string dec_pt_key_finish = des::process(enc_pt_key2, key_string, DES_MODE::DECRYPT);
	return dec_pt_key_finish;
}

void des::fit_string(std::string &data_string)
{
	while (data_string.size()*8 < m_block_size || data_string.size()*8 % m_block_size != 0)
	{
		data_string.push_back(' ');
	}
}

bitarray des::IP1(const bitarray& block64)
{
	if (block64.size() == m_block_size)
	{
		int ip1[64] = {

			58	,	50	,	42	,	34	,	26	,	18	,	10	,	2	,

			60	,	52	,	44	,	36	,	28	,	20	,	12	,	4	,

			62	,	54	,	46	,	38	,	30	,	22	,	14	,	6	,

			64	,	56	,	48	,	40	,	32	,	24	,	16	,	8	,

			57	,	49	,	41	,	33	,	25	,	17	,	 9	,	1	,

			59	,	51	,	43	,	35	,	27	,	19	,	11	,	3	,

			61	,	53	,	45	,	37	,	29	,	21	,	13	,	5	,

			63	,	55	,	47	,	39	,	31	,	23	,	15	,	7	,

		};

		bitarray permutated_block64;

		for (size_t i = 0; i < m_ip_block_size; ++i)
		{
			permutated_block64.push_back(block64.test(ip1[i] - 1));
		}

		return permutated_block64;

	}
	return bitarray();
}

bitarray des::FP1(const bitarray& block64)
{
	if (block64.size() == m_block_size)
	{
		int fp1[64] =
		{

			40	,	8	,	48	,	16	,	56	,	24	,	64	,	32	,	

			39	,	7	,	47	,	15	,	55	,	23	,	63	,	31	,	

			38	,	6	,	46	,	14	,	54	,	22	,	62	,	30	,	

			37	,	5	,	45	,	13	,	53	,	21	,	61	,	29	,	

			36	,	4	,	44	,	12	,	52	,	20	,	60	,	28	,	

			35	,	3	,	43	,	11	,	51	,	19	,	59	,	27	,	

			34	,	2	,	42	,	10	,	50	,	18	,	58	,	26	,	

			33	,	1	,	41	,	 9	,	49	,	17	,	57	,	25	,	

		};

		bitarray fpermutated_block64;

		for (size_t i = 0; i < m_block_size; ++i)
		{
			fpermutated_block64.push_back(block64.test(fp1[i] - 1));
		}
		return fpermutated_block64;
	}
	return bitarray();
}

bitarray des::f(const bitarray& right_block32, const bitarray& round_key48)
{
	bitarray expanded_right_block48 = E(right_block32);

	bitarray xor_reslut_block48 = expanded_right_block48 ^ round_key48;

	bitarray block_after_s_boxes32 = substitude(xor_reslut_block48);

	bitarray permutated_block32 = P(block_after_s_boxes32);

	return permutated_block32;
}

bitarray des::E(const bitarray& right_block32)
{
	if (right_block32.size() == 32)
	{
		int e[48] = {

			32	,	 1	,	 2	,	 3	,	 4	,	 5	,	

			 4	,	 5	,	 6	,	 7	,	 8	,	 9	,	

			 8	,	 9	,	10	,	11	,	12	,	13	,	

			12	,	13	,	14	,	15	,	16	,	17	,	

			16	,	17	,	18	,	19	,	20	,	21	,	

			20	,	21	,	22	,	23	,	24	,	25	,	

			24	,	25	,	26	,	27	,	28	,	29	,	

			28	,	29	,	30	,	31	,	32	,	 1	,	

		};
		bitarray expanded_block48;
		for (size_t i = 0; i < m_e_block_size; ++i)
		{
			expanded_block48.push_back(right_block32.test(e[i] - 1));
		}
		return expanded_block48;
	}
	return bitarray();
}

bitarray des::P(const bitarray& joined_blocks_d)
{
	if (joined_blocks_d.size() == 32)
	{
		int p[32]
		{
			16	,	 7	,	20	,	21	,

			29	,	12	,	28	,	17	,

			 1	,	15	,	23	,	26	,

			 5	,	18	,	31	,	10	,

			 2	,	 8	,	24	,	14	,

			32	,	27	,	 3	,	 9	,

			19	,	13	,	30	,	 6	,

			22	,	11	,	 4	,	25	,
		};

		bitarray permutated_joined_blocks_d32;

		for (size_t i = 0; i < 32; ++i)
		{
			permutated_joined_blocks_d32.push_back(joined_blocks_d.test(p[i] - 1));
		}
		return permutated_joined_blocks_d32;
	}
	return bitarray();
}

void des::split_permutated_block(const bitarray& permutated_block64, bitarray& left_block32, bitarray& right_block32)
{
	left_block32 = permutated_block64.sub_bitarray(0, 32);
	right_block32 = permutated_block64.sub_bitarray(32, 32);
}

bitarray des::join_blocks(const bitarray& left_block32, const bitarray& right_block32)
{
	if (left_block32.size() == right_block32.size() && right_block32.size() == 32)
	{
		bitarray joined_block;

		for (size_t i = 0; i < 32; ++i)
		{
			joined_block.push_back(left_block32.test(i));
		}
		for (size_t i = 0; i < 32; ++i)
		{
			joined_block.push_back(right_block32.test(i));
		}
		return joined_block;
	}
	return bitarray();
}

bitarray des::substitude(const bitarray& xor_result_block48)
{
	if (xor_result_block48.size() == 48)
	{
		int s_boxes[8][4][16] = {
		{
			14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
			0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
			4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
			15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
		},
		{
			15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
			3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
			0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
			13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
		},
		{
			10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
			13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
			13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
			1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
		},
		{
			7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
			13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
			10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
			3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
		},
		{
			2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
			14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
			4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
			11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
		},
		{
			12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
			10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
			9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
			4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
		},
		{
			4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
			13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
			1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
			6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
		},
		{
			13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
			1,15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
			7,11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
			2,1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
		}
		};
		
		std::string d_blocks = "";
		for (size_t i = 0; i < 8; ++i)
		{
			bitarray b_block = xor_result_block48.sub_bitarray(i * 6, 6);

			int raw = static_cast<int>(b_block.test(0)) * 2 + static_cast<int>(b_block.test(5));
			
			int column =	static_cast<int>(b_block.test(1)) * 8 +
							static_cast<int>(b_block.test(2)) * 4 +
							static_cast<int>(b_block.test(3)) * 2 +
							static_cast<int>(b_block.test(4));
			d_blocks += std::bitset<4>(s_boxes[i][raw][column]).to_string();
		}
		bitarray joined_d_blocks(d_blocks);

		return joined_d_blocks;
	}
	return bitarray();
}