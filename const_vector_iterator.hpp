#ifndef C_VEC_ITER
#define C_VEC_ITER

namespace ft {template<class T> class vector_iterator;}
#include "vector_iterator.hpp"

namespace ft
{
template<class T>
class const_vector_iterator
{
    protected:
        const T*  ptr;
    public:
        typedef std::ptrdiff_t difference_type;
        typedef const T       value_type;
        typedef const T*      pointer;
        typedef const T&      reference;
        typedef std::random_access_iterator_tag iterator_category;

        const_vector_iterator();

        const_vector_iterator(const const_vector_iterator &cpy);
		const_vector_iterator(const ft::vector_iterator<T> &cpy);
        const_vector_iterator(pointer ptr);
        const_vector_iterator &operator=(const const_vector_iterator &rhs);
		const_vector_iterator &operator=(const ft::vector_iterator<T> &rhs);

        const_vector_iterator &operator++();
        const_vector_iterator operator++(int);
        const_vector_iterator &operator--();
        const_vector_iterator operator--(int);

        const_vector_iterator operator-(difference_type n) const;
        difference_type operator-(const const_vector_iterator &rhs) const;
        difference_type operator-(const ft::vector_iterator<T> &rhs) const;
        const_vector_iterator operator+(difference_type n) const;

        const_vector_iterator &operator+=(difference_type n);
        const_vector_iterator &operator-=(difference_type n);

		reference operator[](difference_type n) const;
		pointer operator->() const;
		reference operator*() const;

		bool operator==(const ft::vector_iterator<T> &rhs) const;
		bool operator!=(const ft::vector_iterator<T> &rhs) const;
		bool operator>(const ft::vector_iterator<T> &rhs) const;
		bool operator<(const ft::vector_iterator<T> &rhs) const;
        bool operator<=(const ft::vector_iterator<T> &rhs) const;
		bool operator>=(const ft::vector_iterator<T> &rhs) const;

		bool operator==(const ft::const_vector_iterator<T> &rhs) const;
		bool operator!=(const ft::const_vector_iterator<T> &rhs) const;
		bool operator>(const ft::const_vector_iterator<T> &rhs) const;
		bool operator<(const ft::const_vector_iterator<T> &rhs) const;
        bool operator<=(const ft::const_vector_iterator<T> &rhs) const;
		bool operator>=(const ft::const_vector_iterator<T> &rhs) const;
    
        pointer getptr() const;
};
}

template<class T>
ft::const_vector_iterator<T>::const_vector_iterator()
{
    this->ptr = NULL;
}

template<class T>
ft::const_vector_iterator<T>::const_vector_iterator(const_vector_iterator<T>::pointer ptr)
{
    this->ptr = ptr;
}

template <class T>
ft::const_vector_iterator<T>::const_vector_iterator(const const_vector_iterator<T> &cpy)
{
    *this = cpy;
    return ;
}

template <class T>
ft::const_vector_iterator<T>::const_vector_iterator(const vector_iterator<T> &cpy)
{
    this->ptr = cpy.getptr();
    return ;
}

template<class T>
ft::const_vector_iterator<T> &ft::const_vector_iterator<T>::operator=(const ft::const_vector_iterator<T> &rhs)
{
    this->ptr = rhs.getptr();
    return (*this);
}

template<class T>
ft::const_vector_iterator<T> &ft::const_vector_iterator<T>::operator=(const ft::vector_iterator<T> &rhs)
{
    this->ptr = rhs.getptr();
    return (*this);
}

template<class T>
ft::const_vector_iterator<T> &ft::const_vector_iterator<T>::operator++()
{
    (this->ptr)++;
    return (*this);
}

template<class T>
ft::const_vector_iterator<T> ft::const_vector_iterator<T>::operator++(int)
{
    const_vector_iterator tmp;

    tmp = *this;
    (this->ptr)++;
    return (tmp);
}

template<class T>
ft::const_vector_iterator<T> &ft::const_vector_iterator<T>::operator--()
{
    (this->ptr)--;
    return (*this);
}

