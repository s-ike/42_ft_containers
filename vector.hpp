#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <algorithm>
#include <exception>
#include "algorithm.hpp"
#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include <iostream>

namespace ft {
    template <class _Tp, class _Allocator = std::allocator<_Tp> >
    class vector
    {
    public:
        typedef _Tp                                     value_type;
        typedef _Allocator                              allocator_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef _Tp*                                    pointer;
        typedef const _Tp*                              const_pointer;
        typedef ft::vector_iterator<pointer>            iterator;
        typedef ft::vector_iterator<const_pointer>      const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef std::ptrdiff_t                          difference_type;
        typedef std::size_t                             size_type;

    private :
        pointer         __begin_;
        pointer         __end_;
        pointer         __end_cap_;
        allocator_type  __alloc_;

    public:
        // constructor
        explicit vector(const allocator_type& __alloc = allocator_type())
            : __begin_(NULL),
              __end_(NULL),
              __end_cap_(NULL),
              __alloc_(__alloc)
        {}
        explicit vector(size_type __n, const value_type& __val = value_type(),
                        const allocator_type& __alloc = allocator_type())
            : __begin_(NULL),
              __end_(NULL),
              __end_cap_(NULL),
              __alloc_(__alloc)
        {
            if (__n > 0)
            {
                __vallocate(__n);
                std::uninitialized_fill(__begin_, __begin_ + __n, __val);
                __end_ = __begin_ + __n;
            }
        }
        template <class _InputIterator>
        vector(_InputIterator __first,
               typename ft::enable_if<!ft::is_integral<_InputIterator>::value, _InputIterator>::type __last,
               const allocator_type& __alloc = allocator_type())
            : __begin_(NULL),
              __end_(NULL),
              __end_cap_(NULL),
              __alloc_(__alloc)
        {
            size_type __n = static_cast<size_type>(std::distance(__first, __last));
            if (__n > 0)
            {
                __vallocate(__n);
                std::uninitialized_copy(__first, __last, __begin_);
                __end_ = __begin_ + __n;
            }
        }
        vector(const vector& __x)
            : __begin_(NULL),
              __end_(NULL),
              __end_cap_(NULL),
              __alloc_(__x.__alloc_)
        {
            size_type __n = __x.size();
            if (__n > 0)
            {
                __vallocate(__n);
                std::uninitialized_copy(__x.begin(), __x.end(), __begin_);
                __end_ = __begin_ + __n;
            }
        }
        // destructor
        ~vector()
        {
            if (__begin_ != NULL)
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
                __alloc_ = __x.__alloc_;
                assign(__x.begin(), __x.end());
            }
            return *this;
        }

