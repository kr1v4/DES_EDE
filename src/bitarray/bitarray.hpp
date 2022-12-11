#ifndef BITARRAY_HPP
#define BITARRAY_HPP

#include <iostream>
#include <vector>
#include <string>


class bitarray
{
public:

	bitarray();
	~bitarray();
	bitarray(const std::string& decimal_string);
	bitarray(bitarray&& other) noexcept;
	bitarray(const bitarray& other);
	void from_decimal_string(const std::string& decimal_string);

	void push_back(bool bit);
	void empty();
	void set(size_t pos, bool bit);
	bool test(size_t pos) const;
	void cyclic_rotate(size_t n, bool to_left = true);
	bitarray sub_bitarray(size_t from_pos, size_t n) const;

	std::string to_string() const;

	size_t size() const;
	size_t capacity() const;

public:
	bitarray& operator =(bitarray&& other) noexcept;
	bitarray& operator = (const bitarray& other);
	friend std::ostream& operator<<(std::ostream& os, const bitarray& _bitarray);
	friend bitarray operator^(const bitarray& first_bitarray, const bitarray& second_bitarray);

private:
	void free_mem();
	void allocate_mem(size_t size);
	void increase_capacity();

private:
	bool* p_array = nullptr;
	size_t m_array_size;
	size_t m_array_capacity;
};


#endif // !BITARRAY_HPP