#ifndef RBTree_HPP
#define RBTree_HPP
#include <iostream>
#include "stdlib.h"
#include "pair.hpp"


//const T pair

template<class T, class V, class C = std::less<T> >
class RBTree
{
	public:

	typedef typename std::allocator<ft::pair<const T, V> > alloc_t;

	RBTree          		*left;
	RBTree          		*right;
	RBTree          		*parent;
	bool					color;
	ft::pair<const T, V> 	*p;

	//Constructor
	RBTree<T, V, C>(alloc_t &Alloc);
	RBTree<T, V, C>(const T &key, const V &val, alloc_t &Alloc);
	
		RBTree<T, V, C> *getpar(RBTree<T, V, C> *n);
		RBTree<T, V, C> *grandparent(RBTree<T, V, C> *n);
		RBTree<T, V, C> *brother(RBTree<T, V, C> *n);
		RBTree<T, V, C> *oncle(RBTree<T, V, C> *n);

		void rot_left(RBTree<T, V, C> *n);
		void rot_right(RBTree<T, V, C> *n);
		RBTree<T, V, C> *search(RBTree<T, V, C> *rac, const T &key, C &comp);
		RBTree<T, V, C> *search(RBTree<T, V, C> *rac, const T &key, const C &comp) const;
		void new_element(RBTree<T, V, C> *rac, RBTree<T, V, C> *n, C &comp);
		void repare(RBTree<T, V, C>  *n);
		void repareOncleBlack(RBTree<T, V, C> *n);
		bool blackNephews(RBTree<T, V, C> *n);
		RBTree<T, V, C> *insert(RBTree<T, V, C> *rac, RBTree<T, V, C> *n, C &comp);
		RBTree<T, V, C> *vanish(RBTree<T, V, C> *rac, const T &key, bool &erased, C &comp, alloc_t &Alloc);
		RBTree<T, V, C> *tovanish(RBTree<T, V, C> *start, alloc_t &Alloc);
		RBTree<T, V, C> *reparevanish(RBTree<T, V, C> *rac, RBTree<T, V, C> *n);
		RBTree<T, V, C> *getrac(RBTree<T, V, C> *n);

		void supress(RBTree<T, V, C> *n, alloc_t &Alloc);
		void clear(RBTree<T, V, C> *rac, alloc_t &Alloc);

		RBTree<T, V, C> *RBpair(const T &key, const V &val, std::allocator<ft::pair<const T, V> > &Alloc);

};

template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::getrac(RBTree<T, V, C> *n)
{
	RBTree<T, V, C> *res;

	res = n;
	while (getpar(res) != NULL)
		res = getpar(res);
	return (res);
}

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
void hight(RBTree<T, V> *rac, int *highl, int *highr, int *dep)
{
	if (rac == NULL)
	{
		std::cout << "(" << *dep << ")" <<std::endl;
		return ;
	}
	* dep +=1;
	int savedep = *dep;

	if (rac->parent->left == rac)
		(*highl) += 1;
	if (rac->parent->right == rac)
		*(highr) += 1;
	hight(rac->left, highl, highr, dep);
	*dep = savedep;
	hight(rac->right, highl, highr, dep);
	*dep = savedep;
	return ;
}

template<class T, class V>
bool check_hight(RBTree<T, V> *rac)
{
	int hl = 1, hr = 1, d = 0;

	hight(rac->left, &hl, &hr, &d);
	hl = 0;
	hr = 0;
	hight(rac->right, &hl, &hr, &d);
	return (true);
}

template <class T, class V, class C>
void display_node(RBTree<T, V, C> *n, std::string name);

