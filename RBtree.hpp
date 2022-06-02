#ifndef RBtree_HPP
#define RBtree_HPP
#include <iostream>
#include "stdlib.h"
#include "pair.hpp"



//const T pair

template<class T, class C = std::less<T> >
class RBtree
{
	public:

	typedef typename std::allocator<T> alloc_t;

	RBtree          		*left;
	RBtree          		*right;
	RBtree          		*parent;
	bool					color;
	T 	        			*p;

	//Constructor
	RBtree<T, C>(alloc_t &Alloc);
	RBtree<T, C>(const T &val, alloc_t &Alloc);
	
		RBtree<T, C> *getpar(RBtree<T, C> *n);
		RBtree<T, C> *grandparent(RBtree<T, C> *n);
		RBtree<T, C> *brother(RBtree<T, C> *n);
		RBtree<T, C> *oncle(RBtree<T, C> *n);

		void rot_left(RBtree<T, C> *n);
		void rot_right(RBtree<T, C> *n);
		RBtree<T, C> *search(RBtree<T, C> *rac, const T &key, C &comp);
		RBtree<T, C> *search(RBtree<T, C> *rac, const T &key, const C &comp) const;
		void new_element(RBtree<T, C> *rac, RBtree<T, C> *n, C &comp);
		void repare(RBtree<T, C>  *n);
		void repareOncleBlack(RBtree<T, C> *n);
		bool blackNephews(RBtree<T, C> *n);
		RBtree<T, C> *insert(RBtree<T, C> *rac, RBtree<T, C> *n, C &comp);
		RBtree<T, C> *vanish(RBtree<T, C> *rac, const T &key, bool &erased, C &comp, alloc_t &Alloc);
		RBtree<T, C> *tovanish(RBtree<T, C> *start, alloc_t &Alloc);
		RBtree<T, C> *reparevanish(RBtree<T, C> *rac, RBtree<T, C> *n);
		RBtree<T, C> *getrac(RBtree<T, C> *n);

		void supress(RBtree<T, C> *n, alloc_t &Alloc);
		void clear(RBtree<T, C> *rac, alloc_t &Alloc);

		RBtree<T, C> *RBval(const T &val, std::allocator<T > &Alloc);

};

template<class T, class C>
RBtree<T, C> *RBtree<T, C>::getrac(RBtree<T, C> *n)
{
	RBtree<T, C> *res;

	res = n;
	while (getpar(res) != NULL)
		res = getpar(res);
	return (res);
}

template<class T, class C>
RBtree<T, C> *RBval(const T &val, std::allocator<T> &Alloc);

template<class T, class C>
RBtree<T, C>::RBtree(const T &val, alloc_t &Alloc)
{
	this->parent = NULL;
	this->color = 0;
	this->left = NULL;
	this->right = NULL;
	this->p = Alloc.allocate(1);
	Alloc.construct(this->p, val);
}

template <class T, class C> 
RBtree<T, C>::RBtree(alloc_t &Alloc)
{
	this->color = 0;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
	this->p = Alloc.allocate(1);
	Alloc.construct(this->p, T());
}

template<class T, class C>
RBtree<T, C> *RBval(const T &val, std::allocator<T> &Alloc)
{
	return new RBtree<T, C>(val, Alloc);
}

template <class T, class C>
RBtree<T, C> *RBtree<T, C>::RBval(const T &val, std::allocator<T> &Alloc)
{
	return new RBtree<T, C>(val, Alloc);
}

template<class T, class C>
void RBtree<T, C>::clear(RBtree<T, C> *rac, alloc_t &Alloc)
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

template<class T, class C>
RBtree<T, C> *RBtree<T, C>::insert(RBtree<T, C> *rac, RBtree<T, C> *n, C &comp)
{
	new_element(rac, n, comp);
	
	repare(n);
	
	rac = n;
	while (getpar(rac) != NULL)
		rac = getpar(rac);
	return (rac);
}

template<class T, class C>
RBtree<T, C> *RBtree<T, C>::search(RBtree<T, C> *rac, const T &key, C &comp)
{
	while (1)
	{
		if (rac == NULL)
			return (NULL);
		if (!comp(key, *(rac->p)) && !comp(*(rac->p), key))
			return (rac);
		if (comp(key, *(rac->p)))
			rac = rac->left;
		else
			rac = rac->right;
	}
}


template<class T, class C>
RBtree<T, C> *RBtree<T, C>::search(RBtree<T, C> *rac, const T &key, const C &comp) const
{
	while (1)
	{
		if (rac == NULL)
			return (NULL);
		if (!comp(key, *(rac->p)) && !comp(*(rac->p), key))
			return (rac);
		if (comp(key, *(rac->p)))
			rac = rac->left;
		else
			rac = rac->right;
	}
}

