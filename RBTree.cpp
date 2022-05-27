#include "RBTree.hpp"

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

	srand(time(NULL));

	RBTree<int, int> *truc = NULL;

	for (int i = 0 ; i < 5 ; i++)
	{
		truc = stepadd(truc, allo);
		disp_tree(truc);
	}


	RBTree<int, int> *wr = NULL;

	std::less<int> comp;
	bool res;
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
	return ;

}
