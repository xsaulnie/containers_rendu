#ifndef SET_HPP
#define SET_HPP
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "RBtree.hpp"
#include "set_iterator.hpp"
#include "const_set_iterator.hpp"

namespace ft
{
template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set
{
    public:
        typedef Key key_type;
        typedef Key value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Allocator allocator_type;
        typedef value_type & reference;
        typedef const value_type& const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef ft::set_iterator<Key, Compare> iterator;
        typedef ft::const_set_iterator<Key, Compare> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    
        //Constructor
    
        //set();
        explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
        explicit set (const Allocator &alloc);
        template<class InputIt>
        set(InputIt first, InputIt last, const key_compare &comp = Compare(), const allocator_type& alloc = allocator_type());
        set (const set &x);
        ~set();
        set &operator=(const set &x);

        //Insert

        ft::pair<iterator, bool> insert(const value_type &val);
        iterator insert (iterator position, const value_type& val);
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last);

        //Iterator

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        //Clear

        void clear();

        //Erase

        void erase(iterator position);
        size_type erase(const value_type &val);
        void erase(iterator first, iterator last);

        //Swap

        void swap(set &x);

        //Capacity

        bool empty() const;
        size_type size() const;
        size_type max_size() const;

        //Observers

        key_compare key_comp() const;
        value_compare value_comp() const;

        //Operation

        iterator find (const value_type& val) const;
        size_type count (const key_type& k) const;
        iterator lower_bound (const value_type& val) const;
        iterator upper_bound (const value_type& val) const;
        ft::pair<iterator,iterator> equal_range (const value_type& val) const;

        //Allocator

        allocator_type get_allocator() const;

        private:
            RBtre<Key, Compare> *tree;
            key_compare comp;
            size_t nb;
            allocator_type Alloc;

};

template<class Key, class Compare, class Allocator>
void swap(ft::set<Key, Compare, Allocator> &lhs, ft::set<Key, Compare, Allocator> &rhs);
template<class Key, class Compare, class Allocator>
bool operator==(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs);
template<class Key, class Compare, class Allocator>
bool operator!=(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs);
template<class Key, class Compare, class Allocator>
bool operator<(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs);
template<class Key, class Compare, class Allocator>
bool operator>(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs);
template<class Key, class Compare, class Allocator>
bool operator>=(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs);
template<class Key, class Compare, class Allocator>
bool operator<=(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs);
}

//Constructor

template<class Key, class Compare, class Allocator>
ft::set<Key, Compare, Allocator>::set(const ft::set<Key, Compare, Allocator>::key_compare &comp, const ft::set<Key, Compare, Allocator>::allocator_type &alloc)
{
	this->tree = NULL;
	this->nb = 0;
    this->Alloc = alloc;
    this->comp = comp;
}

template<class Key, class Compare, class Allocator>
ft::set<Key, Compare, Allocator>::set(const Allocator &alloc)
{
	this->tree = NULL;
	this->nb = 0;
    this->Alloc = alloc;
}

template<class Key, class Compare, class Allocator>
template<class InputIt>
ft::set<Key, Compare, Allocator>::set(InputIt first, InputIt last, const ft::set<Key, Compare, Allocator>::key_compare &comp, const ft::set<Key, Compare, Allocator>::allocator_type &alloc)
{
    this->comp = comp;
    this->Alloc = alloc;
	this->tree = NULL;
	this->nb = 0;

	while (first != last)
	{
		this->insert(*first);
		first++;
	}
}

template<class Key, class Compare, class Allocator>
ft::set<Key, Compare, Allocator>::set(const set &other)
{
	size_t cmp;
	ft::set<Key, Compare, Allocator>::const_iterator st = other.begin();
	ft::set<Key, Compare, Allocator>::const_iterator en = other.end();
	Key tmp;

	cmp = 0;
	this->tree = NULL;
	while (st != en)
	{
		tmp = *st;
		this->insert(tmp);
		st++;
		cmp++;
	}
	this->nb = cmp;
	this->comp = other.key_comp();
	this->Alloc = other.get_allocator();
}

