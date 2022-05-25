#include "map.hpp"
#include <string>
#include <map>


template<class T, class V>
void dispriter_map(ns::map<T, V> &m)
{
	typename ns::map<T, V>::reverse_iterator theend = m.rend();

	std::cout << "------------------------------" << std::endl;
	for (typename ns::map<T, V>::reverse_iterator it = m.rbegin(); it != theend ; it++)
	{
		std::cout << "(" << it->first << ")" << " " << "(" << it->second << ")" <<std::endl;
	}
	std::cout << "------------------------------" << std::endl;
}

/*
template<class Key, class T, class Compare>
void disp_m(ns::map<Key, T, Compare> &m)
{
	(void)m;
	//m.disp_map(m);
}
*/
template<class Key, class T, class Compare>
void display_map(ns::map<Key, T, Compare> &m)
{
	typename ns::map<Key, T, Compare>::iterator it;

	it = m.begin();
	while (it != m.end())
	{
		std::cout << "(" << it->first << "-" << it->second << ")";
		it++;
	}
	std::cout << " s: "<< m.size() << std::endl;
}

template<class Key, class T, class Compare>
void display_mapm(ns::map<Key, T, Compare> &m, const std::string &msg)
{
	std::cout << msg << " ";
	display_map(m);
}


template<class Key, class T, class Compare>
void compmap(ns::map<Key, T, Compare> &m1, ns::map<Key, T, Compare> &m2, const std::string &n1, const std::string &n2)
{
	if (m1 == m2)
		std::cout << n1 << " == " << n2 << std::endl;
	if (m1 != m2)
		std::cout << n1 << " != " << n2 << std::endl;
	if (m1 > m2)
		std::cout << n1 << " > " << n2 << std::endl;
	if (m1 >= m2)
		std::cout << n1 << " >= " << n2 << std::endl;
	if (m1 < m2)
		std::cout << n1 << " < " << n2 << std::endl;
	if (m1 <= m2)
		std::cout << n1 << " <= " << n2 << std::endl;
	std::cout << std::endl;
}

