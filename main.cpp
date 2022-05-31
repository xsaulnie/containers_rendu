#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "RBTree.hpp"
#include "set.hpp"
#include <string>
#include <vector>

void test_utils();
void test_vector();
void test_stack();
void test_RBtree();
void test_map();
void test_RBTree();
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
	print_title("TEST UTILS");
	test_utils();
	print_title("TEST VECTOR");
	test_vector();
	print_title("TEST STACK");
	test_stack();
	print_title("TEST MAP");
    //test_RBTree();
	test_map();
	//test_set();
	return (0);
}