template<class Key, class Compare, class Allocator>
ft::set<Key, Compare, Allocator>::~set()
{
	this->clear();
}

template<class Key, class Compare, class Allocator>
ft::set<Key, Compare, Allocator> &ft::set<Key,Compare, Allocator>::operator=(const ft::set<Key, Compare, Allocator> &x)
{
	this->clear();
	ft::set<Key, Compare, Allocator>::const_iterator fs = x.begin();
	ft::set<Key, Compare, Allocator>::const_iterator ls = x.end();

	if (fs == ls)
	{
		this->tree = NULL;
		this->nb = 0;
	}

	while (fs != ls)
	{
		this->insert(*fs);
		fs++;
	}
	this->nb = x.size();
	this->Alloc = x.get_allocator();
	this->comp = x.key_comp();
	return (*this);
}

//Iterator

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::iterator ft::set<Key, Compare, Allocator>::begin()
{
	RBtre<Key, Compare> *cur;

	cur = this->tree;

	if (this->tree == NULL)
	{
		return(iterator(cur, true));
	}
	cur = cur->getrac(cur);
	while (cur->left != NULL)
		cur = cur->left;
	return (iterator(cur));
}


template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::const_iterator ft::set<Key, Compare, Allocator>::begin() const
{
	RBtre<Key, Compare> *cur;

	cur = this->tree;

	if (this->tree == NULL)
	{
		return(const_iterator(cur, true));
	}
	cur = cur->getrac(cur);
	while (cur->left != NULL)
		cur = cur->left;
	return (const_iterator(cur));
}



template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::iterator ft::set<Key, Compare, Allocator>::end()
{
	return(iterator(this->tree, true));
}


template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::const_iterator ft::set<Key, Compare, Allocator>::end() const
{
	return(const_iterator(this->tree, true));
}


template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::reverse_iterator ft::set<Key, Compare, Allocator>::rbegin()
{
	return (ft::reverse_iterator<typename ft::set<Key, Compare, Allocator>::iterator>(this->end()));
}


