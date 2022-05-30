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

	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(3, 0, allo), comp);
	disp_tree(ins); std::cout << "3 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(6, 0, allo), comp);
	disp_tree(ins); std::cout << "6 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(9, 0, allo), comp);
	disp_tree(ins); std::cout << "9 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(12, 0, allo), comp);
	disp_tree(ins); std::cout << "12 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(2, 0, allo), comp);
	disp_tree(ins); std::cout << "2 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(8, 0, allo), comp);
	disp_tree(ins); std::cout << "8 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(4, 0, allo), comp);
	disp_tree(ins); std::cout << "4 inserted" << std::endl;

	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(1, 0, allo), comp);
	disp_tree(ins); std::cout << "1 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(7, 0, allo), comp);
	disp_tree(ins); std::cout << "7 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(10, 0, allo), comp);
	disp_tree(ins); std::cout << "10 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(0, 0, allo), comp);
	disp_tree(ins); std::cout << "0 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(11, 0, allo), comp);
	disp_tree(ins); std::cout << "11 inserted" << std::endl;
	ins = ins->insert(ins, RBpair<int, int, std::less<int>>(5, 0, allo), comp);
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
	
	std::cout << "Mixed test" << std::endl;

	RBTree<int, int> *mix = NULL;

	for (int i = 0 ; i < 5 ; i++)
	{
		mix = stepadd(mix, allo);
		disp_tree(mix);
	}
	

	RBTree<int, int> *wr = NULL;

	RBTree<int, int> *six;
	six = RBpair<int, int, std::less<int>>(6, 0, allo);
	six->parent = NULL;


	RBTree<int, int> *eleven = RBpair<int, int, std::less<int>>(11, 0, allo);
	eleven->parent = six;
	six->right = eleven;
	eleven->color = 1;

	RBTree<int, int> *four = RBpair<int, int, std::less<int>>(4, 0, allo);
	four->parent = six;
	six->left = four;

	RBTree<int, int> *twelve = RBpair<int, int, std::less<int>>(12, 0, allo);
	twelve->parent = eleven;
	eleven->right = twelve;

	RBTree<int, int> *nine = RBpair<int, int, std::less<int>>(9, 0, allo);
	nine->parent = eleven;
	eleven->left = nine;

	RBTree<int, int> *two = RBpair<int, int, std::less<int>>(2, 0, allo);
	two->parent = four;
	four->left = two;
	four->color = 1;

		RBTree<int, int> *ten = RBpair<int, int, std::less<int>>(10, 0, allo);
	ten->parent = nine;
	nine->right = ten;
	ten->color = 1;

	std::cout << "\n\none\n" << std::endl;
	disp_tree(six);
	std::cout << "\n\ntwo\n" << std::endl;
	six = six->vanish(six, 2, res, comp, allo);
	disp_tree(six);
	std::cout << "\n\nthree\n" << std::endl;
	six = six->vanish(six, 6, res, comp, allo);
	disp_tree(six);


	return ;


/*
	
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(37, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(34, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(31, 2, allo), comp);
	wr = wr->vanish(wr, 31, res, comp, allo);
	disp_tree(wr);

	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(7, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(63, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(86, 2, allo), comp);
	wr = wr->vanish(wr, 86, res, comp, allo);
	disp_tree(wr);

	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(48, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(46, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(78, 2, allo), comp);
		disp_tree(wr);
	wr = wr->vanish(wr, 48, res, comp, allo);
	disp_tree(wr);
	*/
	
/*
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(75, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(3, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(85, 2, allo), comp);
	wr = wr->vanish(wr, 85, res, comp, allo);
	disp_tree(wr);

	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(5, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(2, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(78, 2, allo), comp);
	wr = wr->vanish(wr, 5, res, comp, allo);
	disp_tree(wr);
*/

/*
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(41, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(11, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(48, 2, allo), comp);
	wr = wr->vanish(wr, 48, res, comp, allo);
	disp_tree(wr);

	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(86, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(65, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(17, 2, allo), comp);
	wr = wr->vanish(wr, 86, res, comp, allo);
	disp_tree(wr);

	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(75, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(74, 0, allo), comp);
	wr = wr->insert(wr, RBpair<int, int, std::less<int>>(51, 2, allo), comp);
		disp_tree(wr);
	wr = wr->vanish(wr, 75, res, comp, allo);
	disp_tree(wr);
	*/

	return ;

}
