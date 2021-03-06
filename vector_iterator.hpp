#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>
#include "iterator_traits.hpp"

namespace ft {
    template <class _Iter>
    class vector_iterator : public std::iterator<std::random_access_iterator_tag, _Iter>
    {
    public:
        typedef _Iter                                                          iterator_type;
        typedef typename ft::iterator_traits<iterator_type>::value_type        value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type   difference_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer           pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference         reference;
        typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;

    private:
        iterator_type __i;

    public:
        vector_iterator()
            : __i(NULL)
        {}
        explicit vector_iterator(pointer __x)
            : __i(__x)
        {}
        template <class _T>
        vector_iterator(const vector_iterator<_T>& __x)
            : __i(__x.base())
        {}
        template <class _T>
        vector_iterator& operator=(const vector_iterator<_T>& __x)
        {
            __i = __x.base();
            return *this;
        }
        ~vector_iterator()
        {}

        reference operator*() const
        {
            return *__i;
        }
        pointer operator->() const
        {
            return __i;
        }
        vector_iterator& operator++()
        {
            ++__i;
            return *this;
        }
        vector_iterator operator++(int)
        {
            vector_iterator __tmp(*this);
            ++(*this);
            return __tmp;
        }
        vector_iterator& operator--()
        {
            --__i;
            return *this;
        }
        vector_iterator operator--(int)
        {
            vector_iterator __tmp(*this);
            --(*this);
            return __tmp;
        }
        vector_iterator operator+(difference_type __n) const
        {
            vector_iterator __w(*this);
            __w += __n;
            return __w;
        }
        vector_iterator& operator+=(difference_type __n)
        {
            __i += __n;
            return *this;
        }
        vector_iterator operator-(difference_type __n) const
        {
            return *this + (-__n);
        }
        vector_iterator& operator-=(difference_type __n)
        {
            *this += -__n;
            return *this;
        }

        reference operator[](difference_type __n) const
        {
            return __i[__n];
        }

        iterator_type base() const
        {
            return __i;
        }
    };

    template <class _Iter>
    bool operator==(const vector_iterator<_Iter>& __x, const vector_iterator<_Iter>& __y)
    {
        return __x.base() == __y.base();
    }
    template <class _Iter1, class _Iter2>
    bool operator==(const vector_iterator<_Iter1>& __x, const vector_iterator<_Iter2>& __y)
    {
        return __x.base() == __y.base();
    }

    template <class _Iter>
    bool operator<(const vector_iterator<_Iter>& __x, const vector_iterator<_Iter>& __y)
    {
        return __x.base() < __y.base();
    }
    template <class _Iter1, class _Iter2>
    bool operator<(const vector_iterator<_Iter1>& __x, const vector_iterator<_Iter2>& __y)
    {
        return __x.base() < __y.base();
    }

    template <class _Iter>
    bool operator!=(const vector_iterator<_Iter>& __x, const vector_iterator<_Iter>& __y)
    {
        return !(__x == __y);
    }
    template <class _Iter1, class _Iter2>
    bool operator!=(const vector_iterator<_Iter1>& __x, const vector_iterator<_Iter2>& __y)
    {
        return !(__x == __y);
    }

    template <class _Iter>
    bool operator>(const vector_iterator<_Iter>& __x, const vector_iterator<_Iter>& __y)
    {
        return __y < __x;
    }
    template <class _Iter1, class _Iter2>
    bool operator>(const vector_iterator<_Iter1>& __x, const vector_iterator<_Iter2>& __y)
    {
        return __y < __x;
    }

    template <class _Iter>
    bool operator>=(const vector_iterator<_Iter>& __x, const vector_iterator<_Iter>& __y)
    {
        return !(__x < __y);
    }
    template <class _Iter1, class _Iter2>
    bool operator>=(const vector_iterator<_Iter1>& __x, const vector_iterator<_Iter2>& __y)
    {
        return !(__x < __y);
    }

    template <class _Iter>
    bool operator<=(const vector_iterator<_Iter>& __x, const vector_iterator<_Iter>& __y)
    {
        return !(__y < __x);
    }
    template <class _Iter1, class _Iter2>
    bool operator<=(const vector_iterator<_Iter1>& __x, const vector_iterator<_Iter2>& __y)
    {
        return !(__y < __x);
    }

    template <class _Iter1, class _Iter2>
    typename vector_iterator<_Iter1>::difference_type operator-(const vector_iterator<_Iter1>& __x, const vector_iterator<_Iter2>& __y)
    {
        return __x.base() - __y.base();
    }

    template <class _Iter>
    vector_iterator<_Iter> operator+(typename vector_iterator<_Iter>::difference_type __n, vector_iterator<_Iter> __x)
    {
        __x += __n;
        return __x;
    }
}

#endif /* VECTOR_ITERATOR_HPP */
