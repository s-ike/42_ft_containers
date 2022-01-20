#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "iterator_traits.hpp"
#include "utility.hpp"

namespace ft {
    template <class _Tp>
    struct __node
    {
        typedef __node* __node_pointer;

        _Tp             data;
        __node_pointer  parent;
        __node_pointer  left;
        __node_pointer  right;
        std::size_t     height;

        __node()
            : data(), parent(NULL), left(NULL), right(NULL), height(0)
        {}
        __node(const _Tp& __data)
            : data(__data), parent(NULL), left(NULL), right(NULL), height(0)
        {}

        __node_pointer min_node(__node_pointer __node) const
        {
            __node_pointer __current = __node;

            while (__current->left != NULL)
                __current = __current->left;
            return __current;
        }
        __node_pointer max_node(__node_pointer __node) const
        {
            __node_pointer __current = __node;

            while (__current->right != NULL)
                __current = __current->right;
            return __current;
        }
        __node_pointer next_node(__node_pointer __node) const
        {
            if (__node->right != NULL)
                return min_node(__node->right);

            __node_pointer __p = __node->parent;
            while (__p != NULL && __node == __p->right)
            {
                __node = __p;
                __p = __p->parent;
            }
            return __p;
        }
        __node_pointer prev_node(__node_pointer __node) const
        {
            if (__node->left != NULL)
                return max_node(__node->left);

            __node_pointer __p = __node->parent;
            while (__p != NULL && __node == __p->left)
            {
                __node = __p;
                __p = __p->parent;
            }
            return __p;
        }
    };

    // _Tp = ft::pair<const _Key, _T>
    template <class _Tp>
    class __tree_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef _Tp                                 value_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef value_type&                         reference;
        typedef value_type*                         pointer;

        typedef __node<value_type>  __node_type;
        typedef __node_type*        __node_pointer;

    private:
        __node_pointer __ptr_;

    public:
        __tree_iterator()
            : __ptr_(NULL)
        {}
        explicit __tree_iterator(__node_pointer __x)
            : __ptr_(__x)
        {}
        __tree_iterator(const __tree_iterator& __x)
            : __ptr_(__x.base())
        {}
        __tree_iterator& operator=(const __tree_iterator& __x)
        {
            __ptr_ = __x.base();
            return *this;
        }
        ~__tree_iterator()
        {}

        reference operator*() const
        {
            return __ptr_->data;
        }
        pointer operator->() const
        {
            return &__ptr_->data;
        }

        __tree_iterator& operator++()
        {
            __ptr_ = __ptr_->next_node(__ptr_);
            return *this;
        }
        __tree_iterator operator++(int)
        {
            __tree_iterator __tmp(*this);
            ++(*this);
            return __tmp;
        }
        __tree_iterator& operator--()
        {
            __ptr_ = __ptr_->prev_node(__ptr_);
            return *this;
        }
        __tree_iterator operator--(int)
        {
            __tree_iterator __tmp(*this);
            --(*this);
            return __tmp;
        }

        bool operator==(const __tree_iterator& __x) const
        {
            return base() == __x.base();
        }
        bool operator!=(const __tree_iterator& __x) const
        {
            return !(base() == __x.base());
        }

