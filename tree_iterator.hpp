#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iterator>
#include "iterator_traits.hpp"

namespace ft {
    template <class _Iter>
    class tree_iterator : public std::iterator<std::bidirectional_iterator_tag, _Iter>
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
        tree_iterator()
            : __i(NULL)
        {}
        explicit tree_iterator(pointer __x)
            : __i(__x)
        {}
        template <class _T>
        tree_iterator(const tree_iterator<_T>& __x)
            : __i(__x.base())
        {}
        template <class _T>
        tree_iterator& operator=(const tree_iterator<_T>& __x)
        {
            __i = __x.base();
            return *this;
        }
        ~tree_iterator()
        {}

        reference operator*() const
        {
            return *__i;
        }
        pointer operator->() const
        {
            return __i;
        }
        tree_iterator& operator++()
        {
            ++__i;
            return *this;
        }
        tree_iterator operator++(int)
        {
            tree_iterator __tmp(*this);
            ++(*this);
            return __tmp;
        }
        tree_iterator& operator--()
        {
            --__i;
            return *this;
        }
        tree_iterator operator--(int)
        {
            tree_iterator __tmp(*this);
            --(*this);
            return __tmp;
        }

        iterator_type base() const
        {
            return __i;
        }
    };
}

#endif /* TREE_ITERATOR_HPP */