template<class T, class C>
bool RBtree<T, C>::blackNephews(RBtree<T, C> *n)
{
	if (brother(n) == NULL)
		return (true);
	if (brother(n)->left != NULL && brother(n)->left->color == 1)
		return (false);
	if (brother(n)->right != NULL && brother(n)->right->color == 1)
		return (false);
	return (true);
}

template<class T, class C>
RBtree<T, C> *RBtree<T, C>::reparevanish(RBtree<T, C> *rac, RBtree<T, C> *n)
{
	// cas 1

	if (n == rac)
	{
		n->color = 0;
		return (rac);
	}

	//cas 2

	if (brother(n) && brother(n)->color == 1 && getpar(n)->color == 0 && blackNephews(n))
	{
		if (rac == getpar(n))
			rac = brother(n);
		brother(n)->color = 0;
		getpar(n)->color = 1;
		if (n == getpar(n)->left)
			rot_left(brother(n));
		else
			rot_right(brother(n));
		return (reparevanish(rac, n));
	}

	//cas 3

	if (brother(n) && brother(n)->color == 0 && getpar(n)->color == 0 && blackNephews(n))
	{
		brother(n)->color = 1;
		if (getpar(n)->parent == NULL)
		{
			if (n == getpar(n)->right)
			{
				if (n->right != NULL && n->left == NULL && brother(n)->left == NULL && brother(n)->right == NULL)
				{
					brother(n)->color = 0;
					n->right->color = 0;
				}
			}
			else
			{
				if (n->left != NULL && n->right == NULL && brother(n)->left == NULL && brother(n)->right == NULL)
				{
					brother(n)->color = 0;
					n->left->color = 0;
				}			
			}
		}
		return(reparevanish(rac, getpar(n)));
	}

	//cas 4

	if (brother(n) && brother(n)->color == 0 && getpar(n)->color == 1 && blackNephews(n))
	{
		getpar(n)->color = 0;
		brother(n)->color = 1;
		return (rac);
	}

	//cas 5

	if (n == getpar(n)->left)
	{
	if (brother(n) && brother(n)->color == 0 && brother(n)->left && brother(n)->left->color == 1 && (brother(n)->right == NULL || brother(n)->right->color == 0))
	{
		brother(n)->left->color = 0;
		brother(n)->color = 1;
		if (brother(n) == rac)
			rac = brother(n)->left;
		rot_right(brother(n)->left);
			return(reparevanish(rac, n));
	}
	}
	else
	{
	if (brother(n) && brother(n)->color == 0 && brother(n)->right && brother(n)->right->color == 1 && (brother(n)->left == NULL || brother(n)->left->color == 0))
	{
		brother(n)->right->color = 0;
		brother(n)->color = 1;
		if (brother(n) == rac)
			rac = brother(n)->right;
		rot_left(brother(n)->right);
		return(reparevanish(rac, n));
	}
	}


	//cas 6

	if (n == getpar(n)->left)
	{
		if (brother(n) && brother(n)->color == 0 && brother(n)->right && brother(n)->right->color == 1)
		{
			if (rac == getpar(n))
				rac = brother(n);
			brother(n)->right->color = 0;
			brother(n)->color = getpar(n)->color;
			getpar(n)->color = 0;
			rot_left(brother(n));
			getpar(n)->color = 0;
			return (rac);
		}
	}
	else
	{
		if (brother(n) && brother(n)->color == 0 && brother(n)->left && brother(n)->left->color == 1)
		{
			if (rac == getpar(n))
				rac = brother(n);

			brother(n)->left->color = 0;
			brother(n)->color = getpar(n)->color;
			getpar(n)->color = 0;
			rot_right(brother(n));
			return (rac);
		}
	}

	if (n->left != NULL)
		n->left->color = 0;
	if (n->right != NULL)
		n->right->color = 0;
	return (rac);
}

template <class T, class C>
void RBtree<T, C>::supress(RBtree *n, alloc_t &Alloc)
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

template <class T, class C>
RBtree<T, C> *RBtree<T, C>::tovanish(RBtree<T, C> *start, alloc_t &Alloc)
{
	RBtree<T, C> *cur;

	cur = start;
	if (start->right != NULL && start->left == NULL)
	{
		Alloc.deallocate(start->p, 1);
		start->p = Alloc.allocate(1);
		Alloc.construct(start->p, *(start->right->p));
		return (start->right);
	}
	if (start->right == NULL && start->left != NULL)
	{
		Alloc.deallocate(start->p, 1);
		start->p = Alloc.allocate(1);
		Alloc.construct(start->p, *(start->left->p));
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
		Alloc.construct(start->p, *(cur->p));
		return (cur);
	}
	return (start);
}

