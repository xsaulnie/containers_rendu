#ifndef VEC_ITER
#define VEC_ITER

namespace ft {template<class T> class const_vector_iterator;}
#include "const_vector_iterator.hpp"

namespace ft
{
template<class T>
class vector_iterator
{
    protected:
        T*  ptr;
    public:
        typedef size_t difference_type;
        typedef T       value_type;
        typedef T*      pointer;
        typedef T&      reference;
        typedef std::random_access_iterator_tag iterator_category;

        vector_iterator();
        vector_iterator(pointer ptr);
        vector_iterator(const vector_iterator &cpy);
        vector_iterator &operator=(const vector_iterator &rhs);

        vector_iterator &operator++();
        vector_iterator operator++(int);
        vector_iterator &operator--();
        vector_iterator operator--(int);

        vector_iterator operator-(difference_type n) const;
        vector_iterator operator+(difference_type n) const;

        vector_iterator &operator+=(difference_type n);
        vector_iterator &operator-=(difference_type n);

		reference operator[](difference_type n) const;
		pointer operator->() const;
		reference operator*() const;
	
		bool operator==(const ft::const_vector_iterator<T> &rhs) const;
		bool operator!=(const ft::const_vector_iterator<T> &rhs) const;
		bool operator==(const ft::vector_iterator<T> &rhs) const;
		bool operator!=(const ft::vector_iterator<T> &rhs) const;
	
        pointer getptr() const;

};
}

template<class T>
ft::vector_iterator<T>::vector_iterator()
{
    this->ptr = NULL;
}

template<class T>
ft::vector_iterator<T>::vector_iterator(vector_iterator<T>::pointer ptr)
{
    this->ptr = ptr;
}

template <class T>
ft::vector_iterator<T>::vector_iterator(const vector_iterator<T> &cpy)
{
    *this = cpy;
    return ;
}

template<class T>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator=(const ft::vector_iterator<T> &rhs)
{
    this->ptr = rhs.getptr();
    return (*this);
}

template<class T>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator++()
{
    (this->ptr)++;
    return (*this);
}

template<class T>
ft::vector_iterator<T> ft::vector_iterator<T>::operator++(int)
{
    vector_iterator tmp;

    tmp = *this;
    (this->ptr)++;
    return (tmp);
}

template<class T>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator--()
{
    (this->ptr)--;
    return (*this);
}

template<class T>
ft::vector_iterator<T> ft::vector_iterator<T>::operator--(int)
{
    vector_iterator tmp;

    tmp = *this;
    (this->ptr)--;
    return (tmp);
}

template<class T>
typename ft::vector_iterator<T>::pointer ft::vector_iterator<T>::getptr() const
{
    return (this->ptr);
}

template<class T>
ft::vector_iterator<T> ft::vector_iterator<T>::operator+(difference_type n) const
{
    return (vector_iterator(this->ptr + n));
}

template<class T>
ft::vector_iterator<T> ft::vector_iterator<T>::operator-(difference_type n) const
{
    return (vector_iterator(this->ptr - n));
}

template<class T>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator-=(difference_type n)
{
    this->ptr -= n;
    return (*this);
}

template<class T>
ft::vector_iterator<T> &ft::vector_iterator<T>::operator+=(difference_type n)
{
    this->ptr += n;
    return (*this);
}

template<class T>
typename ft::vector_iterator<T>::reference ft::vector_iterator<T>::operator[](difference_type n) const
{
	return (*(this->ptr + n));
}

template<class T>
typename ft::vector_iterator<T>::pointer ft::vector_iterator<T>::operator->() const
{
	return (std::__addressof(operator*()));
}

template<class T>
typename ft::vector_iterator<T>::reference ft::vector_iterator<T>::operator*() const
{
	return (*(this->ptr));
}

template<class T>
typename ft::vector_iterator<T>::difference_type operator-(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<T> &rhs)
{
	return(lhs.getptr() - rhs.getptr());
}

template<class T>
typename ft::vector_iterator<T> operator+(typename ft::vector_iterator<T>::difference_type n, const ft::vector_iterator<T> &it)
{
	return (ft::vector_iterator<T>(it.getptr() + n));
}

template<class T>
bool operator==(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<T> &rhs)
{
	return (lhs.getptr() == rhs.getptr());
}

template<class T>
bool operator!=(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<T> &rhs)
{
	return (lhs.getptr() != rhs.getptr());
}

template<class T>
bool ft::vector_iterator<T>::operator==(const ft::const_vector_iterator<T> &rhs) const
{
	return (this->getptr() == rhs.getptr());
}

template<class T>
bool ft::vector_iterator<T>::operator!=(const ft::const_vector_iterator<T> &rhs) const
{
	return (this->getptr() != rhs.getptr());
}

template<class T>
bool ft::vector_iterator<T>::operator==(const ft::vector_iterator<T> &rhs) const
{
	return (this->getptr() == rhs.getptr());
}

template<class T>
bool ft::vector_iterator<T>::operator!=(const ft::vector_iterator<T> &rhs) const
{
	return (this->getptr() != rhs.getptr());
}

template<class T>
bool operator<(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<T> &rhs)
{
	return (lhs.getptr() < rhs.getptr());
}

template<class T>
bool operator>(const ft::vector_iterator<T> &lhs, const ft::vector_iterator<T> &rhs)
{
	return (lhs.getptr() > rhs.getptr());
}


#endif