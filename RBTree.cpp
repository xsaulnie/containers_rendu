#include "RBTree.hpp"
#include <vector>

template <class T, class V>
void display_node(RBTree<T, V> *n, std::string name)
{
	std::cout << "node " << name << " ";
	std::cout << n->p->first;
	if (n->right == NULL)
	{
		std::cout << " right NULL ";
	}
	else
	{
		std::cout << " right " << n->right->p->first;
	}
	if (n->left == NULL)
	{
		std::cout << " left NULL ";
	}
	else
	{
		std::cout << " left " << n->left->p->first;
	}

	if (n->parent == NULL)
	{
		std::cout << " parent NULL ";
	}
	else
	{
		std::cout << " parent " << n->parent->p->first;
	}
	std::cout << std::endl;
}

void test_big()
{
	std::allocator<ft::pair<const int, int> > allo;
	std::less<int> comp;
	RBTree<int, int, std::less<int> > *ins = NULL;
	int nb;
	bool err;
	int ini;
	int rm = 0;

	for (int i = 0 ; i < 100 ; i++)
	{
		ini = 0;
		nb = rand() % 1000;
		if (ins->search(ins, nb, comp) == NULL)
		{
			ins = ins->insert(ins, RBpair<int, int, std::less<int> >(nb, 0, allo), comp);
		}
		if (ins && (!(check_double_red(ins) && hight(ins, nb))))
			std::cout << "Wrong Tree" << std::endl;
	}
	disp_tree(ins);

	for (int i = 0 ; i < 300 ; i++)
	{
		ini = 0;
		nb = rand() % 1000;
		ins = ins->vanish(ins, nb, err, comp, allo);
		if (err)
			rm++;
		if (ins && !(check_double_red(ins) && hight(ins, ini)))
			std::cout << "Wrong Tree" << std::endl;
	}
	std::cout << rm << " nodes removed" << std::endl;
	disp_tree(ins);
	ins->clear(ins, allo);
}

template <class T, class V, class C>
RBTree<T, V, C> *stepadd(RBTree<T, V, C> *n, std::allocator<ft::pair<const int, int> > allo)
{

	std::less<int> comp;
	int num1, num2, num3;
	bool err;

	num1 = rand() % 100;
	do
	{
		num2 = rand() % 100;
	} while (num2 == num1);
	
	do
	{
		num3 = rand() % 100;
	} while (num3 == num1 || num3 == num2);
	
	if (n->search(n, num1, comp) == NULL)
		n = n->insert(n, RBpair<T, V, C>(num1, 0, allo), comp);
	if (n->search(n, num2, comp) == NULL)
		n = n->insert(n, RBpair<T, V, C>(num2, 0, allo), comp);
	if (n->search(n, num3, comp) == NULL)
		n = n->insert(n, RBpair<T, V, C>(num3, 0, allo), comp);
	std::cout << "+" << num1 << " "<<num2 << " " << num3<< "\n-";
	
	int choice = rand() % 3;

	if (choice == 0)
	{
		n = n->vanish(n, num1, err, comp, allo);
		std::cout << num1 << std::endl;
	}
	if (choice == 1)
	{
		n = n->vanish(n, num2, err, comp, allo);
		std::cout << num2 << std::endl;
	}
	if (choice == 2)
	{
		n = n->vanish(n, num3, err, comp, allo);
		std::cout << num3 << std::endl;
	}
	return (n);
}


void test_RBTree()
{
	std::allocator<ft::pair<const int, int> > allo;
	std::less<int> comp;
	bool res;
	srand(time(NULL));

	std::cout << "Test insertion" << std::endl; //0 5 11

	RBTree<int, int> *ins = NULL;

	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(3, 0, allo), comp);
	disp_tree(ins); std::cout << "3 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(6, 0, allo), comp);
	disp_tree(ins); std::cout << "6 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(9, 0, allo), comp);
	disp_tree(ins); std::cout << "9 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(12, 0, allo), comp);
	disp_tree(ins); std::cout << "12 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(2, 0, allo), comp);
	disp_tree(ins); std::cout << "2 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(8, 0, allo), comp);
	disp_tree(ins); std::cout << "8 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(4, 0, allo), comp);
	disp_tree(ins); std::cout << "4 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(1, 0, allo), comp);
	disp_tree(ins); std::cout << "1 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(7, 0, allo), comp);
	disp_tree(ins); std::cout << "7 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(10, 0, allo), comp);
	disp_tree(ins); std::cout << "10 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(0, 0, allo), comp);
	disp_tree(ins); std::cout << "0 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(11, 0, allo), comp);
	disp_tree(ins); std::cout << "11 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int> >(5, 0, allo), comp);
	disp_tree(ins); std::cout << "5 inserted" << std::endl;
	
	std::cout << "Test delete\n";

	std::vector<int> elem;
	int nb;
	for (int i = 0 ; i <= 12 ; i++)
		elem.push_back(i);

	while (!elem.empty())
	{
		nb = rand() % elem.size();

		std::cout << elem[nb] << " removed" << std::endl;

		ins = ins->vanish(ins, elem[nb], res, comp, allo);
		elem.erase(elem.begin() + nb);
		disp_tree(ins);
	}
	ins->clear(ins, allo);
	
	std::cout << "Mixed test" << std::endl;

	RBTree<int, int> *mix = NULL;

	for (int i = 0 ; i < 5 ; i++)
	{
		mix = stepadd(mix, allo);
		disp_tree(mix);
	}
	mix->clear(mix, allo);

	std::cout << "Big test" << std::endl;
	test_big();
	return ;
}