template <class T, class C>
RBtree<T, C> *RBtree<T, C>::vanish(RBtree<T, C> *rac, const T &key, bool &erased, C &comp, typename RBtree<T, C>::alloc_t &Alloc)
{
	RBtree<T, C> *res;
	RBtree<T, C> *red = NULL;

	erased = true;
	res = rac->search(rac, key, comp);
	if (res == NULL)
	{
		erased = false;
		return (rac);
	}

	if (getpar(res) == NULL)
	{
		RBtree<T, C> *ret;
		if (res->left == NULL && res->right == NULL)
		{
			rac->supress(res, Alloc);
			return (NULL);
		}
		if (res->right == NULL && res->left != NULL)
		{
			Alloc.deallocate(res->p, 1);
			res->left->parent = NULL;
			res->left->color = 0;
			ret = res->left;
			delete res;
			return (ret);
		}
		if (res->left == NULL && res->right != NULL)
		{
			Alloc.deallocate(res->p, 1);
			res->right->parent = NULL;
			res->right->color = 0;
			ret = res->right;
			delete res;
			return (ret);
		}
	}

	if (res->color == 1)
		red = res;

	res = rac->tovanish(res, Alloc);


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

	if (red != NULL)
	{
		if (res->parent == red && res->right != NULL)
		{
			if (getpar(res)->color == 1 && res->right->color == 1)
				res->right->color = 0;
			if (res == getpar(res)->right)
				getpar(res)->right = res->right;
			else
				getpar(res)->left = res->right;
			res->right->parent = getpar(res);
			Alloc.deallocate(res->p, 1);
			delete res;
			return (getrac(rac));
		}
		if (res->parent == red && res->left != NULL)
		{
			if (getpar(res)->color == 1 && res->left->color == 1)
				res->left->color = 0;
			if (res == getpar(res)->right)
				getpar(res)->right = res->left;
			else
				getpar(res)->left = res->left;
			res->left->parent = getpar(res);
			Alloc.deallocate(res->p, 1);
			delete res;
			return (getrac(rac));
		}
	}

	if (res->right != NULL)
	{
		if (res->color == 0)
			rac = reparevanish(rac, res);
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

template<class T, class C>
void RBtree<T, C>::rot_left(RBtree<T, C> *x)
{
	if (getpar(x) == NULL)
	{
		if (x->right)
			rot_left(x->right);
		return ;
	}
	x = getpar(x);
	RBtree<T, C> *y = x->right;

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

template<class T, class C>
void RBtree<T, C>::rot_right(RBtree *y)
{

	if (getpar(y) == NULL)
	{
		if (y->left)
			rot_right(y->left);
		return ;
	}
	y = getpar(y);
	RBtree<T, C> *x = y->left;

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

template<class T, class C>
void RBtree<T, C>::new_element(RBtree<T, C> *rac, RBtree<T, C> *n, C &comp)
{
	if (rac != NULL && comp(*(n->p), *(rac->p)))
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

template<class T, class C>
void RBtree<T, C>::repareOncleBlack(RBtree<T, C> *n)
{
	RBtree<T, C> *g = grandparent(n);
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

	RBtree<T, C> *np = getpar(n);
	RBtree<T, C> *ng = grandparent(n);

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

template<class T, class C>
void RBtree<T, C>::repare(RBtree<T, C> *n)
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
		RBtree<T, C> *g = grandparent(n);
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

template<class T, class C>
RBtree<T, C> *RBtree<T, C>::getpar(RBtree *n)
{
	if (n == NULL)
		return (NULL);
	return (n->parent);
}

template<class T, class C>
RBtree<T, C> *RBtree<T, C>::grandparent(RBtree *n)
{
	RBtree<T, C> *p = getpar(n);

	if (p == NULL)
		return (NULL);
	return(getpar(p));
}

template<class T, class C>
RBtree<T, C> *RBtree<T, C>::brother(RBtree *n)
{
	RBtree<T, C> *p = getpar(n);

	if (p == NULL)
		return (NULL);
	if (n == p->left)
		return (p->right);
	return (p->left);
}

template<class T, class C>
RBtree<T, C> *RBtree<T, C>::oncle(RBtree *n)
{
	RBtree<T, C> *p = getpar(n);
	RBtree<T, C> *gp = grandparent(n);

	if (gp == NULL)
		return(NULL);
	return (brother(p));
}

#endif