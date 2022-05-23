#ifndef SET_HPP
#define SET_HPP
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "RBtree.hpp"
#include "set_iterator.hpp"
#include "set_const_iterator.hpp"

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
        typedef const ft::set_iterator<Key, Compare> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    
        //Constructor
    
        //set();
        explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
        explicit set (const Allocator &alloc);
        template<class InputIt>
        set(InputIt first, InputIt last, const key_compare &comp = Compare(), const allocator_type& alloc = allocator_type());

        //Insert

        ft::pair<iterator, bool> insert(const value_type &val);
        //Iterator

        iterator begin();
        iterator end();

        reverse_iterator rbegin();
        reverse_iterator rend();


    
        private:
            RBtre<Key, Compare> *tree;
            key_compare comp;
            size_t nb;
            allocator_type Alloc;

};
}

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

/*
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
*/


template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::iterator ft::set<Key, Compare, Allocator>::end()
{
	return(iterator(this->tree, true));
}

/*
template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::const_iterator ft::set<Key, Compare, Allocator>::end() const
{
	return(const_iterator(this->tree, true));
}
*/

template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::reverse_iterator ft::set<Key, Compare, Allocator>::rbegin()
{
	return (ft::reverse_iterator<typename ft::set<Key, Compare, Allocator>::iterator>(this->end()));
}

/*
template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::const_reverse_iterator ft::set<Key, Compare, Allocator>::rbegin() const
{
	return (ft::reverse_iterator<typename ft::set<Key, Compare, Allocator>::const_iterator>(this->end()));
}
*/
template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::reverse_iterator ft::set<Key, Compare, Allocator>::rend()
{
	return (ft::reverse_iterator<typename ft::set<Key, Compare, Allocator>::iterator>(this->begin()));
}

/*
template<class Key, class Compare, class Allocator>
typename ft::set<Key, Compare, Allocator>::const_reverse_iterator ft::set<Key, Compare, Allocator>::rend() const
{
	return (ft::reverse_iterator<typename ft::set<Key, Compare, Allocator>::const_iterator>(this->begin()));
}
*/
#endif