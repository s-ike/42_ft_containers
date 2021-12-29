#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {
    // lexicographical_compare

    template <class _InputIterator1, class _InputIterator2, class _Compare>
    bool
    lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                            _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
    {
        for (; __first2 != __last2; ++__first1, ++__first2)
        {
            if (__first1 == __last1 || __comp(*__first1, *__first2))
                return true;
            if (__comp(*__first2, *__first1))
                return false;
        }
        return false;
    }

    template <class _InputIterator1, class _InputIterator2>
    bool
    lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                            _InputIterator2 __first2, _InputIterator2 __last2)
    {
        for (; __first2 != __last2; ++__first1, ++__first2)
        {
            if (__first1 == __last1 || *__first1 < *__first2)
                return true;
            if (*__first2 < *__first1)
                return false;
        }
        return false;
    }
}

#endif /* ALGORITHM_HPP */
