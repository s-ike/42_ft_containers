#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
    template <class _Tp, class _Container = ft::vector<_Tp> >
    class stack
    {
    public:
        typedef _Container                               container_type;
        typedef typename container_type::value_type      value_type;
        typedef typename container_type::size_type       size_type;

    protected:
        container_type c;

    public:
        // Member functions
        explicit stack(const container_type& __ctnr = container_type())
            : c(__ctnr)
        {}

        bool empty()     const        {return c.empty();}
        size_type size() const        {return c.size();}
        value_type& top()             {return c.back();}
        const value_type& top() const {return c.back();}

        void push(const value_type& __v) {c.push_back(__v);}
        void pop() {c.pop_back();}

        template <class T1, class _C1>
        friend
        bool operator==(const stack<T1, _C1>& __lhs, const stack<T1, _C1>& __rhs);

        template <class T1, class _C1>
        friend
        bool operator< (const stack<T1, _C1>& __lhs, const stack<T1, _C1>& __rhs);
    };

    // Non-member function overloads
    template <class _Tp, class _Container>
    bool operator==(const stack<_Tp, _Container>& __lhs, const stack<_Tp, _Container>& __rhs)
    {
        return __lhs.c == __rhs.c;
    }
    template <class _Tp, class _Container>
    bool operator!=(const stack<_Tp, _Container>& __lhs, const stack<_Tp, _Container>& __rhs)
    {
        return !(__lhs == __rhs);
    }
    template <class _Tp, class _Container>
    bool operator<(const stack<_Tp, _Container>& __lhs, const stack<_Tp, _Container>& __rhs)
    {
        return __lhs.c < __rhs.c;
    }
    template <class _Tp, class _Container>
    bool operator<=(const stack<_Tp, _Container>& __lhs, const stack<_Tp, _Container>& __rhs)
    {
        return !(__rhs < __lhs);
    }
    template <class _Tp, class _Container>
    bool operator>(const stack<_Tp, _Container>& __lhs, const stack<_Tp, _Container>& __rhs)
    {
        return __rhs < __lhs;
    }
    template <class _Tp, class _Container>
    bool operator>=(const stack<_Tp, _Container>& __lhs, const stack<_Tp, _Container>& __rhs)
    {
        return !(__lhs < __rhs);
    }
}

#endif /* STACK_HPP */
