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
	
	
	return ;


	ns::map <int, int> iteinser;

	ns::map <int, int> citer(test.begin(), test.end());

	display_map(citer);

	iteinser.insert(++test.begin(), --test.end());

	display_map(iteinser);

	display_map(citer);


	std::cout << " value of citer[30] : " << citer[30] << std::endl;

	std::cout << " value of citer[47] : " << citer[47] << std::endl;

	citer[47] =  47;
	std::cout << " value of citer[47] : " << citer[47] << std::endl;

	//disp_m(citer);
	citer.insert(ns::pair<int, int>(27, 8));
	//disp_m(citer);

	std::cout << "affecting test at citer" << std::endl;
	citer = test;
	//disp_m(citer);

	std::cout << "erasing element 6 and element 30" << std::endl;

	citer.erase(++citer.begin());

	citer.erase(--(--citer.end()));

	//disp_m(citer);

	std::cout << "erasing all exepted first and last" << std::endl;

	citer.erase(++citer.begin(), --citer.end());
	//disp_m(citer);

	ns::map<int, int> mini;

	mini.insert(ns::pair<int, int>(8, 0));
	mini.insert(ns::pair<int, int>(60, 0));

	std::cout << "mini map" << std::endl;

	//disp_m(mini);

	ns::swap(citer, mini);

	std::cout << "mini map after swap" << std::endl;

	//disp_m(mini);

	std::cout << "citer after swap" << std::endl;

	//disp_m(citer);

	ns::map<int, int> map(test.begin(), test.end());

    ns::map<int, int> map_copy(map);

	std::cout << "Copy constryctor of test" << std::endl;
	//disp_m(map_copy);

	if (citer.begin() != citer.end())
		std::cout << "They are differents" << std::endl;

	if (citer == mini)
		std::cout << "citer and mini are equal" << std::endl;
	else
		std::cout << "citer and mini are not equal" << std::endl;
	if (citer != mini)
		std::cout << "citer and mini are differents" << std::endl;
	else
		std::cout << "citer and mini are not differents" << std::endl;

	if (mini == mini)
		std::cout << "mini is mini" << std::endl;
	else
		std::cout << "mini is not mini" << std::endl;

	ns::map<int, std::string> dico1;
	ns::map<int, std::string> dico2;

	dico1.insert(ns::pair<int, std::string>(1, "base"));
	dico1.insert(ns::pair<int, std::string>(2, "bonjour"));

	dico2.insert(ns::pair<int, std::string>(1, "base"));
	dico2.insert(ns::pair<int, std::string>(2, "ca va"));


	if (dico1 > dico2)
		std::cout << "dico1 is inferior" << std::endl;
	else
		std::cout << "dico1 is not inferior" << std::endl;
	
	std::cout << "Test bound" << std::endl;

	std::cout << "Lower bound of 15 : " << (map.lower_bound(15))->first << std::endl;
	std::cout << "Lower bound of 30 : " << (map.lower_bound(30))->first << std::endl;
	std::cout << "Upper bound of 15 : " << (map.upper_bound(15))->first << std::endl;
	std::cout << "Upper bound of 30 : " << (map.upper_bound(30))->first << std::endl;

	if (map.upper_bound(100) == map.end())
		std::cout << "Upper bound of 100 return end iterator" << std::endl;

	ns::pair<ns::map<int, int>::iterator, ns::map<int, int>::iterator> prange;

	prange = map.equal_range(28);
	std::cout << "equal range 28 : "<< (prange.first)->first << "-" <<(prange.second)->first << std::endl;

	ns::map<int, int>::const_iterator cit = map.begin();
	cit++;
	std::cout << cit->second << std::endl;

	return ;
/*
	ns::map <int, int> test;

	test.insert(ns::pair<int, int>(42, 42));
	ns::map<int, int>::const_iterator cti = test.begin();
	ns::map<int, int>::iterator ti = test.begin();

	if (ti == cti)
		std::cout << "OK" << std::endl;
	return ;
	*/

}