        // Iterators
        iterator begin()
        {
            return __make_iter(__begin_);
        }
        const_iterator begin() const
        {
            return __make_iter(__begin_);
        }
        iterator end()
        {
            return __make_iter(__end_);
        }
        const_iterator end() const
        {
            return __make_iter(__end_);
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
            return static_cast<size_type>(__end_ - __begin_);
        }
        size_type max_size() const
        {
            return std::min(__alloc_.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));
        }
        void resize(size_type __n, value_type __val = value_type())
        {
            size_type __cs = size();
            if (__cs > __n)
            {
                __destruct_at_end(__begin_ + __n);
            }
            else if (__cs < __n)
            {
                reserve(__n);
                std::uninitialized_fill_n(__end_, __n - __cs, __val);
                __end_ = __begin_ + __n;
            }
        }
        size_type capacity() const
        {
            return static_cast<size_type>(__end_cap_ - __begin_);
        }
        bool empty() const
        {
            return __begin_ == __end_;
        }
        void reserve(size_type __n)
        {
            if (__n <= capacity())
                return;

            pointer __old_begin = __begin_;
            size_type __old_size = size();
            size_type __old_capa = capacity();

            __vallocate(__n);
            for (size_type __i = 0; __i < __old_size; ++__i, ++__end_)
                __alloc_.construct(&__begin_[__i], __old_begin[__i]);
            for (size_type __i = 0; __i < __old_size; ++__i)
                __destroy(&__old_begin[__i]);
            __alloc_.deallocate(__old_begin, __old_capa);
        }

        // Element access
        reference operator[](size_type __n)
        {
            return __begin_[__n];
        }
        const_reference operator[](size_type __n) const
        {
            return __begin_[__n];
        }
        reference at(size_type __n)
        {
            if (__n >= size())
                throw std::out_of_range("vector");
            return __begin_[__n];
        }
        const_reference at(size_type __n) const
        {
            if (__n >= size())
                throw std::out_of_range("vector");
            return __begin_[__n];
        }
        reference front()
        {
            return *__begin_;
        }
        const_reference front() const
        {
            return *__begin_;
        }
        reference back()
        {
            return *(__end_ - 1);
        }
        const_reference back() const
        {
            return *(__end_ - 1);
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
                    std::uninitialized_copy(__first, __last, __begin_);
                }
                else
                {
                    __destruct_at_end(__begin_ + __new_size);
                    std::copy(__first, __last, __begin_);
                }
            }
            else
            {
                __vdeallocate();
                __vallocate(__new_size);
                std::uninitialized_copy(__first, __last, __begin_);
            }
            __end_ = __begin_ + __new_size;
        }
        void assign(size_type __n, const value_type& __val)
        {
            if (__n <= capacity())
            {
                size_type __s = size();
                std::fill_n(__begin_, std::min(__n, __s), __val);
                if (__n > __s)
                    std::uninitialized_fill_n(__begin_ + __s, __n - __s, __val);
                else
                    __destruct_at_end(__begin_ + __n);
            }
            else
            {
                __vdeallocate();
                __vallocate(__n);
                std::uninitialized_fill_n(__begin_, __n, __val);
            }
            __end_ = __begin_ + __n;
        }
        void push_back(const value_type& __val)
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
            __alloc_.construct(__end_, __val);
            ++__end_;
        }
        void pop_back()
        {
            __destruct_at_end(__end_ - 1);
        }
        iterator insert(iterator __position, const value_type& __val)
        {
            difference_type __offset = __position - begin();
            insert(__position, 1, __val);
            return begin() + __offset;
        }
        void insert(iterator __position, size_type __n, const value_type& __val)
        {
            difference_type __offset = __position - begin();
            pointer __p = __begin_ + __offset;
            if (__n > 0)
            {
                if (__n <= static_cast<size_type>(__end_cap_ - __end_))
                {
                    for (size_type __i = 0; __i < __n; ++__i)
                        __alloc_.construct(__begin_ + size() + __i, __val);
                    std::copy_backward(__make_iter(__p), __make_iter(__end_), __end_ + __n);
                    std::fill_n(__p, __n, __val);
                    __end_ += __n;
                }
                else
                {
                    size_type __new_size = size() + __n;
                    if (__new_size > max_size())
                        throw std::length_error("vector");
                    pointer __new = __alloc_.allocate(__new_size);
                    std::uninitialized_copy(begin(), begin() + __offset, __new);
                    std::uninitialized_fill_n(__new + __offset, __n, __val);
                    std::uninitialized_copy(__make_iter(__p), end(), __new + __offset + __n);
                    __vdeallocate();
                    __begin_ = __new;
                    __end_cap_ = __end_ = __begin_ + __new_size;
                }
            }
        }
        template <class _InputIterator>
        typename ft::enable_if<!ft::is_integral<_InputIterator>::value, void>::type
        insert(iterator __position, _InputIterator __first, _InputIterator __last)
        {
            difference_type __offset = __position - begin();
            pointer __p = __begin_ + __offset;
            difference_type __n = std::distance(__first, __last);
            if (__n > 0)
            {
                if (__n <= __end_cap_ - __end_)
                {
                    for (difference_type __i = 0; __i < __n; ++__i)
                        __alloc_.construct(__begin_ + size() + __i, 0);
                    std::copy_backward(__make_iter(__p), __make_iter(__end_), __end_ + __n);
                    std::copy(__first, __last, __p);
                    __end_ += __n;
                }
                else
                {
                    size_type __new_size = size() + __n;
                    if (__new_size > max_size())
                        throw std::length_error("vector");
                    pointer __new = __alloc_.allocate(__new_size);
                    std::uninitialized_copy(begin(), begin() + __offset, __new);
                    std::uninitialized_copy(__first, __last, __new + __offset);
                    std::uninitialized_copy(__make_iter(__p), end(), __new + __offset + __n);
                    __vdeallocate();
                    __begin_ = __new;
                    __end_cap_ = __end_ = __begin_ + __new_size;
                }
            }
        }
        iterator erase(iterator __position)
        {
            if (__position == end())
                return __position;
            for (iterator __i = __position + 1; __i != end(); ++__i)
                *(__i - 1) = *__i;
            __alloc_.destroy(&*(end() - 1));
            --__end_;
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
            __swap(__begin_, __x.__begin_);
            __swap(__end_, __x.__end_);
            __swap(__end_cap_, __x.__end_cap_);
            __swap(__alloc_, __x.__alloc_);
        }
        void clear()
        {
            __clear();
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return __alloc_;
        }

    private:
        void __vallocate(size_type __n)
        {
            if (__n > max_size())
                throw std::length_error("vector");
            __begin_ = __end_ = __alloc_.allocate(__n);
            __end_cap_ = __begin_ + __n;
        }
        void __vdeallocate()
        {
            if (__begin_ != NULL)
            {
                clear();
                __deallocate();
                __begin_ = __end_ = __end_cap_ = NULL;
            }
        }
        void __clear()
        {
            __destruct_at_end(__begin_);
        }
        void __destruct_at_end(pointer __new_last)
        {
            pointer __soon_to_be_end = __end_;
            while (__new_last != __soon_to_be_end)
                __alloc_.destroy(--__soon_to_be_end);
            __end_ = __new_last;
        }
        void __deallocate()
        {
            __alloc_.deallocate(__begin_, capacity());
        }
        void __destroy(pointer ptr)
        {
            __alloc_.destroy(ptr);
        }
        iterator __make_iter(pointer __p)
        {
            return iterator(__p);
        }
        const_iterator __make_iter(const_pointer __p) const
        {
            return const_iterator(__p);
        }
        template <class _Up>
        void __swap(_Up& __x, _Up& __y)
        {
            _Up __temp = __x;
            __x = __y;
            __y = __temp;
        }
        // void __move_range(pointer __from, size_type __n)
        // {
        //     // pointer __i = ++__end_;
        //     // 挿入位置からn番目のメモリ（constructされていない）
        //     pointer __to = __end_ + __n;
        //     pointer __src = --__end_;
        //     for (; __from < __to; --__to, --__src)
        //     {
        //         __alloc_.construct(__to, __src);
        //     }

        // }
    };

    // Non-member function overloads
    template <class _T, class _Allocator>
    bool operator==(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return __lhs.size() == __rhs.size() && ft::equal(__lhs.begin(), __lhs.end(), __rhs.begin());
    }
    template <class _T, class _Allocator>
    bool operator!=(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return !(__lhs == __rhs);
    }
    template <class _T, class _Allocator>
    bool operator<(const vector<_T, _Allocator>& __lhs, const vector<_T, _Allocator>& __rhs)
    {
        return ft::lexicographical_compare(__lhs.begin(), __lhs.end(), __rhs.begin(), __rhs.end());
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