template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::const_reverse_iterator ft::set<Key, Compare, Allocator>::rbegin() const
{
	return (ft::reverse_iterator<typename ft::set<Key, Compare, Allocator>::const_iterator>(this->end()));
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::reverse_iterator ft::set<Key, Compare, Allocator>::rend()
{
	return (ft::reverse_iterator<typename ft::set<Key, Compare, Allocator>::iterator>(this->begin()));
}


template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::const_reverse_iterator ft::set<Key, Compare, Allocator>::rend() const
{
	return (ft::reverse_iterator<typename ft::set<Key, Compare, Allocator>::const_iterator>(this->begin()));
}


//Insert

template<class Key, class Compare, class Allocator>
typename ft::pair<typename ft::set<Key, Compare, Allocator>::iterator, bool> ft::set<Key, Compare, Allocator>::insert(const ft::set<Key, Compare, Allocator>::value_type &value)
{

	RBtre <Key, Compare> *test = this->tree->search(this->tree, value, this->comp);
	if (test != NULL)
		return (ft::pair<typename ft::set<Key, Compare, Allocator>::iterator, bool>(iterator(test), false));
	RBtre <Key, Compare> *n = this->tree->RBval(value, this->Alloc);
	this->tree = this->tree->insert(this->tree, n, this->comp);
	this->nb++;

	RBtre <Key, Compare> *ret = this->tree->search(this->tree, value, this->comp);
	return (ft::pair<typename ft::set<Key, Compare, Allocator>::iterator, bool>(iterator(ret), true));
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::iterator ft::set<Key, Compare, Allocator>::insert(typename ft::set<Key, Compare, Allocator>::iterator hint, const value_type& value)
{
	(void)hint;
	RBtre <Key, Compare> *test = this->tree->search(this->tree, value, this->comp);
	if (test != NULL)
		return (iterator(test));
	RBtre <Key, Compare> *n = this->tree->RBval(value, this->Alloc);
	this->tree = this->tree->insert(this->tree, n, this->comp);
	this->nb++;

	RBtre <Key, Compare> *ret = this->tree->search(this->tree, value, this->comp);
	return (iterator(ret));
}

template<class Key, class Compare, class Allocator>
template <class InputIterator>
void ft::set<Key, Compare, Allocator>::insert(InputIterator first, InputIterator last)
{
	while (first != last)
	{
		this->insert(*first);
		first++;
	}
}

//Clear

template<class Key, class Compare, class Allocator>
void ft::set<Key, Compare, Allocator>::clear()
{
	if (this->tree == NULL)
		return ;
	this->tree->clear(this->tree, this->Alloc);
	this->nb = 0;
	this->tree = NULL;	
}

//Erase

template<class Key, class Compare, class Allocator>
void ft::set<Key, Compare, Allocator>::erase(ft::set<Key, Compare, Allocator>::iterator position)
{
	bool erased;

	if (this->nb == 0)
		return ;
	if (position.getsen())
		return ;
	this->tree = this->tree->vanish(this->tree, *position, erased, this->comp, this->Alloc);
	if (erased)
		this->nb--;
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::size_type ft::set<Key, Compare, Allocator>::erase(const ft::set<Key, Compare, Allocator>::key_type &k)
{
	bool erased;

	if (this->nb == 0)
		return (0);
	this->tree = this->tree->vanish(this->tree, k, erased, this->comp, this->Alloc);
	if (erased)
	{
		this->nb--;
		return (1);
	}
	return (0);
}

//why cpy ?

template<class Key, class Compare, class Allocator>
void ft::set<Key, Compare, Allocator>::erase(ft::set<Key, Compare, Allocator>::iterator first, ft::set<Key, Compare, Allocator>::iterator last)
{
	ft::set<Key, Compare, Allocator> cpy;
	bool erased;

	cpy = *this;

	while (first != last)
	{
		if(!first.getsen())
		{
			cpy.tree = cpy.tree->vanish(cpy.tree, *first, erased, cpy.comp, cpy.Alloc);
			if (erased)
				cpy.nb--;
		}
		first++;
	}
	*this = cpy;
	cpy.clear();
}

//Swap

template<class Key, class Compare, class Allocator>
void ft::set<Key, Compare, Allocator>::swap(ft::set<Key, Compare, Allocator> &x)
{
	RBtre<Key, Compare> *tree_tmp;
	key_compare comp_tmp;
	size_t nb_tmp;
	allocator_type Alloc_tmp;

	tree_tmp = this->tree;
	comp_tmp = this->comp;
	nb_tmp = this->nb;
	Alloc_tmp = this->Alloc;

	this->tree = x.tree;
	this->comp = x.key_comp();
	this->nb = x.size();
	this->Alloc = x.get_allocator();

	x.tree = tree_tmp;
	x.comp = comp_tmp;
	x.nb = nb_tmp;
	x.Alloc = Alloc_tmp;
}

template<class Key, class Compare, class Allocator>
void ft::swap(ft::set<Key, Compare, Allocator> &lhs, ft::set<Key, Compare, Allocator> &rhs)
{
	lhs.swap(rhs);
}

//Capacity

template<class Key, class Compare, class Allocator>
bool ft::set<Key, Compare, Allocator>::empty() const
{
	if (this->nb == 0)
		return (true);
	return (false);
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::size_type ft::set<Key, Compare, Allocator>::size() const
{
	return(this->nb);
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::size_type ft::set<Key, Compare, Allocator>::max_size() const
{
	size_t res;
	unsigned long long int p;
	size_t n;

	n = 63;
	p = 1;
	while (n)
	{
		p *=2;
		n--;
	}

	res = ((p / (sizeof(typename ft::set<Key, Compare, Allocator>::value_type))) - 1);
	return (res);
}

//Observeurs

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::key_compare ft::set<Key, Compare, Allocator>::key_comp() const
{
	return (this->comp);	
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::value_compare ft::set<Key, Compare, Allocator>::value_comp() const
{
	return (this->comp);
}

//Operations

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::iterator ft::set<Key, Compare, Allocator>::find(const typename ft::set<Key, Compare, Allocator>::value_type &val) const
{
	RBtre<Key, Compare> *test = this->tree->search(this->tree, val, this->comp);

	if (test == NULL)
		return (iterator(this->tree, true));
	return (iterator(test));
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::size_type ft::set<Key, Compare, Allocator>::count(const typename ft::set<Key, Compare, Allocator>::value_type &val) const
{
	RBtre<Key, Compare> *test = this->tree->search(this->tree, val, this->comp);

	if (test == NULL)
		return (0);
	return (1);
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::iterator ft::set<Key, Compare, Allocator>::upper_bound(const typename ft::set<Key, Compare, Allocator>::value_type &val) const
{
	typename ft::set<Key, Compare, Allocator>::const_iterator it;
	typename ft::set<Key, Compare, Allocator>::const_iterator end;
	typename ft::set<Key, Compare, Allocator>::const_iterator found;

	end = this->end();
	found = this->find(val);
	if (found != end)
		return (iterator(++found));
	it = this->begin();
	while (it != end)
	{
		if ((this->comp)(val, *it) == true)
			return(iterator(it));
		it++;
	}
	return (iterator(this->tree, true));
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::iterator ft::set<Key, Compare, Allocator>::lower_bound(const typename ft::set<Key, Compare, Allocator>::value_type &val) const
{
	typename ft::set<Key, Compare, Allocator>::const_iterator it;
	typename ft::set<Key, Compare, Allocator>::const_iterator end;
	typename ft::set<Key, Compare, Allocator>::const_iterator found;

	end = this->end();
	found = this->find(val);
	if (found != end)
		return (iterator(found));

	it = this->begin();
	while (it != end)
	{
		if ((this->comp)(*it, val) == false)
			return (iterator(it));
		it++;
	}
	return (iterator(this->tree, true));
}

template<class Key, class Compare, class Allocator>
ft::pair<typename ft::set<Key, Compare, Allocator>::iterator, typename ft::set<Key, Compare, Allocator>::iterator> ft::set<Key, Compare, Allocator>::equal_range(const typename ft::set<Key, Compare, Allocator>::value_type &val) const
{
	return (ft::make_pair<typename ft::set<Key, Compare, Allocator>::iterator, typename ft::set<Key, Compare, Allocator>::iterator>(this->lower_bound(val), this->upper_bound(val)));
}

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::allocator_type ft::set<Key, Compare, Allocator>::get_allocator() const
{
	return (this->Alloc);
}

//Comparaison Operators

template<class Key, class Compare, class Allocator>
bool ft::operator==(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
		return (true);
	return (false);
}

template<class Key, class Compare, class Allocator>
bool ft::operator!=(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs)
{
	if (lhs == rhs)
		return (false);
	return (true);
}

template<class Key, class Compare, class Allocator>
bool ft::operator<(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs)
{
	if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
		return (true);
	return (false);
}

template<class Key, class Compare, class Allocator>
bool ft::operator>(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs)
{
	if (lhs == rhs)
		return (false);
	if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
		return (false);
	return (true);
}

template<class Key, class Compare, class Allocator>
bool ft::operator>=(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs)
{
	if (lhs == rhs)
		return (true);
	if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
		return (false);
	return (true);
}

template<class Key, class Compare, class Allocator>
bool ft::operator<=(const ft::set<Key, Compare, Allocator> &lhs, const ft::set<Key, Compare, Allocator> &rhs)
{
	if (lhs == rhs)
		return (true);
	if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
		return (true);
	return (false);
}
#endif