#ifndef SET_ITER
#define SET_ITER

#include "RBtree.hpp"
#include "stdlib.h"
namespace ft {template<class T, class C> class const_set_iterator;}
#include "const_set_iterator.hpp"

namespace ft
{
template<class T, class C>
class set_iterator
{
	protected:
		RBtree<T, C>         *cur;
		bool				sentinel;

	public:
		typedef size_t difference_type;
		typedef T value_type;
		typedef const T * pointer;
		typedef const T & reference;
		typedef std::bidirectional_iterator_tag iterator_category;
	 
		set_iterator();
		set_iterator(RBtree<T, C> *init);
		set_iterator(RBtree<T, C> *iend, bool sen);
        set_iterator(const ft::const_set_iterator<T, C> &cpy);

		set_iterator &operator++();
		set_iterator operator++(int);
		set_iterator &operator--();
		set_iterator operator--(int);
		const T &operator*() const;
		const  T*operator->() const;

		RBtree<T, C> *getcur() const;
		bool getsen() const;
		class Badoperation : public std::exception // le vrai ne segault pas
		{
			public:
				virtual const char *what() const throw()
				{
						return ("Bad operation on set iterator");
				}
		};
		bool operator==(const ft::const_set_iterator<T, C> &rhs) const;
		bool operator!=(const ft::const_set_iterator<T, C> &rhs) const;

};

template<class T, class C>
bool operator==(ft::set_iterator<T, C> &lhs, ft::set_iterator<T, C> &rhs);
template<class T, class C>
bool operator==(const ft::set_iterator<T, C> &lhs, const ft::set_iterator<T, C> &rhs);
template<class T, class C>
bool operator!=(ft::set_iterator<T, C> &lhs, ft::set_iterator<T, C> &rhs);
template<class T, class C>
bool operator!=(const ft::set_iterator<T, C> &lhs, const ft::set_iterator<T, C> &rhs);
}

template<class T, class C>
RBtree<T, C> *ft::set_iterator<T, C>::getcur() const
{
	return (this->cur);
}

template<class T, class C>
bool ft::set_iterator<T, C>::getsen() const
{
	return (this->sentinel);
}

template<class T, class C>
const T *ft::set_iterator<T, C>::operator->() const
{
	return (std::__addressof(operator*()));
}

template<class T, class C>
ft::set_iterator<T, C>::set_iterator(RBtree<T, C> *iend, bool sen)
{
	if (sen == false)
	{
		this->cur = NULL;
		this->sentinel = false;
		return ;
	}
	if (sen == true)
	{
		if (iend == NULL)
		{
			this->cur = NULL;
			this->sentinel = true;
			return ; 
		}
		while(iend->parent != NULL)
			iend = iend->parent;
		while (iend->right != NULL)
			iend = iend->right;
		this->cur = iend;
		this->sentinel = true;
	}
}

template<class T, class C>
ft::set_iterator<T, C>::set_iterator()
{
	this->cur = NULL;
	this->sentinel = false;
}

template<class T, class C>
ft::set_iterator<T, C>::set_iterator(const ft::const_set_iterator<T, C> &cpy)
{
	this->cur = cpy.getcur();
	this->sentinel = cpy.getsen();
}

template<class T, class C>
ft::set_iterator<T, C>::set_iterator(RBtree<T, C> *init)
{
	this->cur = init;
	this->sentinel = false;
}

template<class T, class C>
const T &ft::set_iterator<T, C>::operator*() const
{
	if (this->sentinel == true)
		throw (Badoperation());
	return (*(this->cur->p));
}

template<class T, class C>
ft::set_iterator<T, C> &ft::set_iterator<T, C>::operator++()
{
	RBtree<T, C> *res;
	C comp;

	if (this->sentinel == true)
		throw (Badoperation());

	if (this->cur->right != NULL)
	{
		res = this->cur->right;
		while (res->left != NULL)
		{
			res = res->left;
		}
		this->cur = res;
		return (*this);
	}

	if (this->cur->parent == NULL)
	{
		this->sentinel = 1;
		return (*this);
	} 
	res = this->cur->parent;
	while (!comp(*(this->cur->p), *(res->p)))
	{
		res = res->parent;
		if (res == NULL)
		{
			this->sentinel = 1;
			return (*this);
		}
	}
	this->cur = res;
	return (*this);
}

