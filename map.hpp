#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <iterator>
#include "tree.hpp"
#include "utility.hpp"
// #include "tree_iterator.hpp"

namespace ft {
    // template <class _Tp> struct
    // __libcpp_is_final : public std::integral_constant<bool, __is_final(_Tp)> {};

    // template <class _Key, class _CP, class _Compare,
    //           bool = std::is_empty<_Compare>::value && !__libcpp_is_final<_Compare>::value>
    template <class _Key, class _CP, class _Compare>
    class __map_value_compare
        : private _Compare
    {
    public:
        __map_value_compare() : _Compare()
        {}
        __map_value_compare(_Compare c) : _Compare(c)
        {}
        const _Compare& key_comp() const
        {
            return *this;
        }
        bool operator()(const _CP& __x, const _CP& __y) const
        {
            return static_cast<const _Compare&>(*this)(__x.__get_value().first, __y.__get_value().first);
        }
        bool operator()(const _CP& __x, const _Key& __y) const
        {
            return static_cast<const _Compare&>(*this)(__x.__get_value().first, __y);
        }
        bool operator()(const _Key& __x, const _CP& __y) const
        {
            return static_cast<const _Compare&>(*this)(__x, __y.__get_value().first);
        }
        // void swap(__map_value_compare&__y)
        // {
        // using _VSTD::swap;
        // swap(static_cast<_Compare&>(*this), static_cast<_Compare&>(__y));
        // }
    };

    // template <class _TreeIterator>
    // class __map_iterator
    // {
    //     typedef typename _TreeIterator::_NodeTypes                   _NodeTypes;
    //     typedef typename _TreeIterator::__pointer_traits             __pointer_traits;

    //     _TreeIterator __i_;

    // public:
    //     typedef std::bidirectional_iterator_tag                      iterator_category;
    //     typedef typename _NodeTypes::__map_value_type                value_type;
    //     typedef typename _TreeIterator::difference_type              difference_type;
    //     typedef value_type&                                          reference;
    //     typedef typename _NodeTypes::__map_value_type_pointer        pointer;

    //     __map_iterator() {}

    //     __map_iterator(_TreeIterator __i) : __i_(__i) {}

    //     reference operator*() const {return __i_->__get_value();}
    //     pointer operator->() const {return std::pointer_traits<pointer>::pointer_to(__i_->__get_value());}

    //     __map_iterator& operator++() {++__i_; return *this;}
    //     __map_iterator operator++(int)
    //     {
    //         __map_iterator __t(*this);
    //         ++(*this);
    //         return __t;
    //     }

    //     __map_iterator& operator--() {--__i_; return *this;}
    //     __map_iterator operator--(int)
    //     {
    //         __map_iterator __t(*this);
    //         --(*this);
    //         return __t;
    //     }

    //     friend
    //     bool operator==(const __map_iterator& __x, const __map_iterator& __y)
    //         {return __x.__i_ == __y.__i_;}
    //     friend
    //     bool operator!=(const __map_iterator& __x, const __map_iterator& __y)
    //         {return __x.__i_ != __y.__i_;}

    //     template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    //     template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
    //     template <class> friend class _LIBCPP_TEMPLATE_VIS __map_const_iterator;
    // };

    // template <class _TreeIterator>
    // class __map_const_iterator
    // {
    //     typedef typename _TreeIterator::_NodeTypes                   _NodeTypes;
    //     typedef typename _TreeIterator::__pointer_traits             __pointer_traits;

    //     _TreeIterator __i_;

    // public:
    //     typedef std::bidirectional_iterator_tag                      iterator_category;
    //     typedef typename _NodeTypes::__map_value_type                value_type;
    //     typedef typename _TreeIterator::difference_type              difference_type;
    //     typedef const value_type&                                    reference;
    //     typedef typename _NodeTypes::__const_map_value_type_pointer  pointer;

    //     __map_const_iterator() _NOEXCEPT {}

    //     __map_const_iterator(_TreeIterator __i) _NOEXCEPT : __i_(__i) {}
    //     __map_const_iterator(__map_iterator<
    //         typename _TreeIterator::__non_const_iterator> __i) _NOEXCEPT
    //         : __i_(__i.__i_) {}

    //     reference operator*() const {return __i_->__get_value();}
    //     pointer operator->() const {return std::pointer_traits<pointer>::pointer_to(__i_->__get_value());}

    //     __map_const_iterator& operator++() {++__i_; return *this;}
    //     __map_const_iterator operator++(int)
    //     {
    //         __map_const_iterator __t(*this);
    //         ++(*this);
    //         return __t;
    //     }

