#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <exception>
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

namespace ft {
    template <typename _T, typename _Allocator = std::allocator<_T> >
    class vector
    {
    public:
        typedef _T                                      value_type;
        typedef _Allocator                              allocator_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef _T*                                     pointer;
        typedef const _T*                               const_pointer;
        typedef ft::vector_iterator<pointer>            iterator;
        typedef ft::vector_iterator<const_pointer>      const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef std::ptrdiff_t                          difference_type;
        typedef std::size_t                             size_type;

    private :
        pointer         __begin;
        pointer         __end;
        pointer         __end_cap;
        allocator_type  __alloc;

    public:
        // constructor
        explicit vector(const allocator_type& __alloc = allocator_type())
            : __begin(NULL), __end(NULL), __end_cap(NULL), __alloc(__alloc)
        {}
        explicit vector(size_type __n, const value_type& __val = value_type(),
                 const allocator_type& __alloc = allocator_type())
            : __begin(NULL), __end(NULL), __end_cap(NULL), __alloc(__alloc)
        {
            if (__n > 0)
            {
                __vallocate(__n);
                std::uninitialized_fill(__begin, __begin + __n, __val);
                __end = __begin + __n;
            }
        }
        template <class _InputIterator>
        vector(_InputIterator __first,
               typename ft::enable_if<!ft::is_integral<_InputIterator>::value, _InputIterator>::type __last,
               const allocator_type & __alloc = allocator_type())
            : __begin(NULL), __end(NULL), __end_cap(NULL), __alloc(__alloc)
        {
            size_type __n = static_cast<size_type>(std::distance(__first, __last));
            if (__n > 0)
            {
                __vallocate(__n);
                std::uninitialized_copy(__first, __last, __begin);
                __end = __begin + __n;
            }
        }
        vector(const vector& __x)
            : __begin(NULL), __end(NULL), __end_cap(NULL), __alloc(__x.__alloc)
        {
            size_type __n = __x.size();
            if (__n > 0)
            {
                __vallocate(__n);
                std::uninitialized_copy(__x.begin(), __x.end(), __begin);
                __end = __begin + __n;
            }
        }
        // destructor
        ~vector()
        {
            if (__begin != NULL)
            {
                __clear();
                __deallocate();
            }
        }
        // operator=
        vector& operator=(const vector& __x)
        {
            if (this != &__x)
            {
                __alloc = __x.__alloc;
                assign(__x.__begin, __x.__end);
            }
            return *this;
        }

        // Iterators
        iterator begin()
        {
            return __make_iter(__begin);
        }
        const_iterator begin() const
        {
            return __make_iter(__begin);
        }
        iterator end()
        {
            return __make_iter(__end);
        }
        const_iterator end() const
        {
            return __make_iter(__end);
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        // Capacity
        size_type size() const
        {
            return static_cast<size_type>(__end - __begin);
        }
        size_type max_size() const
        {
            return std::min(__alloc.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));
        }
        void resize(size_type __n, value_type __val = value_type())
        {
            size_type __cs = size();
            if (__cs > __n)
            {
                __base_destruct_at_end(__begin + __n);
            }
            else if (__cs < __n)
            {
                reserve(__n);
                std::uninitialized_fill_n(__end, __n - __cs, __val);
                __end = __begin + __n;
            }
        }
        size_type capacity() const
        {
            return static_cast<size_type>(__end_cap - __begin);
        }
        bool empty() const
        {
            return __begin == __end;
        }
        void reserve(size_type __n)
        {
            if (__n <= capacity())
                return ;

            pointer __old_begin = __begin;
            size_type __old_size = size();
            size_type __old_capa = capacity();

            __vallocate(__n);
            for (size_type __i = 0; __i < __old_size; ++__i, ++__end)
                __alloc.construct(&__begin[__i], __old_begin[__i]);
            for (size_type __i = 0; __i < __old_size; ++__i)
                __destroy(&__old_begin[__i]);
            __alloc.deallocate(__old_begin, __old_capa);
        }

        // Element access
        reference operator[](size_type __n)
        {
            return __begin[__n];
        }
        const_reference operator[](size_type __n) const
        {
            return __begin[__n];
        }
        reference at(size_type __n)
        {
            if (__n >= size())
                throw std::out_of_range("vector");
            return __begin[__n];
        }
        const_reference at(size_type __n) const
        {
            if (__n >= size())
                throw std::out_of_range("vector");
            return __begin[__n];
        }
        reference front()
        {
            return *__begin;
        }
        const_reference front() const
        {
            return *__begin;
        }
        reference back()
        {
            return *(__end - 1);
        }
        const_reference back() const
        {
            return *(__end - 1);
        }

