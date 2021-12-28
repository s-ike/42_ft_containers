#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>

namespace ft {
    template <class _Iter>
    struct iterator_traits
    {
        typedef typename _Iter::iterator_category iterator_category;
        typedef typename _Iter::value_type        value_type;
        typedef typename _Iter::difference_type   difference_type;
        typedef typename _Iter::pointer           pointer;
        typedef typename _Iter::reference         reference;
    };

    template <class _T>
    struct iterator_traits<_T*>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef _T                              value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef _T*                             pointer;
        typedef _T&                             reference;
    };

    template <class _T>
    struct iterator_traits<const _T*>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef _T                              value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef const _T*                       pointer;
        typedef const _T&                       reference;
    };
}

#endif /* ITERATOR_TRAITS_HPP */
