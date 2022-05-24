#include "set.hpp"
#include <set>
#include <vector>

template <class Key>
void	display_set(ns::set<Key>& lst)
{
	for (typename ns::set<Key>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout <<  "|" << *it << "|";
    std::cout << " size " << lst.size() << std::endl;
	std::cout << std::endl;
}

void test_set()
{
    //Constructor

    ns::set<int> defau;

    std::cout << "Constructor test\n";

    if (defau.empty())
        std::cout << "default constructor empty construction" << std::endl;
    
    std::vector<int> list;

    list.push_back(1); list.push_back(2);list.push_back(3);list.push_back(4);
    ns::set<int> creation(list.begin(), list.end());

    std::cout << "Constructor by iteration : ";
    display_set(creation);

    std::cout << "Constructor by copy : ";
    ns::set<int> creationcopy(creation);
    display_set(creationcopy);

    std::cout << "Egality operator :";
    defau = creationcopy;
    display_set(defau);

    std::cout << "display by reverse iterator\n";
    ns::set<int>::reverse_iterator ritb;
    ns::set<int>::const_reverse_iterator rite;

    ritb = defau.rbegin();
    rite = defau.rend();

    while (ritb != rite)
    {
        std::cout << "||" << *ritb << "||" <<std::endl;
        ritb++;
    }

    std::cout << "\nInsert test\n" << std::endl;

    ns::pair<ns::set<int>::iterator, bool> retp;
    ns::set<int>::iterator reti;
    ns::set<int> inserted;

    std::cout << "\n8 inserted\n"; retp = inserted.insert(8);
    display_set(inserted);
    std::cout << "returned " << "(" <<*(retp.first) << "-" <<retp.second << ")" << std::endl;
    std::cout << "\n5 inserted\n"; retp = inserted.insert(5);
    display_set(inserted);
    std::cout << "returned " << "(" <<*(retp.first) << "-" <<retp.second << ")" << std::endl;
    std::cout << "\n5 inserted\n"; retp = inserted.insert(5);
    display_set(inserted);
    std::cout << "returned " << "(" <<*(retp.first) << "-" <<retp.second << ")" << std::endl;
    std::cout << "\n3 inserted\n"; reti = inserted.insert(inserted.begin(), 3);
    display_set(inserted);
    std::cout << *reti << " got inserted" << std::endl;
    std::cout << "\n5 inserted\n"; reti = inserted.insert(inserted.begin()++, 5);
    display_set(inserted);
    std::cout << *reti << " got inserted" << std::endl;
    std::cout << "\n8 inserted\n"; reti = inserted.insert(inserted.end()-- , 8);
    display_set(inserted);
    if (reti == inserted.end())
        std::cout << "failed to insert" << std::endl;
    std::cout << "list 1-4 inserted\n"; inserted.insert(list.begin(), list.end());
    display_set(inserted);

    std::cout << "\nerase test\n" << std::endl;

    int erase_ret;
    std::cout << "begin erased\n";inserted.erase(inserted.begin()); display_set(inserted);
    std::cout << "end erased\n"; inserted.erase(--inserted.end()); display_set(inserted);
    std::cout << "third position erased\n"; inserted.erase(++(++(++inserted.begin()))); display_set(inserted);

    std::cout << "erase 5\n";
    erase_ret = inserted.erase(5); display_set(inserted);
    std::cout << erase_ret << " got erased" << std::endl;
    std::cout << "erase 3\n";
    erase_ret = inserted.erase(3); display_set(inserted);
    std::cout << erase_ret << " got erased" << std::endl;

    std::cout << "erase all\n";
    inserted.erase(inserted.begin(), inserted.end()); display_set(inserted);

    std::cout << "\nSwap test\n";

    ns::set<int> sw1; ns::set<int> sw2; ns::set<int> sw3;

    sw1.insert(1);sw1.insert(3);sw1.insert(5);sw1.insert(7);

    for (ns::set<int>::iterator it = sw1.begin() ; it != sw1.end() ; it++)
    {
        sw2.insert((*it) + 1);
    }
    std::cout << "sw1 : ";
    display_set(sw1);
    std::cout << "sw2 : ";
    display_set(sw2);

    sw1.swap(sw2);
    std::cout << "sw1 : ";
    display_set(sw1);
    std::cout << "sw2 : ";
    display_set(sw2);

    ns::swap(sw2, sw1);
    std::cout << "sw1 : ";
    display_set(sw1);
    std::cout << "sw2 : ";
    display_set(sw2);

    sw3.swap(sw1);
    std::cout << "sw1 : ";
    display_set(sw1);
    std::cout << "sw3 : ";
    display_set(sw3);

    sw3.clear();
    std::cout << "sw2 :";
    display_set(sw3);

    std::cout << "\nObserver test" << std::endl;

    if (sw3.key_comp()(3, 8) && sw3.value_comp()(10, 12))
        std::cout << "key comp and value comp correct\n"; 
    std::cout << "\nOperations test" << std::endl;

    ns::set<int>triple;
    ns::set<int>::iterator ret_found;
    //size_t  count_ret;

    for (int i = 0 ; i < 12 ; i++)
    {
        triple.insert(3 * i);
    }
    display_set(triple);

    ret_found = triple.find(18);
    if (ret_found != triple.end())
        std::cout << *ret_found << " got founded" << std::endl;
    else
        std::cout << "18 was not founded" << std::endl;
    
    ret_found = triple.find(42);
    if (ret_found != triple.end())
        std::cout << *ret_found << "got founded" << std::endl;
    else
        std::cout << "42 was not founded" << std::endl;

    std::cout << triple.count(30) << " is the count of 30" << std::endl;
    std::cout << triple.count(11) << " is the count of 11" << std::endl;
    std::cout << triple.count(33) << " is the count of 33" << std::endl;
    std::cout << triple.count(39) << " is the count of 39" << std::endl;

    std::cout << "\nBound test\n" << std::endl;

    ns::set<int>::iterator bond;

    bond = triple.lower_bound(12); std::cout << "Lower bound of 12 "<< *bond << std::endl;
    bond = triple.upper_bound(12); std::cout << "Upper bound of 12 " << *bond << std::endl;

    bond = triple.lower_bound(18); std::cout << "Lower bound of 18 "<< *bond << std::endl;
    bond = triple.upper_bound(18); std::cout << "Upper bound of 18 " << *bond << std::endl;

    bond = triple.lower_bound(33); std::cout << "Lower bound of 33 " << *bond << std::endl;
    bond = triple.upper_bound(33);
    if (triple.end() == bond)
    {
        std::cout << "Upper bound of 33 : end iterator" << std::endl;
    }

    std::cout << "\nComparaison operator\n";

    ns::set<char> dic1; dic1.insert('a'); dic1.insert('b'); dic1.insert('c');
    ns::set<char> dic2; dic2.insert('a'); dic2.insert('b'); dic2.insert('e');

    display_set(dic1);
    display_set(dic2);

    if (dic1 >= dic1)
        std::cout << "dic1 >= dic1\n";
    if (dic1 == dic1)
        std::cout << "dic1 == dic1\n";
    if (dic1 != dic1)
        std::cout << "dic1 != dic1\n";

    if (dic1 <= dic2)
        std::cout << "dic1 <= dic2\n";
    if (dic1 < dic2)
        std::cout << "dic1 < dic2\n";
    if (dic1 != dic2)
        std::cout << "dic1 != dic2\n";

    if (dic2 >= dic1)
        std::cout << "dic2 >= dic1\n";
    if (dic2 > dic1)
        std::cout << "dic2 > dic1\n";
    if (dic2 != dic1)
        std::cout << "dic2 != dic1\n";

}