        // Modifiers
        template <class _InputIterator>
        typename ft::enable_if<!ft::is_integral<_InputIterator>::value, void>::type
        assign(_InputIterator __first, _InputIterator __last)
        {
            size_type __new_size = static_cast<size_type>(std::distance(__first, __last));
            if (__new_size <= capacity())
            {
                if (__new_size > size())
                {
                    clear();
                    std::uninitialized_copy(__first, __last, __begin);
                }
                else
                {
                    __base_destruct_at_end(__begin + __new_size);
                    std::copy(__first, __last, __begin);
                }
            }
            else
            {
                __vdeallocate();
                __vallocate(__new_size);
                std::uninitialized_copy(__first, __last, __begin);
            }
            __end = __begin + __new_size;
        }
        void assign(size_type __n, const value_type& __val)
        {
            if (__n <= capacity())
            {
                size_type __s = size();
                std::fill_n(__begin, std::min(__n, __s), __val);
                if (__n > __s)
                    std::uninitialized_fill_n(__begin + __s, __n - __s, __val);
                else
                    __base_destruct_at_end(__begin + __n);
            }
            else
            {
                __vdeallocate();
                __vallocate(__n);
                std::uninitialized_fill_n(__begin, __n, __val);
            }
            __end = __begin + __n;
        }
        void push_back(const value_type& val)
        {
            if (size() + 1 > capacity())
            {
                size_type __sz = size();
                if (__sz == 0)
                    __sz = 1;
                else
                    __sz *= 2;
                reserve(__sz);
            }
            __alloc.construct(__end, val);
            ++__end;
        }
        void pop_back()
        {
            __base_destruct_at_end(__end - 1);
        }
        iterator insert(iterator __position, const value_type& __val)
        {
            size_type __idx = __position - begin();
            if (size() == capacity())
                reserve(size() == 0 ? 1 : size() * 2);
            __alloc.construct(__begin + size(), back());
            ++__end;
            iterator __pos = begin() + __idx;
            for (iterator __i = end() - 1; __i != __pos; --__i)
                *__i = *(__i - 1);
            *(begin() + __idx) = __val;
            return __pos;
        }
        void insert(iterator __position, size_type __n, const value_type& __val)
        {
            size_type __idx = __position - begin();
            if (__n > 0)
            {
                while (__n--)
                {
                    iterator __pos = begin() + __idx;
                    insert(__pos, __val);
                }
            }
        }
        template <class _InputIterator>
        typename ft::enable_if<!ft::is_integral<_InputIterator>::value, void>::type
        insert(iterator __position, _InputIterator __first, _InputIterator __last)
        {
            size_type __idx = __position - begin();
            while (__first != __last)
            {
                iterator __pos = begin() + __idx;
                insert(__pos, *--__last);
            }
        }
        iterator erase(iterator __position)
        {
            if (__position == end())
                return __position;
            for (iterator __i = __position + 1; __i != end(); ++__i)
                *(__i - 1) = *__i;
            __alloc.destroy(&*(end() - 1));
            --__end;
            return __position;
        }
        iterator erase(iterator __first, iterator __last)
        {
            while (__first != __last)
            {
                erase(__first);
                --__last;
            }
            return __first;
        }
        void swap(vector& __x)
        {
            pointer __temp_begin = __x.__begin;
            pointer __temp_end = __x.__end;
            pointer __temp_end_cap = __x.__end_cap;
            allocator_type __temp_alloc = __x.__alloc;

            __x.__begin = __begin;
            __x.__end = __end;
            __x.__end_cap = __end_cap;
            __x.__alloc = __alloc;

            __begin = __temp_begin;
            __end = __temp_end;
            __end_cap = __temp_end_cap;
            __alloc = __temp_alloc;
        }
        void clear()
        {
            __clear();
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return __alloc;
        }

    private:
        void __vallocate(size_type __n)
        {
            if (__n > max_size())
                throw std::length_error("vector");
            __begin = __end = __alloc.allocate(__n);
            __end_cap = __begin + __n;
        }
        void __vdeallocate()
        {
            if (__begin != NULL)
            {
                clear();
                __deallocate();
                __begin = __end = __end_cap = NULL;
            }
        }
        void __clear()
        {
            __base_destruct_at_end(__begin);
        }
        void __base_destruct_at_end(pointer __new_last)
        {
            pointer __soon_to_be_end = __end;
            while (__new_last != __soon_to_be_end)
                __alloc.destroy(--__soon_to_be_end);
            __end = __new_last;
        }
        void __deallocate()
        {
            __alloc.deallocate(__begin, capacity());
        }
        void __destroy(pointer ptr)
        {
            __alloc.destroy(ptr);
        }
        iterator __make_iter(pointer __p)
        {
            return iterator(__p);
        }
        const_iterator __make_iter(const_pointer __p) const
        {
            return const_iterator(__p);
        }
    };

    // Non-member function overloads
    template <class _T, class _Allocator>
    bool operator==(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return __lhs.size() == __rhs.size() && std::equal(__lhs.begin(), __lhs.end(), __rhs.begin());
    }
    template <class _T, class _Allocator>
    bool operator!=(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return !(__lhs == __rhs);
    }
    template <class _T, class _Allocator>
    bool operator<(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return std::lexicographical_compare(__lhs.begin(), __lhs.end(), __rhs.begin(), __rhs.end());
    }
    template <class _T, class _Allocator>
    bool operator<=(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return !(__rhs < __lhs);
    }
    template <class _T, class _Allocator>
    bool operator>(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return __rhs < __lhs;
    }
    template <class _T, class _Allocator>
    bool operator>=(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return !(__lhs < __rhs);
    }

    template <class _T, class _Allocator>
    void swap(vector<_T, _Allocator>& __x, vector<_T, _Allocator>& __y)
    {
        __x.swap(__y);
    }
}

#endif /* VECTOR_HPP */
