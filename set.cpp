#include "set.hpp"
#include <set>

void test_set()
{
    std::vector<int> list;

    list.push_back(1); list.push_back(2);list.push_back(3);list.push_back(4);
    ns::set<int> creation(list.begin(), list.end());

    ns::set<int>::iterator itest;

    itest = creation.begin();

    while (itest != creation.end())
    {
        std::cout << *itest << std::endl;
        itest++;
    }
}