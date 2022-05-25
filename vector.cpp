#include "vector.hpp"

template<typename T>
void displayit_vector(typename ns::vector<T> vec)
{
	typename ns::vector<T>::iterator it;
	for (it = vec.begin() ; it != vec.end() ; it++)
	{
		std::cout << "|" << *it << "|";
	}
	std::cout << std::endl;
}

template<typename T>
void display_reverseit(typename ns::vector<T> vec)
{
	typename ns::vector<T>::reverse_iterator it;
	for (it = vec.rbegin() ; it != vec.rend() ; it++)
	{
		std::cout << "/" << *it << "/";
	}
	std::cout << std::endl;
}

template<typename T>
void display_vector(typename ns::vector<T> &vec, const std::string &name = "")
{
	std::cout << name << " ";
	for (size_t i = 0 ; i < vec.size() ; i++)
	{
		std::cout << "[" << vec[i] << "]";
	}
	std::cout << " " << vec.size() << " " << vec.capacity();
	std::cout << std::endl;
}

void test_capacity(bool reserved)
{
	size_t cap;

	ns::vector<int> foo;
	cap = foo.capacity();
	if (reserved)
		foo.reserve(50);
	std::cout << "Capacity test 50 push_back ";
	if (reserved)
		std::cout << "reserved";
	std::cout << std::endl;
	for (int i = 0 ; i < 50 ; i++)
	{
		foo.push_back(i);
		if (cap != foo.capacity())
		{
			cap = foo.capacity();
			std::cout << "capacity changed: " << cap << std::endl;
		}
	}
}