        __node_pointer base() const
        {
            return __ptr_;
        }
    };

    template <class _Tp>
    class __tree_const_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef _Tp                                 value_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef const value_type&                   reference;
        typedef const value_type*                   pointer;

        typedef __node<value_type>  __node_type;
        typedef __node_type*        __node_pointer;

    private:
        typedef __tree_iterator<value_type> __non_const_iterator;

        __node_pointer __ptr_;

    public:
        __tree_const_iterator()
            : __ptr_(NULL)
        {}
        explicit __tree_const_iterator(__node_pointer __x)
            : __ptr_(__x)
        {}
        __tree_const_iterator(const __non_const_iterator& __x)
            : __ptr_(__x.base())
        {}
        __tree_const_iterator& operator=(const __tree_const_iterator& __x)
        {
            __ptr_ = __x.base();
            return *this;
        }
        ~__tree_const_iterator()
        {}

        reference operator*() const
        {
            return __ptr_->data;
        }
        pointer operator->() const
        {
            return &__ptr_->data;
        }

        __tree_const_iterator& operator++()
        {
            __ptr_ = __ptr_->next_node(__ptr_);
            return *this;
        }
        __tree_const_iterator operator++(int)
        {
            __tree_const_iterator __tmp(*this);
            ++(*this);
            return __tmp;
        }
        __tree_const_iterator& operator--()
        {
            __ptr_ = __ptr_->prev_node(__ptr_);
            return *this;
        }
        __tree_const_iterator operator--(int)
        {
            __tree_const_iterator __tmp(*this);
            --(*this);
            return __tmp;
        }

        bool operator==(const __tree_const_iterator& __x) const
        {
            return base() == __x.base();
        }
        bool operator!=(const __tree_const_iterator& __x) const
        {
            return !(base() == __x.base());
        }

        __node_pointer base() const
        {
            return __ptr_;
        }
    };

    // _Tp = ft::pair<const _Key, _Tp>
    template <class _Tp, class _Compare, class _Allocator = std::allocator<_Tp> >
    class __tree
    {
    public:
        typedef _Tp         value_type;
        typedef _Compare    key_compare;
        typedef _Allocator  allocator_type;

        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;
        typedef __node<value_type>                          node_type;

        typedef ft::__tree_iterator<_Tp>        iterator;
        typedef ft::__tree_const_iterator<_Tp>  const_iterator;

    private:
        typedef typename allocator_type::template
            rebind<node_type>::other    __node_allocator;

        node_type*          __end_;
        node_type*          __root_;
        size_type           __size_;
        key_compare         __comp_;
        __node_allocator    __alloc_;

    public:
        explicit __tree(const allocator_type& __alloc = allocator_type())
            : __end_(NULL), __root_(NULL), __size_(0), __comp_(key_compare()), __alloc_(__node_allocator(__alloc))
        {
            __init_tree();
        }
        explicit __tree(const _Compare& __comp, const allocator_type& __alloc = allocator_type())
            : __end_(NULL), __root_(NULL), __size_(0), __comp_(__comp), __alloc_(__node_allocator(__alloc))
        {
            __init_tree();
        }
        // Used in map copy constructor
        __tree(const __tree& __x)
            : __end_(NULL), __root_(NULL), __size_(0), __comp_(__x.__comp_), __alloc_(__x.__alloc_)
        {
            __init_tree();
            for (const_iterator __itr = __x.begin(); __itr != __x.end(); ++__itr)
                insert(*__itr);
        }
        ~__tree()
        {
            __clear(__root_);
            __root_ = NULL;
            __alloc_.destroy(__end_);
            __alloc_.deallocate(__end_, 1);
            __end_ = NULL;
        }
        // Used in map assignment
        __tree& operator=(const __tree& __x)
        {
            if (this != &__x)
            {
                __clear(__root_);
                __root_ = NULL;

                __comp_ = __x.__comp_;
                __alloc_ = __x.__alloc_;
                for (const_iterator __itr = __x.begin(); __itr != __x.end(); ++__itr)
                    insert(*__itr);
            }
            return *this;
        }

        // Iterators
        iterator begin()
        {
            return iterator(__end_->min_node(__end_));
        }
        const_iterator begin() const
        {
            return const_iterator(__end_->min_node(__end_));
        }
        iterator end()
        {
            return iterator(__end_);
        }
        const_iterator end() const
        {
            return const_iterator(__end_);
        }

        // Capacity
        size_type size() const
        {
            return __size_;
        }
        size_type max_size() const
        {
            return std::min(__alloc_.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));
        }

        node_type* search(const value_type& __data) const
        {
            return __search_node(__root_, __data);
        }
        template <class _Key>
        iterator find(const _Key& __k)
        {
            node_type* __find = __find_node(__root_, __k);
            if (__find && !__comp_(__k, __find->data.first))
                return iterator(__find);
            return end();
        }
        template <class _Key>
        const_iterator find(const _Key& __k) const
        {
            node_type* __find = __find_node(__root_, __k);
            if (__find && !__comp_(__k, __find->data.first))
                return const_iterator(__find);
            return end();
        }

        // Modifiers
        node_type* insert(const value_type& __data)
        {
            __root_ = __insert_node(__root_, __data);
            __end_->left = __root_;
            if (__root_)
                __root_->parent = __end_;
            return __search_node(__root_, __data);
        }
        void erase(_Tp __data)
        {
            __root_ = __erase_node(__root_, __data);
            __end_->left = __root_;
            if (__root_)
                __root_->parent = __end_;
        }
        void erase(iterator __p)
        {
            erase(*__p);
        }
        void erase(iterator __f, iterator __l)
        {
            while (__f != __l)
                erase(__f++);
        }
        template <class _Key>
        size_type erase_unique(const _Key& __k)
        {
            iterator __i = find(__k);
            if (__i == end())
                return 0;
            erase(__i);
            return 1;
        }
        void swap(__tree& __t)
        {
            __swap(__root_, __t.__root_);
            __swap(__end_, __t.__end_);
            __swap(__size_, __t.__size_);
            __swap(__comp_, __t.__comp_);
            __swap(__alloc_, __t.__alloc_);
        }
        void clear()
        {
            __clear(__root_);
            __root_ = NULL;
            __end_->left = __root_;
        }

        // Observers
        key_compare key_comp() const
        {
            return __comp_;
        }

        // Operations
        template <class _Key>
        iterator lower_bound(const _Key& __k)
        {
            return __lower_bound(__k);
        }
        template <class _Key>
        const_iterator lower_bound(const _Key& __k) const
        {
            return __lower_bound(__k);
        }
        template <class _Key>
        iterator upper_bound(const _Key& __k)
        {
            return __upper_bound(__k);
        }
        template <class _Key>
        const_iterator upper_bound(const _Key& __k) const
        {
            return __upper_bound(__k);
        }
        template <class _Key>
        pair<typename __tree<_Tp, _Compare, _Allocator>::iterator,
             typename __tree<_Tp, _Compare, _Allocator>::iterator>
        equal_range(const _Key& __k)
        {
            return __equal_range(__k);
        }
        template <class _Key>
        pair<typename __tree<_Tp, _Compare, _Allocator>::const_iterator,
             typename __tree<_Tp, _Compare, _Allocator>::const_iterator>
        equal_range(const _Key& __k) const
        {
            return __equal_range(__k);
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return allocator_type(__alloc_);
        }

        // Debug
        void print_from_root(node_type* __root) const
        {
            if(__root != NULL)
            {
                __print(__root);
                print_from_root(__root->left);
                print_from_root(__root->right);
            }
        }
        void print_all_in_order() const
        {
            print_in_order(__root_);
        }
        void print_in_order(node_type* __root) const
        {
            if (__root != NULL)
            {
                print_in_order(__root->left);
                __print_detail(__root);
                print_in_order(__root->right);
            }
        }

    private:
        void __init_tree()
        {
            __end_ = __alloc_.allocate(1);
            __alloc_.construct(__end_);
            __end_->left = NULL;
            __end_->right = NULL;
            __end_->parent = NULL;
            __end_->height = 0;
        }
        node_type* __search_node(node_type* __node, const value_type& __data) const
        {
            if (__node == NULL)
                return NULL;
            if (__comp_(__data.first, __node->data.first))
                return __search_node(__node->left, __data);
            else if (__comp_(__node->data.first, __data.first))
                return __search_node(__node->right, __data);
            else
                return __node;
        }
        template <class _Key>
        node_type* __find_node(node_type* __node, const _Key& __k) const
        {
            if (__node == NULL)
                return NULL;
            if (__comp_(__k, __node->data.first))
                return __find_node(__node->left, __k);
            else if (__comp_(__node->data.first, __k))
                return __find_node(__node->right, __k);
            else
                return __node;
        }
        node_type* __new_node(const _Tp& __data)
        {
            node_type* __node = __alloc_.allocate(1);
            __alloc_.construct(__node, __data);
            __node->left = NULL;
            __node->right = NULL;
            __node->parent = NULL;
            __node->height = 1; // new node is initially added at leaf
            return __node;
        }
        std::size_t __height(node_type* __node) const
        {
            if (__node == NULL)
                return 0;
            return __node->height;
        }
        int __get_balance(node_type* __node)
        {
            if (__node == NULL)
                return 0;
            return __height(__node->left) - __height(__node->right);
        }
        /*
                y      x
               /        \
              x    ->    y
               \        /
               t2      t2
        */
        node_type* __right_rotate(node_type* __y)
        {
            node_type* __p = __y->parent;
            node_type* __x = __y->left;
            node_type* __t2 = __x->right;

            __x->right = __y;
            __y->parent = __x;
            __y->left = __t2;
            __x->parent = __p;
            if (__t2)
                __t2->parent = __y;

            __y->height = std::max(__height(__y->left), __height(__y->right)) + 1;
            __x->height = std::max(__height(__x->left), __height(__x->right)) + 1;

            return __x;
        }
        /*
            x          y
             \        /
              y  ->  x
             /        \
            t2        t2
        */
        node_type* __left_rotate(node_type* __x)
        {
            node_type* __p = __x->parent;
            node_type* __y = __x->right;
            node_type* __t2 = __y->left;

            __y->left = __x;
            __x->parent = __y;
            __x->right = __t2;
            __y->parent = __p;
            if (__t2)
                __t2->parent = __x;

            __x->height = std::max(__height(__x->left), __height(__x->right)) + 1;
            __y->height = std::max(__height(__y->left), __height(__y->right)) + 1;

            return __y;
        }
        node_type* __insert_node(node_type* __node, const _Tp& __data)
        {
            /* 1. Perform the normal BST insertion */
            if (__node == NULL)
            {
                __node = __new_node(__data);
                ++__size_;
                return __node;
            }

            if (__comp_(__data.first, __node->data.first))  // std::less -> if (__data.first < __node->data.first)
            {
                __node->left = __insert_node(__node->left, __data);
                __node->left->parent = __node;
            }
            else if (__comp_(__node->data.first, __data.first)) // std::less -> if (__node->data.first < __data.first)
            {
                __node->right = __insert_node(__node->right, __data);
                __node->right->parent = __node;
            }
            else    // Equal keys are not allowed in BST
                return __node;

            /* 2. Update height of this ancestor node */
            __node->height = 1 + std::max(__height(__node->left), __height(__node->right));

             /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
            int __balance = __get_balance(__node);

            // If this node becomes unbalanced, then there are 4 cases

            // Left Left Case
            if (__balance > 1 && __comp_(__data.first, __node->left->data.first))
                return __right_rotate(__node);

            // Right Right Case
            if (__balance < -1 && __comp_(__node->right->data.first, __data.first))
                return __left_rotate(__node);

            // Left Right Case
            if (__balance > 1 && __comp_(__node->left->data.first, __data.first))
            {
                __node->left = __left_rotate(__node->left);
                return __right_rotate(__node);
            }

            // Right Left Case
            if (__balance < -1 && __comp_(__data.first, __node->right->data.first))
            {
                __node->right = __right_rotate(__node->right);
                return __left_rotate(__node);
            }

            return __node;
        }
        node_type* __min_node(node_type* __node) const
        {
            node_type* __current = __node;

            while (__current->left != NULL)
                __current = __current->left;
            return __current;
        }
        void __clear(node_type* __node)
        {
            if (__node)
            {
                __clear(__node->left);
                __clear(__node->right);
                __delete_node(__node);
            }
        }
        void __delete_node(node_type* __node)
        {
            __alloc_.destroy(__node);
            __alloc_.deallocate(__node, 1);
            --__size_;
        }
        node_type* __erase_node(node_type* __node, _Tp __data)
        {
            /* 1: PERFORM STANDARD BST DELETE */
            if (__node == NULL)
                return __node;

            // If the key to be deleted is smaller than the root's key, then it lies in left subtree
            if (__comp_(__data.first, __node->data.first))  // std::less -> if (__data.first < __node->data.first)
            {
                __node->left = __erase_node(__node->left, __data);
            }
            // If the key to be deleted is greater than the root's key, then it lies in right subtree
            else if (__comp_(__node->data.first, __data.first)) // std::less -> if (__node->data.first < __data.first)
            {
                __node->right = __erase_node(__node->right, __data);
            }
            //  if key is same as root's key, then this is the node to be deleted
            else
            {
                // node with only one child or no child
                if ((__node->left == NULL) || (__node->right == NULL))
                {
                    node_type* __child = __node->left ? __node->left : __node->right;

                    // No child case
                    if (__child == NULL)
                    {
                        __delete_node(__node);
                        __node = NULL;
                    }
                    else // One child case
                    {
                        node_type* __target = __node;
                        __child->parent = __target->parent;
                        if (__target->parent->right == __target)
                            __target->parent->right = __child;
                        else if (__target->parent->left == __target)
                            __target->parent->left = __child;
                        __delete_node(__target);
                        __node = __child;
                    }
                }
                else
                {
                    node_type* __new = __min_node(__node->right);
                    node_type* __target = __node;

                    // set the parent node of __new
                    if (__new->parent->left == __new)
                        __new->parent->left = NULL;
                    else if (__new->parent->right == __new)
                        __new->parent->right = NULL;
                    // set __new
                    if (__target->left)
                        __new->left = __target->left;
                    if (__target->right)
                        __new->right = __target->right;
                    __new->height = __target->height;
                    __new->parent = __target->parent;
                    // set the parent of __new child nodes
                    if (__new->left)
                        __new->left->parent = __new;
                    if (__new->right)
                        __new->right->parent = __new;
                    // set the child of the parent node of __new
                    if (__target->parent->left == __target)
                        __target->parent->left = __new;
                    else if (__target->parent->right == __target)
                        __target->parent->right = __new;
                    __delete_node(__target);
                    __node = __new;
                }
            }

            // if the tree had only one node then return
            if (__node == NULL)
                return __node;

            /* 2: UPDATE HEIGHT OF THE CURRENT NODE */
            __node->height = 1 + std::max(__height(__node->left), __height(__node->right));

            /* 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced) */
            int __balance = __get_balance(__node);

            // If this node becomes unbalanced, then there are 4 cases

            // Left Left Case
            if (__balance > 1 && __get_balance(__node->left) >= 0)
                return __right_rotate(__node);

            // Left Right Case
            if (__balance > 1 && __get_balance(__node->left) < 0)
            {
                __node->left = __left_rotate(__node->left);
                return __right_rotate(__node);
            }

            // Right Right Case
            if (__balance < -1 && __get_balance(__node->right) <= 0)
                return __left_rotate(__node);

            // Right Left Case
            if (__balance < -1 && __get_balance(__node->right) > 0)
            {
                __node->right = __right_rotate(__node->right);
                return __left_rotate(__node);
            }

            return __node;
        }
        template <class _U>
        void __swap(_U& __x, _U& __y)
        {
            _U __temp = __x;
            __x = __y;
            __y = __temp;
        }

        template <class _Key>
        iterator __lower_bound(const _Key& __k)
        {
            node_type* __result = __end_;
            node_type* __node = __root_;
            while (__node != NULL)
            {
                if (!__comp_(__node->data.first, __k))
                {
                    __result = __node;
                    __node = __node->left;
                }
                else
                    __node = __node->right;
            }
            return iterator(__result);
        }
        template <class _Key>
        const_iterator __lower_bound(const _Key& __k) const
        {
            node_type* __result = __end_;
            node_type* __node = __root_;
            while (__node != NULL)
            {
                if (!__comp_(__node->data.first, __k))
                {
                    __result = __node;
                    __node = __node->left;
                }
                else
                    __node = __node->right;
            }
            return const_iterator(__result);
        }
        template <class _Key>
        iterator __upper_bound(const _Key& __k)
        {
            node_type* __result = __end_;
            node_type* __node = __root_;
            while (__node != NULL)
            {
                if (__comp_(__k, __node->data.first))
                {
                    __result = __node;
                    __node = __node->left;
                }
                else
                    __node = __node->right;
            }
            return iterator(__result);
        }
        template <class _Key>
        const_iterator __upper_bound(const _Key& __k) const
        {
            node_type* __result = __end_;
            node_type* __node = __root_;
            while (__node != NULL)
            {
                if (__comp_(__k, __node->data.first))
                {
                    __result = __node;
                    __node = __node->left;
                }
                else
                    __node = __node->right;
            }
            return const_iterator(__result);
        }
        template <class _Key>
        pair<typename __tree<_Tp, _Compare, _Allocator>::iterator,
             typename __tree<_Tp, _Compare, _Allocator>::iterator>
        __equal_range(const _Key& __k)
        {
            typedef pair<iterator, iterator> _Pp;
            node_type* __result = __end_;
            node_type* __node = __root_;
            while (__node != NULL)
            {
                if (__comp_(__k, __node->data.first))
                {
                    __result = __node;
                    __node = __node->left;
                }
                else if (__comp_(__node->data.first, __k))
                    __node = __node->right;
                else
                {
                    return _Pp(iterator(__node),
                                iterator(
                                    __node->right != NULL ? __min_node(__node->right)
                                        : __result));
                }
            }
            return _Pp(iterator(__result), iterator(__result));
        }
        template <class _Key>
        pair<typename __tree<_Tp, _Compare, _Allocator>::const_iterator,
             typename __tree<_Tp, _Compare, _Allocator>::const_iterator>
        __equal_range(const _Key& __k) const
        {
            typedef pair<const_iterator, const_iterator> _Pp;
            node_type* __result = __end_;
            node_type* __node = __root_;
            while (__node != NULL)
            {
                if (__comp_(__k, __node->data.first))
                {
                    __result = __node;
                    __node = __node->left;
                }
                else if (__comp_(__node->data.first, __k))
                    __node = __node->right;
                else
                {
                    return _Pp(const_iterator(__node),
                                const_iterator(
                                    __node->right != NULL ? __min_node(__node->right)
                                        : __result));
                }
            }
            return _Pp(const_iterator(__result), const_iterator(__result));
        }

        void __print(node_type* __root) const
        {
            if (__root)
            {
                std::cout
                    << '['
                    << __root->data.first
                    << "] : "
                    << __root->data.second
                    << std::endl;
            }
        }
        void __print_detail(node_type* __root) const
        {
            if (__root)
            {
                std::cout
                    << '['
                    << __root->data.first
                    << "]: "
                    << __root->data.second
                    << " (p:";
                if (__root->parent)
                    std::cout << __root->parent->data.first;
                else
                    std::cout << '_';
                std::cout << ",L:";
                if (__root->left)
                    std::cout << __root->left->data.first;
                else
                    std::cout << '_';
                std::cout << ",R:";
                if (__root->right)
                    std::cout << __root->right->data.first;
                else
                    std::cout << '_';
                std::cout
                    << ",h:"
                    << __root->height
                    << ')'
                    << std::endl;
            }
        }
    };
}

#endif /* TREE_HPP */