template<class T, class C>
ft::set_iterator<T, C> ft::set_iterator<T, C>::operator++(int)
{
	RBtree<T, C> *res;
	set_iterator tmp;
	C comp;

	if (this->sentinel == true)
		throw (Badoperation());

	tmp = *this;
	if (this->cur->right != NULL)
	{
		res = this->cur->right;
		while (res->left != NULL)
			res = res->left;
		this->cur = res;
		return (tmp);
	}

	if (this->cur->parent == NULL)
	{
		this->sentinel = 1;
		return (tmp);
	} 
	res = this->cur->parent;
	while (!comp(*(this->cur->p), *(res->p)))
	{
		res = res->parent;
		if (res == NULL)
		{
			this->sentinel = 1;
			return (tmp);
		}
	}
	this->cur = res;
	return (tmp);
}

template<class T, class C>
ft::set_iterator<T, C> ft::set_iterator<T, C>::operator--(int)
{
	RBtree<T, C> *res;
	set_iterator tmp;
	C comp;

	tmp = *this;
	if (this->sentinel == true)
	{
		res = cur;
		while(res->parent != NULL)
			res = res->parent;
		while (res->right != NULL)
			res = res->right;
		this->cur = res;
		this->sentinel = false;
		return (tmp);
	}

	if (this->cur->left != NULL)
	{
		res = this->cur->left;
		while (res->right != NULL)
		{
			res = res->right;
		}
		this->cur = res;
		return (tmp);
	}

	if (this->cur->parent == NULL)
		throw (Badoperation());
	res = this->cur->parent;
	while (comp(*(this->cur->p), *(res->p)))
	{
		res = res->parent;
		if (res == NULL)
		{
			throw (Badoperation());
		}
	}
	this->cur = res;
	return (tmp);
}

template<class T, class C>
ft::set_iterator<T, C> &ft::set_iterator<T, C>::operator--()
{
	RBtree<T, C> *res;
	C comp;

	if (this->sentinel == true)
	{
		res = cur;
		while(res->parent != NULL)
			res = res->parent;
		while (res->right != NULL)
			res = res->right;
		this->cur = res;
		this->sentinel = false;
		return (*this);
	}

	if (this->cur->left != NULL)
	{
		res = this->cur->left;
		while (res->right != NULL)
		{
			res = res->right;
		}
		this->cur = res;
		return (*this);
	}

	if (this->cur->parent == NULL)
		throw (Badoperation());
	res = this->cur->parent;
	while (comp(*(this->cur->p), *(res->p)))
	{
		res = res->parent;
		if (res == NULL)
		{
			throw (Badoperation());
		}
	}
	this->cur = res;
	return (*this);
}

template<class T, class C>
bool ft::operator!=(ft::set_iterator<T, C> &lhs, ft::set_iterator<T, C> &rhs)
{
	if (lhs.getsen() != rhs.getsen())
		return (true);
	if (lhs.getsen() == true)
		return (false);
	if (lhs.getcur() != rhs.getcur())
		return (true);
	return (false);
}

template<class T, class C>
bool ft::operator==(ft::set_iterator<T, C> &lhs, ft::set_iterator<T, C> &rhs)
{
	if (lhs.getsen() != rhs.getsen())
		return (false);
	if (lhs.getsen() == true && rhs.getsen() == true)
		return (true);
	if (lhs.getcur() == rhs.getcur())
		return (true);
	return (false);
}

template<class T, class C>
bool ft::operator!=(const ft::set_iterator<T, C> &lhs, const ft::set_iterator<T, C> &rhs)
{
	if (lhs.getsen() != rhs.getsen())
		return (true);
	if (lhs.getsen() == true)
		return (false);
	if (lhs.getcur() != rhs.getcur())
		return (true);
	return (false);
}

template<class T, class C>
bool ft::operator==(const ft::set_iterator<T, C> &lhs, const ft::set_iterator<T, C> &rhs)
{
	if (lhs.getsen() != rhs.getsen())
		return (false);
	if (lhs.getsen() == true && rhs.getsen() == true)
		return (true);
	if (lhs.getcur() == rhs.getcur())
		return (true);
	return (false);
}

template<class T, class C>
bool ft::set_iterator<T, C>::operator==(const ft::const_set_iterator<T, C> &rhs) const
{
	if (this->getsen() != rhs.getsen())
		return (false);
	if (this->getsen() == true && rhs.getsen() == true)
		return (true);
	if (this->getcur() == rhs.getcur())
		return (true);
	return (false);
}

template<class T, class C>
bool ft::set_iterator<T, C>::operator!=(const ft::const_set_iterator<T, C> &rhs) const
{
	if (this->getsen() != rhs.getsen())
		return (true);
	if (this->getsen() == true)
		return (false);
	if (this->getcur() != rhs.getcur())
		return (true);
	return (false);
}

#endif