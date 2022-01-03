#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {

    /* ********************************************************************** */
    /*   pair                                                                 */
    /* ********************************************************************** */

    template <class _T1, class _T2>
    struct pair
    {
        // Member types
        typedef _T1 first_type;
        typedef _T2 second_type;

        // Member variables
        _T1 first;
        _T2 second;

        // Member functions
        pair()
            : first(), second()
        {}
        template <class _U, class _V>
        pair(const pair<_U, _V>& __pr)
            : first(__pr.first), second(__pr.second)
        {}
        pair (const first_type& __a, const second_type& __b)
            : first(__a), second(__b)
        {}

        pair& operator=(const pair& __pr) {
            first = __pr.first;
            second = __pr.second;
            return *this;
        }
    };

    // Non-member function overloads
    template <class _T1, class _T2>
    bool operator==(const pair<_T1, _T2>& __lhs, const pair<_T1, _T2>& __rhs)
    {
        return __lhs.first == __rhs.first && __lhs.second == __rhs.second;
    }
    template <class _T1, class _T2>
    bool operator!=(const pair<_T1, _T2>& __lhs, const pair<_T1, _T2>& __rhs)
    {
        return !(__lhs == __rhs);
    }
    template <class _T1, class _T2>
    bool operator<(const pair<_T1, _T2>& __lhs, const pair<_T1, _T2>& __rhs)
    {
        return __lhs.first < __rhs.first || (!(__rhs.first < __lhs.first) && __lhs.second < __rhs.second);
    }
    template <class _T1, class _T2>
    bool operator<=(const pair<_T1, _T2>& __lhs, const pair<_T1, _T2>& __rhs)
    {
        return !(__rhs < __lhs);
    }
    template <class _T1, class _T2>
    bool operator>(const pair<_T1, _T2>& __lhs, const pair<_T1, _T2>& __rhs)
    {
        return __rhs < __lhs;
    }
    template <class _T1, class _T2>
    bool operator>=(const pair<_T1, _T2>& __lhs, const pair<_T1, _T2>& __rhs)
    {
        return !(__lhs < __rhs);
    }

    /* ********************************************************************** */
    /*   make_pair                                                            */
    /* ********************************************************************** */

    template <class _T1, class _T2>
    pair<_T1, _T2> make_pair(_T1 __x, _T2 __y)
    {
        return pair<_T1, _T2>(__x, __y);
    }
}

#endif /* UTILITY_HPP */
