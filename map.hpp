#ifndef MAP_HPP
#define MAP_HPP

#include "__tree.hpp"
#include "algorithm.hpp"
#include "utility.hpp"

namespace ft {
    template <class _Key, class _Tp, class _Compare = std::less<_Key>,
              class _Allocator = std::allocator<ft::pair<const _Key, _Tp> > >
    class map
    {
    public:
        // Member types
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
        typedef ft::__tree<value_type, key_compare, allocator_type> __base;
        __base __tree_;

    public:
        typedef typename __base::iterator               iterator;
        typedef typename __base::const_iterator         const_iterator;
        typedef std::reverse_iterator<iterator>         reverse_iterator;
        typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;
        typedef std::ptrdiff_t                          difference_type;
        typedef std::size_t                             size_type;

        // (constructor)
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
        {}
        // (destructor)
        ~map()
        {}
        // operator=
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
        bool empty() const
        {
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
        const_iterator upper_bound(const key_type& __k) const
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
    };

    // Non-member function overloads
    template <class _Key, class _Tp, class _Compare, class _Allocator>
    bool operator==(const map<_Key, _Tp, _Compare, _Allocator>& __lhs,
                    const map<_Key, _Tp, _Compare, _Allocator>& __rhs)
    {
        return __lhs.size() == __rhs.size() && ft::equal(__lhs.begin(), __lhs.end(), __rhs.begin());
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
