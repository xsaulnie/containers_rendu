#ifndef RBtest_HPP
#define RBtest_HPP
#include <iostream>
#include <vector>
#include <string>
#include "RBTree.hpp"

template <class T, class V>
bool double_red(RBTree<T, V> *rac, bool *res)
{

	if (rac == NULL)
	{
		return (true);
	}
	if (rac->color == 1)
	{
		if (rac->left != NULL && rac->left->color == 1)
		{
			*res = false;
			return (double_red(rac->left, res) && double_red(rac->right, res));
		}
		if (rac->right != NULL && rac->right->color == 1)
		{
			*res = false;
			return (double_red(rac->left, res) && double_red(rac->right, res));
		}
	}
	return (true);
}

template <class T, class V>
bool check_double_red(RBTree<T, V> *rac)
{
	bool res = true;

	double_red(rac->left, &res);
	double_red(rac->right, &res);
	return (res);
}

template<class T, class V>
void load_count(std::vector<int> &res, RBTree<T, V> *rac, int lvl)
{
    int add;

    add = 0;
    if (rac == NULL)
    {
        res.push_back(lvl);
        return ;
    }
    if (rac->color == 0)
        add = 1;
    load_count(res, rac->left, lvl + add);
    load_count(res, rac->right, lvl + add);
}

template<class T, class V>
bool disp_count(RBTree<T, V> *rac)
{
    int black_level;
    if (rac == NULL)
        return (true);
    std::vector<int> res;
    load_count(res, rac, 0);

    if (res.empty() == true)
        return (true);

    black_level = res[0]; 
    for (size_t i = 0 ; i < res.size() ; i++)
    {
        if (black_level != res[i])
        {
            for (size_t i = 0 ; i < res.size() ; i++)
            {
                std::cout << "-" <<res[i] << "-" << std::endl;
            }
            return (false);
        }
    }
    return (true);
}

template<class T, class V>
bool hight(RBTree<T, V> *rac, int &lvl)
{
	if (rac == NULL)
		return (true);
	(void)lvl;
	int leftM = 0;
	int rightM = 0;

	if (hight(rac->left, leftM) && hight(rac->right, rightM))
	{
		int allmin = (leftM < rightM) ? leftM + 1 : rightM + 1;
		int allmax = (leftM > rightM) ? leftM + 1 : rightM + 1;
		return (allmax <= 2 * allmin);
	}
	return false;
}

template<class T, class V, class C>
void disp_tree(RBTree<T, V, C> *n)
{
	RBTree<T, V, C> *rac;
	std::allocator<ft::pair<const T, V> > allo;
	rac = n;
	while (n->getpar(rac) != NULL)
		rac = n->getpar(rac);
	std::cout << "----------------------";
	if (rac != NULL)
	{
		display_tree(rac, 0);
	if (check_double_red(rac) && disp_count(rac))
		std::cout << "ok" <<std::endl;
	else
	{
		std::cout << "Wrong tree" << std::endl;
		n->clear(n, allo);
		exit(1);
	}
	}
	if (rac == NULL)
		std::cout << "\nempty \n";
	std::cout << "----------------------" << std::endl;
}

template<class T, class V, class C>
void display_tree(RBTree<T, V, C> *rac, int sp)
{
	if (rac == NULL)
		return ;
	sp += 5;

	display_tree(rac->right, sp);

	if (sp != 0)
		std::cout << std::endl;

	for (int i = 5 ; i < sp ; i++)
	{
		std::cout << " ";
	}
	if (rac->color == 1)
		std::cout << "|" << rac->p->first << "|" << std::endl;
	else
	{
		std::cout << rac->p->first << std::endl;
	}
	display_tree(rac->left, sp);
}

#endif