template<class T>
ft::const_vector_iterator<T> ft::const_vector_iterator<T>::operator--(int)
{
    const_vector_iterator tmp;

    tmp = *this;
    (this->ptr)--;
    return (tmp);
}

template<class T>
typename ft::const_vector_iterator<T>::pointer ft::const_vector_iterator<T>::getptr() const
{
    return (this->ptr);
}

template<class T>
ft::const_vector_iterator<T> ft::const_vector_iterator<T>::operator+(difference_type n) const
{
    return (const_vector_iterator(this->ptr + n));
}

template<class T>
ft::const_vector_iterator<T> ft::const_vector_iterator<T>::operator-(difference_type n) const
{
    return (const_vector_iterator(this->ptr - n));
}

template<class T>
typename ft::const_vector_iterator<T>::difference_type ft::const_vector_iterator<T>::operator-(const ft::const_vector_iterator<T> &rhs) const
{
	return(this->getptr() - rhs.getptr());
}

template<class T>
typename ft::const_vector_iterator<T>::difference_type ft::const_vector_iterator<T>::operator-(const ft::vector_iterator<T> &rhs) const
{
	return(this->getptr() - rhs.getptr());
}

template<class T>
ft::const_vector_iterator<T> &ft::const_vector_iterator<T>::operator-=(difference_type n)
{
    this->ptr -= n;
    return (*this);
}

template<class T>
ft::const_vector_iterator<T> &ft::const_vector_iterator<T>::operator+=(difference_type n)
{
    this->ptr += n;
    return (*this);
}

template<class T>
typename ft::const_vector_iterator<T>::reference ft::const_vector_iterator<T>::operator[](difference_type n) const
{
	return (*(this->ptr + n));
}

template<class T>
typename ft::const_vector_iterator<T>::pointer ft::const_vector_iterator<T>::operator->() const
{
	return (std::__addressof(operator*()));
}

template<class T>
typename ft::const_vector_iterator<T>::reference ft::const_vector_iterator<T>::operator*() const
{
	return (*(this->ptr));
}

template<class T>
typename ft::const_vector_iterator<T>::difference_type operator-(const ft::const_vector_iterator<T> &lhs, const ft::const_vector_iterator<T> &rhs)
{
	return(lhs.getptr() - rhs.getptr());
}

template<class T>
typename ft::const_vector_iterator<T> operator+(typename ft::const_vector_iterator<T>::difference_type n, const ft::const_vector_iterator<T> &it)
{
	return (ft::const_vector_iterator<T>(it.getptr() + n));
}

template<class T>
bool ft::const_vector_iterator<T>::operator==(const ft::const_vector_iterator<T> &rhs) const
{
	return (this->getptr() == rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator!=(const ft::const_vector_iterator<T> &rhs) const
{
	return (this->getptr() != rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator>(const ft::const_vector_iterator<T> &rhs) const
{
	return (this->getptr() > rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator<(const ft::const_vector_iterator<T> &rhs) const
{
	return (this->getptr() < rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator>=(const ft::const_vector_iterator<T> &rhs) const
{
	return (this->getptr() >= rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator<=(const ft::const_vector_iterator<T> &rhs) const
{
	return (this->getptr() <= rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator==(const ft::vector_iterator<T> &rhs) const
{
	return (this->getptr() == rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator!=(const ft::vector_iterator<T> &rhs) const
{
	return (this->getptr() != rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator>(const ft::vector_iterator<T> &rhs) const
{
	return (this->getptr() > rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator<(const ft::vector_iterator<T> &rhs) const
{
	return (this->getptr() < rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator>=(const ft::vector_iterator<T> &rhs) const
{
	return (this->getptr() >= rhs.getptr());
}

template<class T>
bool ft::const_vector_iterator<T>::operator<=(const ft::vector_iterator<T> &rhs) const
{
	return (this->getptr() <= rhs.getptr());
}

#endif