    //     _LIBCPP_INLINE_VISIBILITY
    //     __map_const_iterator& operator--() {--__i_; return *this;}
    //     _LIBCPP_INLINE_VISIBILITY
    //     __map_const_iterator operator--(int)
    //     {
    //         __map_const_iterator __t(*this);
    //         --(*this);
    //         return __t;
    //     }

    //     friend
    //     bool operator==(const __map_const_iterator& __x, const __map_const_iterator& __y)
    //         {return __x.__i_ == __y.__i_;}
    //     friend
    //     bool operator!=(const __map_const_iterator& __x, const __map_const_iterator& __y)
    //         {return __x.__i_ != __y.__i_;}

    //     template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    //     template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
    //     template <class, class, class> friend class _LIBCPP_TEMPLATE_VIS __tree_const_iterator;
    // };

    // template <class _Key, class _Tp>
    // struct __value_type
    // {
    //     typedef _Key                                    key_type;
    //     typedef _Tp                                     mapped_type;
    //     typedef std::pair<const key_type, mapped_type>  value_type;

    // private:
    //     value_type __cc;

    // public:
    //     _LIBCPP_INLINE_VISIBILITY
    //     value_type& __get_value() { return __cc; }
    //     _LIBCPP_INLINE_VISIBILITY
    //     const value_type& __get_value() const { return __cc; }

    // private:
    //     __value_type();
    //     __value_type(__value_type const&);
    //     __value_type& operator=(__value_type const&);
    //     ~__value_type();
    // };

    template <class _Key, class _Tp, class _Compare = std::less<_Key>,
              class _Allocator = std::allocator<ft::pair<const _Key, _Tp> > >
    class map
    {
    public:
        // types:
        typedef _Key                                    key_type;
        typedef _Tp                                     mapped_type;
        typedef ft::pair<const key_type, mapped_type>   value_type;
        typedef _Compare                                key_compare;

        class value_compare
            : public std::binary_function<value_type, value_type, bool>
        {
            friend class map;

        protected:
            _Compare comp;
            value_compare(_Compare __c) : comp(__c)
            {}

        public:
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;
            bool operator()(const value_type& __x, const value_type& __y) const
            {
                return comp(__x.first, __y.first);
            }
        };

        typedef _Allocator                                  allocator_type;
        typedef typename allocator_type::value_type&        reference;
        typedef const typename allocator_type::value_type&  const_reference;
        typedef typename allocator_type::value_type*        pointer;
        typedef const typename allocator_type::value_type*  const_pointer;

    private:
        // typedef __value_type<key_type, mapped_type>                      __value_type;
        typedef __map_value_compare<key_type, value_type, key_compare> __vc;
        // typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>,
        //                                             __value_type>::type __allocator_type;
        typedef ft::tree<value_type, key_compare, allocator_type>           __base;
        // typedef typename __base::__node_traits                 __node_traits;
        // typedef allocator_traits<allocator_type>               __alloc_traits;

        __base __tree_;

    public:
        typedef typename __base::iterator               iterator;
        typedef typename __base::const_iterator         const_iterator;
        typedef std::reverse_iterator<iterator>         reverse_iterator;
        typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;
        typedef std::ptrdiff_t                          difference_type;
        typedef std::size_t                             size_type;

        template <class _Key2, class _Value2, class _Comp2, class _Alloc2>
            friend class map;
        template <class _Key2, class _Value2, class _Comp2, class _Alloc2>
            friend class multimap;

        explicit map(const key_compare& __comp = key_compare(),
                     const allocator_type& __alloc = allocator_type())
            : __tree_(__comp, __alloc)
        {}
        template <class _InputIterator>
        map(_InputIterator __first, _InputIterator __last,
            const key_compare& __comp = key_compare(),
            const allocator_type& __alloc = allocator_type())
            : __tree_(__comp, __alloc)
        {
            insert(__first, __last);
        }
        map(const map& __x)
            : __tree_(__x.__tree_)
        {
            insert(__x.begin(), __x.end());
        }
        ~map()
        {}
        map& operator=(const map& __x)
        {
            if (this != &__x)
            {
                __tree_ = __x.__tree_;
            }
            return *this;
        }