template<class T, class V, class C>
void disp_tree(RBTree<T, V, C> *n)
{
	RBTree<T, V, C> *rac;
	rac = n;
	while (n->getpar(rac) != NULL)
		rac = n->getpar(rac);
	std::cout << "----------------------";
	display_tree(rac, 0);
	if (check_double_red(rac))
		std::cout << "ok" <<std::endl;
	else
		std::cout << "Wrong tree" << std::endl;
	//check_hight(rac);
	
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

template<class T, class V, class C>
RBTree<T, V, C> *RBpair(const T &key, const V &val, std::allocator<ft::pair<const T, V> > &Alloc);

template<class T, class V, class C>
void display_tree(RBTree<T, V, C> *rac, int sp);

template<class T, class V, class C>
RBTree<T, V, C>::RBTree(const T &key, const V &val, alloc_t &Alloc)
{
	this->parent = NULL;
	this->color = 0;
	this->left = NULL;
	this->right = NULL;
	this->p = Alloc.allocate(1);
	Alloc.construct(this->p, ft::make_pair<const T, V>(key, val));
}

template <class T, class V, class C> 
RBTree<T, V, C>::RBTree(alloc_t &Alloc)
{
	this->color = 0;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
	this->p = Alloc.allocate(1);
	Alloc.construct(this->p, ft::make_pair<const T, V>(T(), V()));
}

template<class T, class V, class C>
RBTree<T, V, C> *RBpair(const T &key, const V &val, std::allocator<ft::pair<const T, V> > &Alloc)
{
	return new RBTree<T, V, C>(key, val, Alloc);
}

template <class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::RBpair(const T &key, const V &val, std::allocator<ft::pair<const T, V> > &Alloc)
{
	return new RBTree<T, V, C>(key, val, Alloc);
}

template<class T, class V, class C>
void RBTree<T, V, C>::clear(RBTree<T, V, C> *rac, alloc_t &Alloc)
{
	if (rac == NULL)
		return ;
	if (rac->left == NULL && rac->right == NULL)
	{
		Alloc.deallocate(rac->p, 1);
		delete (rac);
		return ;
	}
	if (rac->left != NULL)
		clear(rac->left,  Alloc);
	if (rac->right != NULL)
		clear(rac->right, Alloc);
	Alloc.deallocate(rac->p, 1);
	delete (rac);
	return ;
}

template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::insert(RBTree<T, V, C> *rac, RBTree<T, V, C> *n, C &comp)
{
	new_element(rac, n, comp);

	repare(n);
	
	rac = n;
	while (getpar(rac) != NULL)
		rac = getpar(rac);
	return (rac);
}

template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::search(RBTree<T, V, C> *rac, const T &key, C &comp)
{
	while (1)
	{
		if (rac == NULL)
			return (NULL);
		if (!comp(key, rac->p->first) && !comp(rac->p->first, key))
			return (rac);
		if (comp(key, rac->p->first))
			rac = rac->left;
		else
			rac = rac->right;
	}
}


template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::search(RBTree<T, V, C> *rac, const T &key, const C &comp) const
{
	while (1)
	{
		if (rac == NULL)
			return (NULL);
		if (!comp(key, rac->p->first) && !comp(rac->p->first, key))
			return (rac);
		if (comp(key, rac->p->first))
			rac = rac->left;
		else
			rac = rac->right;
	}
}

template<class T,class V, class C>
bool RBTree<T, V, C>::blackNephews(RBTree<T, V, C> *n)
{
	if (brother(n) == NULL)
		return (true);
	if (brother(n)->left != NULL && brother(n)->left->color == 1)
		return (false);
	if (brother(n)->right != NULL && brother(n)->right->color == 1)
		return (false);
	return (true);
}

template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::reparevanish(RBTree<T, V, C> *rac, RBTree<T, V, C> *n)
{
	// cas 1
	disp_tree(rac);

	if (n == rac)
	{
		std::cout << "cas 1" << std::endl;
		n->color = 0;
		return (rac);
	}

	//cas 2

	if (brother(n) && brother(n)->color == 1 && getpar(n)->color == 0 && blackNephews(n))
	{
				std::cout << "cas 2" << std::endl;
		if (rac == getpar(n))
			rac = brother(n);
		brother(n)->color = 0;
		getpar(n)->color = 1;
		if (n == getpar(n)->left)
			rot_left(brother(n));
		else
			rot_right(brother(n));
		reparevanish(rac, n);
	}

	//cas 3

	if (brother(n) && brother(n)->color == 0 && getpar(n)->color == 0 && blackNephews(n))
	{
				std::cout << "cas 3" << std::endl;
		brother(n)->color = 1;
		reparevanish(rac, getpar(n));
	}

	//cas 4

	if (brother(n) && brother(n)->color == 0 && getpar(n)->color == 1 && blackNephews(n))
	{
				std::cout << "cas 4" << std::endl;
		getpar(n)->color = 0;
		brother(n)->color = 1;
		return (rac);
	}

	//cas 5

	if (n == getpar(n)->left)
	{
				std::cout << "cas 5a" << std::endl;
	if (brother(n) && brother(n)->color == 0 && brother(n)->left && brother(n)->left->color == 1 && (brother(n)->right == NULL || brother(n)->right->color == 0))
	{
		brother(n)->left->color = 0;
		brother(n)->color = 1;
		if (brother(n) == rac)
			rac = brother(n)->left;
		rot_right(brother(n)->left);
		if (getpar(n)->color != 1)
			reparevanish(rac, n);
		return (rac);
	}
	}
	else
	{
	if ( brother(n) && brother(n)->color == 0 && brother(n)->right && brother(n)->right->color == 1 && (brother(n)->left == NULL || brother(n)->left->color == 0))
	{
				std::cout << "cas 5b" << std::endl;
		brother(n)->right->color = 0;
		brother(n)->color = 1;
		if (brother(n) == rac)
			rac = brother(n)->right;
		rot_left(brother(n)->right);
		if (getpar(n)->color != 1)
			reparevanish(rac, n);
		return(rac);
	}
	}
	//cas 6

	if (n == getpar(n)->left)
	{

	if (brother(n) && brother(n)->color == 0 && brother(n)->right && brother(n)->right->color == 1)
	{
				std::cout << "cas 6a" << std::endl;
		if (rac == getpar(n))
			rac = brother(n);
		brother(n)->right->color = 0;
		brother(n)->color = getpar(n)->color;
		rot_left(brother(n));
		getpar(n)->color = 0;
		return (rac);
	}
	}
	else
	{
	if (brother(n) && brother(n)->color == 0 && brother(n)->left && brother(n)->left->color == 1)
	{
				std::cout << "cas 6b" << std::endl;
		if (rac == getpar(n))
			rac = brother(n);

		brother(n)->left->color = 0;
		brother(n)->color = getpar(n)->color;
		rot_right(brother(n));
		return (rac);
	}
	}
	return (rac);
}

template <class T, class V, class C>
void RBTree<T, V, C>::supress(RBTree *n, alloc_t &Alloc)
{
	if (n->parent && n == n->parent->left)
	{
		n->parent->left = NULL;
	}
	else if (n->parent && n == n->parent->right)
	{
		n->parent->right = NULL;
	}
	Alloc.deallocate(n->p, 1);
	delete n;
}

template <class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::tovanish(RBTree<T, V, C> *start, alloc_t &Alloc)
{
	RBTree<T, V, C> *cur;
	//bool tmpc;

	cur = start;
	if (start->right != NULL && start->left == NULL)
	{
		Alloc.deallocate(start->p, 1);
		start->p = Alloc.allocate(1);
		Alloc.construct(start->p, ft::make_pair<const T, V>(start->right->p->first, start->right->p->second));
		//tmpc = start->right->color; start->right->color = start->color; start->color = tmpc;
		return (start->right);
	}
	if (start->right == NULL && start->left != NULL)
	{
		Alloc.deallocate(start->p, 1);
		start->p = Alloc.allocate(1);
		Alloc.construct(start->p, ft::make_pair<const T, V>(start->left->p->first, start->left->p->second));
		//tmpc = start->left->color; start->left->color = start->color; start->color = tmpc;
		return (start->left);
	}
	if (start->right != NULL && start->left != NULL)
	{
		cur = start->right;
		while (cur->left != NULL)
		{
			cur = cur->left;
		}
		Alloc.deallocate(start->p, 1);
		start->p = Alloc.allocate(1);
		Alloc.construct(start->p, ft::make_pair<const T, V>(cur->p->first, cur->p->second));
		//tmpc = cur->color; cur->color = start->color; start->color = tmpc;
		return (cur);
	}
	return (start);
}

template <class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::vanish(RBTree<T, V, C> *rac, const T &key, bool &erased, C &comp, typename RBTree<T, V, C>::alloc_t &Alloc)
{
	RBTree<T, V, C> *res;

	erased = true;
	res = rac->search(rac, key, comp);
	if (res == NULL)
	{
		erased = false;
		return (rac);
	}

	if (getpar(res) == NULL && res->left == NULL && res->right == NULL)
	{
		rac->supress(res, Alloc);
		return (NULL);
	}
/*
	if (res->color == 1)
	{
		if (res->left == NULL && res->right == NULL)
		{
			rac->supress(res, Alloc);
			return (rac);
		}
		if (res->right != NULL && res->left == NULL)
		{
			if (res == getpar(res)->right)
				getpar(res)->right = res->right;
			else
				getpar(res)->left = res->right;
			res->right->parent = getpar(res);
			rac->supress(res, Alloc);
			return (rac);
		}
		if (res->right == NULL && res->left != NULL)
		{
			if (res == getpar(res)->right)
				getpar(res)->right = res->left;
			else
				getpar(res)->left = res->left;
			res->left->parent = getpar(res);
			rac->supress(res, Alloc);
			return (rac);
		}
	}
*/
	res = rac->tovanish(res, Alloc);
	//std::cout << "(" <<res->p->first << ")" <<std::endl;

	if (res == rac)
	{
		rac->supress(res, Alloc);
		return (NULL);
	}
	if (res->left == NULL && res->right == NULL)
	{
		if (res->color == 1)
		{
			rac->supress(res, Alloc);
			return (getrac(rac));
		}
		rac = reparevanish(rac, res);
		rac->supress(res, Alloc);
		return (getrac(rac));
	}
	if (res->right != NULL)
	{

		if (res->color == 0)
		{
				std::cout << "(" <<res->p->first << ")" <<std::endl;
			rac = reparevanish(rac, res);
				std::cout << "(" <<res->p->first << ")" <<std::endl;
		}
		if (res == getpar(res)->right)
			getpar(res)->right = res->right;
		else
			getpar(res)->left = res->right;
		res->right->parent = getpar(res);
		Alloc.deallocate(res->p, 1);
		delete res;
		return (getrac(rac));
	}

	if (res->left != NULL)
	{
		if (res->color == 0)
			rac = reparevanish(rac, res);
		if (res == getpar(res)->right)
			getpar(res)->right = res->left;
		else
			getpar(res)->left = res->left;
		res->left->parent = getpar(res);
		Alloc.deallocate(res->p, 1);
		delete res;
		return (getrac(rac));
	}
	return (getrac(rac));
}

template<class T, class V, class C>
void RBTree<T, V, C>::rot_left(RBTree<T, V, C> *x) //3-4-6
{
	if (getpar(x) == NULL)
	{
		if (x->right)
			rot_left(x->right);
		return ;
	}
	x = getpar(x);
	RBTree<T, V, C> *y = x->right;

	if (y == NULL)
		return ;

	if (y->left != NULL)
	{
		y->left->parent = x;
		x->right = y->left;
		y->left = NULL;
		y->parent = NULL;
	}
	else
	{
		x->right = NULL;
	}
	if (x->parent == NULL)
	{
		y->parent = NULL;
		x->parent = y;
		y->left = x;
		return ;
	}
	if (x->parent != NULL)
	{
		if (x == x->parent->left)
		{
			y->parent = x->parent;
			x->parent->left = y;
			x->parent = y;
			y->left = x;
		}
		else
		{
			y->parent = x->parent;
			x->parent->right = y;
			x->parent = y;
			y->left = x;
		}
	}
}

template<class T, class V, class C>
void RBTree<T, V, C>::rot_right(RBTree *y)
{

	if (getpar(y) == NULL)
	{
		if (y->left)
			rot_right(y->left);
		return ;
	}
	y = getpar(y);
	RBTree<T, V, C> *x = y->left;

	if (x == NULL)
		return ;

	if (x->right != NULL)
	{
		x->right->parent = y;
		y->left = x->right;
		x->right = NULL;
		x->parent = NULL;
	}
	else
	{
		y->left = NULL;
	}

	if (y->parent == NULL)
	{
		x->parent = NULL;
		x->right = y;
		y->parent = x;
		return ;
	}
	if (y == y->parent->right)
	{
		x->parent = y->parent;
		y->parent->right = x;
		y->parent = x;
		x->right = y;
	}
	else
	{
		x->parent = y->parent;
		y->parent->left = x;
		y->parent = x;
		x->right = y;
	}
}

template<class T, class V, class C>
void RBTree<T, V, C>::new_element(RBTree<T, V, C> *rac, RBTree<T, V, C> *n, C &comp)
{
	if (rac != NULL && comp(n->p->first, rac->p->first))
	{
		if (rac->left != NULL)
		{
			new_element(rac->left, n, comp);
			return ;
		}
		else
			rac->left = n;
	}
	else if (rac != NULL)
	{
		if (rac->right != NULL)
		{
			new_element(rac->right, n, comp);
			return ;
		}
		else
			rac->right = n;
	}

	n->parent = rac;
	n->left = NULL;
	n->right = NULL;
	n->color = 1;
	
}

template<class T, class V, class C>
void RBTree<T, V, C>::repareOncleBlack(RBTree<T, V, C> *n)
{
	RBTree<T, V, C> *g = grandparent(n);
	bool st = 0;

	if (oncle(n) == NULL)
		st = 1;

	if (g->left && n == g->left->right)
	{
		rot_left(n);
		n = n->left;
	}
	else if (g->right && n == g->right->left)
	{
		rot_right(n);
		n = n->right;
	}

	RBTree<T, V, C> *np = getpar(n);
	RBTree<T, V, C> *ng = grandparent(n);

	if (n == np->left)
	{
		if (st)
			rot_right(np);
		else
			rot_right(np);
	}
	else
	{
		if (st)
		{
			rot_left(np);
		}
		else
		{
			rot_left(np);
		}
	}
	np->color = 0;
	ng->color = 1;
}

template<class T, class V, class C>
void RBTree<T, V, C>::repare(RBTree<T, V, C> *n)
{
	if (getpar(n) == NULL)
	{
		n->color = 0;
		return ;
	}
	if (getpar(n)->color == 0)
		return ;

	if (oncle(n) && oncle(n)->color == 1)
	{
		getpar(n)->color = 0;
		oncle(n)->color = 0;
		RBTree<T, V, C> *g = grandparent(n);
		if (g != NULL)
		{ 
			g->color = 1;
			if (getpar(g) == NULL)
			{
				g->color = 0;
				return ;
			}
			repare(g);
		}
		return ;
	}
	repareOncleBlack(n);
}

template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::getpar(RBTree *n)
{
	if (n == NULL)
		return (NULL);
	return (n->parent);
}

template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::grandparent(RBTree *n)
{
	RBTree<T, V, C> *p = getpar(n);

	if (p == NULL)
		return (NULL);
	return(getpar(p));
}

template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::brother(RBTree *n)
{
	RBTree<T, V, C> *p = getpar(n);

	if (p == NULL)
		return (NULL);
	if (n == p->left)
		return (p->right);
	return (p->left);
}

template<class T, class V, class C>
RBTree<T, V, C> *RBTree<T, V, C>::oncle(RBTree *n)
{
	RBTree<T, V, C> *p = getpar(n);
	RBTree<T, V, C> *gp = grandparent(n);

	if (gp == NULL)
		return(NULL);
	return (brother(p));
}

#endif