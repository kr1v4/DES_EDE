#include "bitarray.hpp"
//#define LOG

bitarray::bitarray() :m_array_capacity(256), m_array_size(0)
{
#ifdef LOG
	std::cout << "ctor - " << this << "\n";
#endif // LOG
	allocate_mem(m_array_capacity);
}

bitarray::~bitarray()
{
#ifdef LOG
	std::cout << "dtor - " << this << "\n";
#endif // LOG
	free_mem();
}

bitarray::bitarray(const std::string& decimal_string) :m_array_capacity(256), m_array_size(0)
{
#ifdef LOG
	std::cout << "string ctor - " << this << "\n";
#endif // LOG
	allocate_mem(m_array_capacity);
	size_t dec_str_lenght = decimal_string.length();
	m_array_size = dec_str_lenght;

	bool need_allocate = false;
	while (m_array_capacity <= m_array_size)
	{
		increase_capacity();
		need_allocate = true;
	}
	if (need_allocate)
	{
		free_mem();
		allocate_mem(m_array_capacity);
		for (size_t i = 0; i < m_array_size; ++i)
		{
			p_array[i] = decimal_string[i] != '0';
		}
		return;
	}
	empty();
	for (size_t i = 0; i < m_array_size; ++i)
	{
		p_array[i] = decimal_string[i] != '0';
	}
}

bitarray::bitarray(bitarray&& other) noexcept

	:m_array_capacity(other.m_array_capacity),
	m_array_size(other.m_array_size),
	p_array(other.p_array)
{
#ifdef LOG
	std::cout << "move ctor - " << this << "\n";
#endif // LOG
	other.p_array = nullptr;
	other.m_array_capacity = 0;
	other.m_array_size = 0;

}

bitarray::bitarray(const bitarray& other)
{
#ifdef LOG
	std::cout << "copy ctor - " << this << "\n";
#endif // LOG
	m_array_size = other.m_array_size;
	m_array_capacity = other.m_array_capacity;
	allocate_mem(m_array_capacity);

	for (size_t i = 0; i < m_array_size; ++i)
	{
		set(i, other.test(i));
	}
}

void bitarray::from_decimal_string(const std::string& decimal_string)
{
	size_t dec_str_lenght = decimal_string.length();
	m_array_size = dec_str_lenght;

	bool need_allocate = false;
	while (m_array_capacity <= m_array_size)
	{
		increase_capacity();
		need_allocate = true;
	}
	if (need_allocate)
	{
		free_mem();
		allocate_mem(m_array_capacity);
		for (size_t i = 0; i < m_array_size; ++i)
		{
			p_array[i] = decimal_string[i] != '0';
		}
		return;
	}
	empty();
	for (size_t i = 0; i < m_array_size; ++i)
	{
		p_array[i] = decimal_string[i] != '0';
	}
}

void bitarray::push_back(bool bit)
{
	++m_array_size;
	int reallocate_border = static_cast<int>(std::ceil(m_array_capacity * 0.7));
	bool need_reallocate_mem = false;
	if (m_array_size >= reallocate_border)
	{
		increase_capacity();
		need_reallocate_mem = true;
	}
	if (need_reallocate_mem)
	{
		bool* copy = new bool[m_array_size - 1];
		for (size_t i = 0; i < m_array_size - 1; ++i)
		{
			copy[i] = p_array[i];
		}
		free_mem();
		allocate_mem(m_array_capacity);
		for (size_t i = 0; i < m_array_size - 1; ++i)
		{
			p_array[i] = copy[i];
		}
		p_array[m_array_size - 1] = bit;
		delete[] copy;
		return;
	}
	p_array[m_array_size - 1] = bit;
}

void bitarray::empty()
{
	std::fill_n(p_array, m_array_capacity, false);
}

void bitarray::set(size_t pos, bool bit)
{
	if (!(pos >= m_array_size))
	{
		p_array[pos] = bit;
	}
}

bool bitarray::test(size_t pos) const
{
	if (!(pos >= m_array_size))
	{
		return p_array[pos];
	}
	return false;
}

void bitarray::cyclic_rotate(size_t n, bool to_left)
{
	if (to_left)
	{
		for (size_t i = 0; i < n; ++i)
		{
			bool last_bit = p_array[0];

			for (size_t j = 0; j < m_array_size - 1; ++j)
			{
				p_array[j] = p_array[j + 1];
			}
			p_array[m_array_size - 1] = last_bit;
		}
		return;
	}
	for (size_t i = 0; i < n; ++i)
	{
		bool first_bit = p_array[m_array_size - 1];
		for (size_t j = m_array_size - 1; j > 0; --j)
		{
			p_array[j] = p_array[j - 1];
		}
		p_array[0] = first_bit;
	}
}

bitarray bitarray::sub_bitarray(size_t from_pos, size_t n)
{
	if (from_pos <= m_array_size && from_pos + n <= m_array_size)
	{
		bitarray sub_bitarray;

		for (size_t i = from_pos; i < from_pos + n; ++i)
		{
			sub_bitarray.push_back(test(i));
		}
		return sub_bitarray;
	}
	return bitarray();
}

std::string bitarray::to_string() const
{
	std::string bin_string;

	for (size_t i = 0; i < m_array_size; ++i)
	{
		p_array[i] ? bin_string.push_back('1') : bin_string.push_back('0');
	}
	return bin_string;
}

size_t bitarray::size() const
{
	return m_array_size;
}

size_t bitarray::capacity() const
{
	return m_array_capacity;
}

bitarray& bitarray::operator=(bitarray&& other) noexcept
{
#ifdef LOG
	std::cout << "move op= - " << this << "\n";
#endif // LOG
	if (&other == this)
	{
		return *this;
	}

	free_mem();
	m_array_size = other.m_array_size;
	m_array_capacity = other.m_array_capacity;
	p_array = other.p_array;

	other.p_array = nullptr;
	other.m_array_size = 0;
	other.m_array_capacity = 0;

	return *this;
}

bitarray& bitarray::operator=(const bitarray& other)
{
#ifdef LOG
	std::cout << "op= - " << this << "\n";
#endif // LOG
	if (this == &other)
	{
		return *this;
	}
	m_array_size = other.m_array_size;
	m_array_capacity = other.m_array_capacity;
	free_mem();
	allocate_mem(m_array_capacity);

	for (size_t i = 0; i < m_array_size; ++i)
	{
		set(i, other.test(i));
	}
	return	*this;
}

void bitarray::free_mem()
{
#ifdef LOG
	std::cout << "\tfree - " << sizeof(bool) * m_array_capacity << "\n\n";
#endif // LOG
	delete[] p_array;
}

void bitarray::allocate_mem(size_t size)
{
#ifdef LOG
	std::cout << "\tallocate - " << sizeof(bool) * size << " mem\n\n";
#endif
	p_array = new bool[size];
	empty();
}

void bitarray::increase_capacity()
{
	m_array_capacity *= 2;
}

std::ostream& operator<<(std::ostream& os, const bitarray& _bitarray)
{
	return os << _bitarray.to_string();
}

bitarray operator^(const bitarray& first_bitarray, const bitarray& second_bitarray)
{
	if (first_bitarray.size() == second_bitarray.size())
	{
		size_t bitarrays_size = first_bitarray.size();
		bitarray xored_bitarray;

		for (size_t i = 0; i < bitarrays_size; ++i)
		{
			bool result = first_bitarray.test(i) ^ second_bitarray.test(i);
			xored_bitarray.push_back(result);
		}
		return xored_bitarray;
	}
	return bitarray();
}