void test_map()
{
	ns::map<int, int> test;
	test.insert(ns::pair<int, int>(42, 8));
	test.erase(42);
	if (test.empty())
		std::cout << "test is empty" << std::endl;

	ns::pair<ns::map<int, int>::iterator, bool> pairtest;

	std::cout << "SIMPLE INSERT TEST \n";
	pairtest = test.insert(ns::pair<int, int>(8, 8));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(12, 12));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(13, 13));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(20, 20));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(28, 28));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(24, 24));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(30, 30));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(1, 1));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(11,11));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(6, 6));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(50, 50));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;
	pairtest = test.insert(ns::pair<int, int>(50, 52));	display_map(test); std::cout << "ret : "<< (pairtest.first)->first << " " << pairtest.second << std::endl;

	std::cout << "print with reverse iteration" << std::endl;

	dispriter_map(test);

	std::cout << "CONSTRUCTOR TEST" << std::endl;;

	ns::map<int, int> empty;
	std::cout << "Default constructor\n";
	if (empty.empty())
		display_map(empty);
	std::cout << "range constructor\n";
	ns::map<int, int>rantest(test.begin(), test.end());
	display_mapm(rantest, "rantest constructed over test : ");
	std::cout << "copy constructor\n";
	ns::map<int, int>cpyrantest(rantest);
	display_mapm(cpyrantest, "cpyrantest constructed by copy of rantest : ");

	ns::map<int, int> affectmap;

	std::cout << "affectation operator\n";
	affectmap = test;
	display_mapm(affectmap, "new_map = test : ");

	std::cout << "BRACKET OPERATOR TEST" << std::endl;

	ns::map<int, int> bra;
	bra.insert(ns::pair<int, char>(1, 1));
	display_map(bra);
	bra[6]; 
	display_map(bra);
	bra[12] = 3;
	display_map(bra);
	std::cout << "display through bracket" << std::endl;
	for (ns::map<int, int>::const_iterator it = bra.begin() ; it != bra.end() ; it++)
	{
		std::cout << "-" << bra[it->first] << "-";
	}
	bra[1] = bra[1] * 2 + 1;
	bra[6] = bra[6] * 2 + 1;
	bra[12] = bra[12] * 2 + 1;
	std::cout << "multiply by 2 adding one" << std::endl;

	for (ns::map<int, int>::const_iterator it = bra.begin() ; it != bra.end() ; it++)
	{
		std::cout << "-" << bra[it->first] << "-";
	}

	std::cout << "\nINSERT TEST\n";

	std::cout << "Insert with hint\n";
	ns::map<int, int> ins1;
	ns::map<int, int> ins2;

	ns::map<int, int>::iterator ret_ins;
	ns::map<int, int>::const_iterator cbins1 = ins1.begin();
	ns::map<int, int>::const_iterator cbins2 = ins2.end();


	std::cout << "try to insert 16 at 8" << std::endl;
	ret_ins = ins1.insert(cbins1, ns::pair<int, int>(8, 16)); display_mapm(ins1, "ins1 : "); std::cout << "ret : " << ret_ins->first << " " << ret_ins->second << std::endl;
	
	std::cout << "try to insert 9 at 3" << std::endl;
	ret_ins = ins2.insert(cbins2, ns::pair<int, int>(3, 9)); display_mapm(ins2, "ins2 : "); std::cout << "ret : " << ret_ins->first << " " << ret_ins->second << std::endl;

	std::cout << "try to insert 8 at 4" << std::endl;
	ret_ins = ins1.insert(ins1.begin(), ns::pair<int, int>(4, 8)); display_mapm(ins1, "ins1 : "); std::cout << "ret : " << ret_ins->first << " " << ret_ins->second << std::endl;
	
	std::cout << "try to insert 22 at 11" << std::endl;
	ret_ins = ins2.insert(ins2.end(), ns::pair<int, int>(11, 22)); display_mapm(ins2, "ins2 : "); std::cout << "ret : " << ret_ins->first << " " << ret_ins->second << std::endl;
	
	std::cout << "try to insert 12 at 6" << std::endl;
	ret_ins = ins1.insert(++ins1.begin(), ns::pair<int, int>(6, 12)); display_mapm(ins1, "ins1 : "); std::cout << "ret : " << ret_ins->first << " " << ret_ins->second << std::endl;
	std::cout << "try to insert 10 at 5" << std::endl;
	ret_ins = ins2.insert(--ins2.end(), ns::pair<int, int>(5, 10)); display_mapm(ins1, "ins2 : "); std::cout << "ret : " << ret_ins->first << " " << ret_ins->second << std::endl;
	std::cout << "try to insert 8 at 8" << std::endl;
	ret_ins = ins1.insert(cbins1, ns::pair<int, int>(8, 8)); display_mapm(ins1, "ins1 : "); std::cout << "ret : " << ret_ins->first << " " << ret_ins->second << std::endl;
	std::cout << "try to insert 56 at 11" << std::endl;
	ret_ins = ins2.insert(ins2.end(), ns::pair<int, int>(11, 56)); display_mapm(ins2, "ins2 : "); std::cout << "ret : " << ret_ins->first << " " << ret_ins->second << std::endl;
	
	std::cout <<"Insert a range\n";

	std::cout << "insert ins2 on ins1\n";  
	ins1.insert(ins2.begin(), ins2.end());
	display_mapm(ins1, "ins1 : ");
	std::cout << "insert ins1 on ins2\n";
	ins2.insert(ins1.begin(), ins1.end());
	display_mapm(ins2, "ins2 : ");
	if (ins1 == ins2)
		std::cout << "insertion completed" << std::endl;

	std::cout << "\nERASE TEST\n";

	size_t ret_erase;

	std::cout << "erasing iterator\n" << std::endl;
	std::cout << "erase ins first position ";
	ins1.erase(ins1.begin()); display_mapm(ins1, "ins1 : ");

	std::cout << "erase ins last position ";
	ins1.erase(--ins1.end()); display_mapm(ins1, "ins1 : ");

	std::cout << "erase ins second position ";
	ins1.erase(++ins1.begin()); display_mapm(ins1, "ins1 : ");

	std::cout << "erase ins before last position ";
	ins1.erase(--(--ins1.end())); display_mapm(ins1, "ins1 : ");

	std::cout << "erasing key\n" << std::endl;

	std::cout << "try to erase 3\n"; 
	ret_erase = ins2.erase(3); display_mapm(ins2, "ins2 : "); std::cout << "ret : " << ret_erase << std::endl;
	std::cout << "try to erase 11\n"; 
	ret_erase = ins2.erase(11); display_mapm(ins2, "ins2 : "); std::cout << "ret : " << ret_erase << std::endl;
	std::cout << "try to erase 6\n"; 
	ret_erase = ins2.erase(6); display_mapm(ins2, "ins2 : "); std::cout << "ret : " << ret_erase << std::endl;
	std::cout << "try to erase 100\n"; 
	ret_erase = ins2.erase(100); display_mapm(ins2, "ins2 : "); std::cout << "ret : " << ret_erase << std::endl;

	std::cout << "erasing range\n";

	std::cout << "Erasing all exepted first\n";
	ins1.erase(++ins1.begin(), ins1.end()); display_mapm(ins1, "ins1 : ");
	std::cout << "Erasing all exepted last\n"; display_mapm(ins2, "ins2 : ");
	ins2.erase(ins2.begin(), --ins2.end());

	std::cout << "\nSWAP TEST\n";

	ns::map<int, char> sw1;
	ns::map<int, char> sw2;
	ns::map<int, char> sw3;

	sw1.insert(ns::pair<int, char>(8, 'h'));
	sw1.insert(ns::pair<int, char>(19, 's'));

	sw2.insert(ns::pair<int, char>(13, 'm'));
	sw2.insert(ns::pair<int, char>(11, 'k'));

	display_mapm(sw1, "sw1 : ");
	display_mapm(sw2, "sw2 : ");
	display_mapm(sw3, "sw3 : ");

	std::cout << "sw1 swap with sw2\n";
	sw1.swap(sw2);
	display_mapm(sw1, "sw1 : ");
	display_mapm(sw2, "sw2 : ");

	std::cout << "sw2 swap with sw3\n";
	ns::swap(sw2, sw3);
	display_mapm(sw2, "sw2 : ");
	display_mapm(sw3, "sw3 : ");

	std::cout << "sw3 swap with sw1\n";
	sw3.swap(sw1);
	display_mapm(sw1, "sw1 : ");
	display_mapm(sw2, "sw2 : ");
	display_mapm(sw3, "sw3 : ");

	std::cout << "All clear" << std::endl;
	sw1.clear();
	sw3.clear();
	display_mapm(sw1, "sw1 : ");
	display_mapm(sw2, "sw2 : ");
	display_mapm(sw3, "sw3 : ");

	std::cout << "\nFIND AND COUNT TEST\n";

	size_t ret_c;

	ns::map<int, std::string> prime;

	ns::map<int, std::string>::iterator ret_f;

	prime.insert(ns::pair<int, std::string>(2, "two"));
	prime.insert(ns::pair<int, std::string>(3, "three"));
	prime.insert(ns::pair<int, std::string>(5, "five"));
	prime.insert(ns::pair<int, std::string>(7, "seven"));
	prime.insert(ns::pair<int, std::string>(11, "eleven"));

	display_mapm(prime, "short list of prime : ");

	ret_f = prime.find(2);
	ret_c = prime.count(2);
	if (ret_f == prime.end())
		std::cout << "prime not found " << ret_c << " counted\n";
	else
		std::cout << ret_f->second << " is prime " << ret_c << " counted\n";

	ret_f = prime.find(11);
	ret_c = prime.count(11);
	if (ret_f == prime.end())
		std::cout << "prime not found " << ret_c << " counted\n";
	else
		std::cout << ret_f->second << " is prime " << ret_c << " counted\n";

	ret_f = prime.find(28);
	ret_c = prime.count(28);
	if (ret_f == prime.end())
		std::cout << "prime not found " << ret_c << " counted\n";
	else
		std::cout << ret_f->second << " is prime " << ret_c << " counted\n";

	std::cout << "\nBOUND TEST\n";

	ns::map<int, int> map;

	map.insert(ns::pair<int, int>(30, 30));
	map.insert(ns::pair<int, int>(12, 12));
	map.insert(ns::pair<int, int>(16, 16));
	map.insert(ns::pair<int, int>(50, 50));

	display_mapm(map, "map to test bounds :");

	std::cout << "Lower bound of 15 : " << (map.lower_bound(15))->first << std::endl;
	std::cout << "Lower bound of 30 : " << (map.lower_bound(30))->first << std::endl;

	std::cout << "Upper bound of 15 : " << (map.upper_bound(15))->first << std::endl;
	std::cout << "Upper bound of 30 : " << (map.upper_bound(30))->first << std::endl;

	if (map.upper_bound(100) == map.end())
		std::cout << "Upper bound of 100 return end iterator" << std::endl;
	if (map.upper_bound(100) == map.end())
		std::cout << "Lower bound of 100 return end iterator" << std::endl;

	ns::pair<ns::map<int, int>::iterator, ns::map<int, int>::iterator> prange;

	prange = map.equal_range(28);
	std::cout << "equal range 28 : "<< (prange.first)->first << "-" <<(prange.second)->first << std::endl;


	ns::map<int, int> cmp1;
	ns::map<int, int> cmp2;
	ns::map<int, int> cmp3;
	ns::map<int, int> cmp4;

	cmp1.insert(ns::pair<int, int>(1, 8));
	cmp2.insert(ns::pair<int, int>(1, 12));
	cmp3.insert(ns::pair<int, int>(-3, 1));
	cmp4.insert(ns::pair<int, int>(1, 8)); 	cmp4.insert(ns::pair<int, int>(7, 9));
	display_mapm(cmp1, "cmp1 : ");
	display_mapm(cmp2, "cmp2 : ");
	display_mapm(cmp3, "cmp3 : ");
	std::cout << std::endl;

	compmap(cmp1, cmp1, "cmp1", "cmp1");
	compmap(cmp1, cmp2, "cmp1", "cmp2");
	compmap(cmp1, cmp3, "cmp1", "cmp3");

	cmp1.insert(ns::pair<int, int>(7, 6));
	display_mapm(cmp1, "cmp1 : ");
	display_mapm(cmp4, "cmp4 : ");
	std::cout << std::endl;
	compmap(cmp1, cmp4, "cmp1", "cmp4");

	return ;

}