void test_vector()
{
	std::cout << "\nTEST CONSTRUCTORS\n" << std::endl;
	std::cout << "Default constructor" << std::endl;
	ns::vector<int> first;
	display_vector(first, "first");
	first.push_back(12);
	display_vector(first, "push_back 1");
	first.push_back(28);
	display_vector(first, "push_back 2");
	std::cout << "first ";
	displayit_vector(first);
	display_vector(first, "first");
	std::cout << "n elements constructor" << std::endl;
	ns::vector<int> second(10, 8);
	second.push_back(-3);
	std::cout << "second ";
	displayit_vector(second);
	std::cout << "Iterator constructor" << std::endl;
	ns::vector<int> third(first.begin(), first.end());
	third.push_back(3);
	display_vector(third, "third");
	std::cout << "copy constructor" << std::endl;
	ns::vector<int> cpy(third);
	
	if (cpy == third)
		std::cout << "cpy and third are equal" << std::endl;
	
	display_vector(cpy, "cpy");
	std::cout << std::endl << "Affectation operator" << std::endl;

	ns::vector<int> b(20, 3);
	ns::vector<int> a(10, 8);

	b.push_back(10);
	display_vector(b, "b");
	display_vector(a, "a");
	a = b;
	display_vector(a, "a = b");
	std::cout << "a = b Size and capacity : " << a.size() << " " << a.capacity() << std::endl;

	std::cout << std::endl << "\nREVERSE ITERATOR TEST\n" << std::endl;
	ns::vector<int> order;
	order.push_back(0); order.push_back(1); order.push_back(2); order.push_back(3); order.push_back(4);
	display_vector(order, "order");
	std::cout << "order ";
	display_reverseit(order);

	std::cout << "order through const iterator : ";
	ns::vector<int>::const_iterator cit;

	cit = order.begin();

	while (cit != order.end())
	{
		std::cout << "|" << *cit << "|";
		cit++;
	}
	std::cout << std::endl;
	std::cout << "\nACCESS OPERATOR TEST\n" << std::endl;
	ns::vector<int> accessible;
	accessible.push_back(2);accessible.push_back(4);accessible.push_back(6);accessible.push_back(8);accessible.push_back(10);accessible.push_back(12);
	std::cout << "accessible display with [] : ";
	for (int i = 0 ; i < accessible.size() ; i++)
	{
		std::cout << "-" << accessible[i] << "-";
	}
	std::cout << "\nadding 1 to accessible :     ";
	for (int i = 0 ; i < accessible.size() ; i++)
	{
		accessible[i]++;
		std::cout << "-" << accessible[i] << "-";
	}
	std::cout << std::endl;
	std::cout << "front is : " << accessible.front() << " back is " << accessible.back() << " at 2 is " << accessible.at(2) << std::endl;

	std::cout << "\nSIZE AND RESIZE TEST\n" << std::endl;
	ns::vector<double> big;
	std::vector<double> bigc;
	std::cout << "Maximum size " << big.max_size() << std::endl;

	ns::vector<int> muta(10, 0);
	display_vector(muta, "muta");
	muta.resize(15, 1);
	std::cout << "resize muta to 15" << std::endl;
	display_vector(muta, "muta");

	ns::vector<int> muto(10, 0);
	display_vector(muto, "muto");
	muto.resize(5, 1);
	std::cout << "resize muto to 5 with value 1" << std::endl;
	display_vector(muto, "muto");
	muto.resize(7, 2);
	std::cout << "resize muto to 7 with value 2" << std::endl;
	display_vector(muto, "muto");
	muto.resize(0);
	std::cout << "resize muto to 0 " << std::endl;
	display_vector(muto, "muto");
	if (muto.empty())
		std::cout << "muto is empty" << std::endl;

	ns::vector<int> place(12);
	place.reserve(15);

	display_vector(place, "place reserved 15");
	place.reserve(100);
	display_vector(place, "place reserved 100");

	std::cout << std::endl << "Capazity test" << std::endl;
	test_capacity(false);
	std::cout << "capacity test with 50 reserved" << std::endl;
	test_capacity(true);

	std::cout << "\nASSIGNED TEST\n\n";
	ns::vector<int> assigned;

	assigned.assign(10, 3);
	display_vector(assigned, "10 3 assigned");
	assigned.assign(6, 1);
	display_vector(assigned, "6 1 assigned");
	assigned.assign(muta.begin(), muta.end());
	display_vector(assigned, "assigned as muta");
	assigned.assign(order.begin(), order.end());
	display_vector(assigned, "assigned as order");
	assigned.pop_back();
	assigned.pop_back();
	display_vector(assigned, "assigned double pop_back");

	std::cout << "\nERASE TEST\n";

	ns::vector<int> erased;
	order.push_back(5);order.push_back(6);order.push_back(7);order.push_back(8);order.push_back(9);
	erased.assign(order.begin(), order.end());

	std::cout << std::endl;
	display_vector(erased, "erased");
	erased.erase(erased.begin() + 5);
	display_vector(erased, "5 erased");
	erased.erase(erased.end() - 1);
	display_vector(erased, "last erased");
	erased.erase(erased.begin());
	display_vector(erased, "first erased");

	erased.assign(order.begin(), order.end());
	erased.erase(erased.end() - 2, erased.end());
	display_vector(erased, "last 2 erased");

	erased.assign(order.begin(), order.end());
	erased.erase(erased.begin(), erased.begin() + 2);
	display_vector(erased, "first 2 erased");

	erased.assign(order.begin(), order.end());
	erased.erase(erased.begin() + 2, erased.end() - 2);
	display_vector(erased, "last 2, first 2, not  erased");

	std::cout << "\nINSER TEST\n"; 

	std::cout << std::endl;
	ns::vector<int> inserted;
	inserted.assign(order.begin(), order.end());
	display_vector(inserted, "test");
	inserted.insert(inserted.begin() + 2, 0);
	display_vector(inserted, "0 inserted at pos 2");
	inserted.insert(inserted.end() - 1, 0);
	display_vector(inserted, "0 inserted before last");
	inserted.insert(inserted.begin(), -1);
	display_vector(inserted, "-1 inserted at begining");

	ns::vector<int> minserted;

	std::cout << "Multiple insertion\n";
	minserted.assign(order.begin(), order.end());
	minserted.insert(minserted.begin() + 2, 5, 0);
	display_vector(minserted, "5 0 inserted at pos 2");

	minserted.insert(minserted.begin() + 8, 3, 7);
	display_vector(minserted, "3 7 inserted at pos 8");
	minserted.insert(minserted.end(), 2, 10);
	display_vector(minserted, "2 10 inserted last pos");
	minserted.insert(minserted.end() - 2, 10, -2);
	display_vector(minserted, "10 -2 inserted before the 10");


	std::cout<< "Iterator insetion\n";

	ns::vector<int> iterinserted(8);
	display_vector(iterinserted, "vector of 8 0");
	ns::vector<int> little1;
	little1.push_back(1); little1.push_back(2); little1.push_back(3);
	iterinserted.insert(iterinserted.begin() + 2, little1.begin(), little1.end());
	display_vector(iterinserted, "little at pos 2");

	iterinserted.insert(iterinserted.end() - 1, little1.begin(), little1.end());
	display_vector(iterinserted, "little before the end");

	ns::vector<int> lit;
	lit.push_back(10); lit.push_back(11);
	iterinserted.insert(iterinserted.end(), lit.begin(), lit.end());
	display_vector(iterinserted, "10 11 at the end");
	iterinserted.insert(iterinserted.begin() + 5, little1.begin(), little1.end());
	display_vector(iterinserted, "123 pos 5");

	std::cout << "\nSWAP TEST\n";

	ns::vector<int> sw1; ns::vector<int> sw2; ns::vector<int> sw3;

	sw1.push_back(7); sw1.push_back(8); sw1.push_back(9); sw1.push_back(10);

	for (ns::vector<int>::const_iterator it = sw1.begin() ; it != sw1.end() ; it++)
	{
		sw2.insert(sw2.end(), 2 * (*it) - 6);
	}

	display_vector(sw1, "sw1 : ");
	display_vector(sw2, "sw2 : ");
	display_vector(sw3, "sw3 : ");

	sw1.swap(sw2); std::cout << "swap 1 with 2 member fonction\n"; 
	display_vector(sw1, "sw1 : ");
	display_vector(sw2, "sw2 : ");
	ns::swap(sw2, sw1); std::cout << "swap 2 with 1 externe fonction\n";
	display_vector(sw1, "sw1 : ");
	display_vector(sw2, "sw2 : ");

	sw3.swap(sw1); std::cout << "swap 3 with 1 member fonction\n";
	display_vector(sw1, "sw1 : ");
	display_vector(sw3, "sw3 : ");

	sw3.clear(); std::cout << "clear tested on 3\n";

	display_vector(sw1, "sw1 : ");
	display_vector(sw2, "sw2 : ");
	display_vector(sw3, "sw3 : ");

	std::cout << "\nCOMPARAISON OPERATOR TEST\n";

	ns::vector<char> one;
	ns::vector<char> two;
	ns::vector<char> the;

	one.push_back('a'); one.push_back('e');
	ns::vector<char> cone(one);
	two.push_back('a'); two.push_back('e'); two.push_back('b');
	the.push_back('a'), the.push_back('r');

	if (one == one)
		std::cout << "one == one\n";
	if (one >= one)
		std::cout << "one >= one\n";
	if (one != one)
		std::cout << "one != one\n";
	if (one <= one)
		std::cout << "one <= one\n";
	if (one < one)
		std::cout << "one < one\n";
	if (one > one)
		std::cout << "one > one\n";

	if (one == two)
		std::cout << "one == two\n";
	if (one >= two)
		std::cout << "one >= two\n";
	if (one != two)
		std::cout << "one != two\n";
	if (one <= two)
		std::cout << "one <= two\n";
	if (one < two)
		std::cout << "one < two\n";
	if (one > one)
		std::cout << "one > two\n";

	if (one == cone)
		std::cout << "one == cone\n";
	if (one >= cone)
		std::cout << "one >= cone\n";
	if (one != cone)
		std::cout << "one != cone\n";
	if (one <= cone)
		std::cout << "one <= cone\n";
	if (one < cone)
		std::cout << "one < cone\n";
	if (one > cone)
		std::cout << "one > cone\n";
	
	if (one == the)
		std::cout << "one == the\n";
	if (one >= the)
		std::cout << "one >= the\n";
	if (one != the)
		std::cout << "one != the\n";
	if (one <= the)
		std::cout << "one <= the\n";
	if (one < the)
		std::cout << "one < the\n";
	if (one > the)
		std::cout << "one > the\n";
	

	return ;
}