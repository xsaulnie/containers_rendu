#include "set.hpp"
#include <string>
#include <vector>

void test_set();

void print_title(std::string msg)
{
	int dec;

	dec = (54 - msg.length() ) / 2;
	std::cout << "\n\n\n------------------------------------------------------\n";
	std::cout << "|";
	for (int i = 0 ; i < dec; i++)
		std::cout << " ";
	std::cout << msg;
	for (size_t i = 0 ; i < 54 - (msg.length() + dec) - 2; i++)
		std::cout << " ";
	std::cout << "|\n";
	std::cout << "------------------------------------------------------\n\n\n";

}

int main()
{
	print_title("TEST SET");
	test_set();
	return (0);
}
