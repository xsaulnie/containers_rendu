#ifndef IS_ITEG
#define IS_ITEG

namespace ft
{
template<class T>
struct is_integral
{
	const static bool value = false;

	typedef bool value_type;

};

template<>
struct ft::is_integral<int>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<char>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<wchar_t>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<signed char>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<short int>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<long int>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<long long int>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<unsigned char>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<unsigned short int>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<unsigned long int>
{
	const static bool value = true;

	typedef bool value_type;
};

template<>
struct ft::is_integral<unsigned long long int>
{
	const static bool value = true;

	typedef bool value_type;
};
}

#endif