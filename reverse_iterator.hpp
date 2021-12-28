#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator>
#include "iterator_traits.hpp"

namespace ft {
    template <class _Iter>
    class reverse_iterator
        : public std::iterator<typename ft::iterator_traits<_Iter>::iterator_category,
                               typename ft::iterator_traits<_Iter>::value_type,
                               typename ft::iterator_traits<_Iter>::difference_type,
                               typename ft::iterator_traits<_Iter>::pointer,
                               typename ft::iterator_traits<_Iter>::reference>
    {
    protected:
        _Iter current;

    public:
        typedef _Iter                                                  iterator_type;
        typedef typename ft::iterator_traits<_Iter>::difference_type   difference_type;
        typedef typename ft::iterator_traits<_Iter>::reference         reference;
        typedef typename ft::iterator_traits<_Iter>::pointer           pointer;
        typedef typename ft::iterator_traits<_Iter>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<_Iter>::value_type        value_type;

        reverse_iterator() : current()
        {}
        explicit reverse_iterator(_Iter __x) : current(__x)
        {}
        template <class _Up>
        reverse_iterator(const reverse_iterator<_Up>& __u)
            : current(__u.base())
        {}
        template <class _Up>
        reverse_iterator& operator=(const reverse_iterator<_Up>& __u)
        {
            current = __u.base();
            return *this;
        }

        _Iter base() const
        {
            return current;
        }
        reference operator*() const
        {
            _Iter __tmp = current;
            return *--__tmp;
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        reverse_iterator& operator++()
        {
            --current;
            return *this;
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator __tmp(*this);
            --current;
            return __tmp;
        }
        reverse_iterator& operator--()
        {
            ++current;
            return *this;
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator __tmp(*this);
            ++current;
            return __tmp;
        }
        reverse_iterator operator+(difference_type __n) const
        {
            return reverse_iterator(current - __n);
        }
        reverse_iterator& operator+=(difference_type __n)
        {
            current -= __n;
            return *this;
        }
        reverse_iterator operator-(difference_type __n) const
        {
            return reverse_iterator(current + __n);
        }
        reverse_iterator& operator-=(difference_type __n)
        {
            current += __n;
            return *this;
        }
        reference operator[](difference_type __n) const
        {
            return *(*this + __n);
        }
    };

    template <class _Iter1, class _Iter2>
    inline bool operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
    {
        return __x.base() == __y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool operator<(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
    {
        return __x.base() > __y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool operator!=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
    {
        return __x.base() != __y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool operator>(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
    {
        return __x.base() < __y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool operator>=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
    {
        return __x.base() <= __y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool operator<=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
    {
        return __x.base() >= __y.base();
    }

    template <class _Iter1, class _Iter2>
    inline typename reverse_iterator<_Iter1>::difference_type
    operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
    {
        return __y.base() - __x.base();
    }

    template <class _Iter>
    inline reverse_iterator<_Iter>
    operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter>& __x)
    {
        return reverse_iterator<_Iter>(__x.base() - __n);
    }
}

#endif /* REVERSE_ITERATOR_HPP */