        // Iterators
        iterator begin()
        {
            return __tree_.begin();
        }
        const_iterator begin() const
        {
            return __tree_.begin();
        }
        iterator end()
        {
            return __tree_.end();
        }
        const_iterator end() const
        {
            return __tree_.end();
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
        bool      empty() const {
            return __tree_.size() == 0;
        }
        size_type size() const
        {
            return __tree_.size();
        }
        size_type max_size() const
        {
            return __tree_.max_size();
        }

        // Element access
        mapped_type& operator[](const key_type& __k)
        {
            iterator __itr = find(__k);
            if (__itr == end())
                __itr = insert(value_type(__k, mapped_type())).first;
            return (*__itr).second;
        }

        // Modifiers
        ft::pair<iterator, bool> insert(const value_type& __val)
        {
            typename __base::node_type* __re = __tree_.search(__val);
            if (__re)
                return (ft::make_pair(iterator(__re), false));
            __re = __tree_.insert(__val);
            return (ft::make_pair(iterator(__re), true));
        }
        iterator insert(iterator __position, const value_type& __val)
        {
            (void)__position;
            return insert(__val).first;
        }
        template <class _InputIterator>
        void insert(_InputIterator __first, _InputIterator __last)
        {
            for (; __first != __last; ++__first)
                insert(*__first);
        }
        void erase(iterator __position)
        {
            __tree_.erase(__position);
        }
        size_type erase(const key_type& __k)
        {
            return __tree_.erase_unique(__k);
        }
        void erase(iterator __first, iterator __last)
        {
            __tree_.erase(__first, __last);
        }
        void swap(map& __x)
        {
            __tree_.swap(__x.__tree_);
        }
        void clear()
        {
            __tree_.clear();
        }

        // Observers
        key_compare key_comp() const
        {
            return __tree_.key_comp();
        }
        value_compare value_comp() const
        {
            return value_compare(__tree_.key_comp());
        }

        // Operations
        iterator find(const key_type& __k)
        {
            return iterator(__tree_.find(__k));
        }
        const_iterator find(const key_type& __k) const
        {
            return const_iterator(__tree_.find(__k));
        }
        size_type count(const key_type& __k) const
        {
            return find(__k) == end() ? 0 : 1;
        }
        iterator lower_bound(const key_type& __k)
        {
            return __tree_.lower_bound(__k);
        }
        const_iterator lower_bound(const key_type& __k) const
        {
            return __tree_.lower_bound(__k);
        }
        iterator upper_bound(const key_type& __k)
        {
            return __tree_.upper_bound(__k);
        }
        const_iterator upper_bound (const key_type& __k) const
        {
            return __tree_.upper_bound(__k);
        }
        pair<const_iterator, const_iterator> equal_range(const key_type& __k) const
        {
            return __tree_.equal_range(__k);
        }
        pair<iterator, iterator> equal_range(const key_type& __k)
        {
            return __tree_.equal_range(__k);
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return allocator_type(__tree_.get_allocator());
        }

        // void debug() const
        // {
        //     __tree_.print_all_in_order();
        // }
    };

    // Non-member function overloads
    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool operator==(const map<_Key, _Tp, _Compare, _Allocator>& __lhs,
                    const map<_Key, _Tp, _Compare, _Allocator>& __rhs)
    {
        return __lhs.size() == __rhs.size() && std::equal(__lhs.begin(), __lhs.end(), __rhs.begin());
    }
    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool operator!=(const map<_Key, _Tp, _Compare, _Allocator>& __lhs,
                    const map<_Key, _Tp, _Compare, _Allocator>& __rhs)
    {
        return !(__lhs == __rhs);
    }
    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool operator<(const map<_Key, _Tp, _Compare, _Allocator>& __lhs,
                   const map<_Key, _Tp, _Compare, _Allocator>& __rhs)
    {
        return ft::lexicographical_compare(__lhs.begin(), __lhs.end(), __rhs.begin(), __rhs.end());
    }
    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool operator<=(const map<_Key, _Tp, _Compare, _Allocator>& __lhs,
                    const map<_Key, _Tp, _Compare, _Allocator>& __rhs)
    {
        return !(__rhs < __lhs);
    }
    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool operator>(const map<_Key, _Tp, _Compare, _Allocator>& __lhs,
                   const map<_Key, _Tp, _Compare, _Allocator>& __rhs)
    {
        return __rhs < __lhs;
    }
    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool operator>=(const map<_Key, _Tp, _Compare, _Allocator>& __lhs,
                    const map<_Key, _Tp, _Compare, _Allocator>& __rhs)
    {
        return !(__lhs < __rhs);
    }

    template <class _Key, class _Tp, class _Compare, class _Allocator>
    void swap(map<_Key, _Tp, _Compare, _Allocator>& __x,
              map<_Key, _Tp, _Compare, _Allocator>& __y)
    {
        __x.swap(__y);
    }
}

#endif /* MAP_HPP */
