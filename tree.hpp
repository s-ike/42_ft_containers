#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "iterator_traits.hpp"
#include "utility.hpp"

namespace ft {
    template <class _T>
    struct node
    {
        _T                  data;
        struct node<_T>*    parent;
        struct node<_T>*    left;
        struct node<_T>*    right;
        std::size_t         height;

        node()
            : data(NULL), parent(NULL), left(NULL), right(NULL), height(0)
        {}
        node(const _T& __data)
            : data(__data), parent(NULL), left(NULL), right(NULL), height(0)
        {}

        node<_T>* min_node(node<_T>* __node) const
        {
            node<_T>* __current = __node;

            while (__current->left != NULL)
                __current = __current->left;
            return __current;
        }
        node<_T>* max_node(node<_T>* __node) const
        {
            node<_T>* __current = __node;

            while (__current->right != NULL)
                __current = __current->right;
            return __current;
        }
        // TODO: 最大値を探したとき
        node<_T>* next_node(node<_T>* __node) const
        {
            if (__node->right != NULL)
                return min_node(__node->right);

            node<_T>* __p = __node->parent;
            while (__p != NULL && __node == __p->right)
            {
                __node = __p;
                __p = __p->parent;
            }
            return __p;
        }
        // TODO: 最小値を探したとき
        node<_T>* prev_node(node<_T>* __node) const
        {
            if (__node->left != NULL)
                return max_node(__node->left);

            node<_T>* __p = __node->parent;
            while (__p != NULL && __node == __p->left)
            {
                __node = __p;
                __p = __p->parent;
            }
            return __p;
        }
    };

    template <class _T>
    class tree_iterator : public std::iterator<std::bidirectional_iterator_tag, _T>
    {
    public:
        typedef typename ft::iterator_traits<_T>::value_type        value_type;
        typedef typename ft::iterator_traits<_T>::difference_type   difference_type;
        typedef typename ft::iterator_traits<_T>::pointer           pointer;
        typedef typename ft::iterator_traits<_T>::reference         reference;
        typedef typename ft::iterator_traits<_T>::iterator_category iterator_category;

    private:
        typedef node<value_type>    __node_type;
        __node_type* __i;

    public:
        tree_iterator()
            : __i(NULL)
        {}
        explicit tree_iterator(__node_type* __x)
            : __i(__x)
        {}
        template <class _Iter>
        tree_iterator(const tree_iterator<_Iter>& __x)
            : __i(__x.base())
        {}
        template <class _Iter>
        tree_iterator& operator=(const tree_iterator<_Iter>& __x)
        {
            __i = __x.base();
            return *this;
        }
        ~tree_iterator()
        {}

        reference operator*() const
        {
            return __i->data;
        }
        pointer operator->() const
        {
            return &__i->data;
        }
        tree_iterator& operator++()
        {
            __i = __i->next_node(__i);
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
            __i = __i->prev_node(__i);
            return *this;
        }
        tree_iterator operator--(int)
        {
            tree_iterator __tmp(*this);
            --(*this);
            return __tmp;
        }

        __node_type* base() const
        {
            return __i;
        }
    };

    template <class _T, class _Compare, class _Allocator = std::allocator<_T> >
    class tree
    {
    public:
        typedef _T          value_type;
        typedef _Compare    value_compare;
        typedef _Allocator  allocator_type;

        typedef typename allocator_type::size_type  size_type;
        typedef node<value_type>                    node_type;

        typedef ft::tree_iterator<_T*>          iterator;
        typedef ft::tree_iterator<const _T*>    const_iterator;

    private:
        typedef typename allocator_type::template
            rebind<node_type>::other    __node_allocator;

        node_type*          __root;
        size_type           __size;
        value_compare       __comp;
        __node_allocator    __alloc;

    public:
        explicit tree(const allocator_type& __alloc = allocator_type())
            : __root(NULL), __size(0), __comp(value_compare()), __alloc(__node_allocator(__alloc))
        {}
        explicit tree(const _Compare& __comp, const allocator_type& __alloc = allocator_type())
            : __root(NULL), __size(0), __comp(__comp), __alloc(__node_allocator(__alloc))
        {}
        ~tree()
        {
            __clear(__root);
            __root = NULL;
        }
        iterator begin()
        {
            return iterator(__root->min_node(__root));
        }
        size_type size() const
        {
            return __size;
        }
        node_type* search(const value_type& __data)
        {
            return __search_node(__root, __data);
        }
        node_type* insert(const value_type& __data)
        {
            __root = __insert_node(__root, __data);
            return __search_node(__root, __data);
        }
        void erase(_T __data)
        {
            __root = __erase_node(__root, __data);
        }

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
            print_in_order(__root);
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
        node_type* __search_node(node_type* __node, const value_type& __data)
        {
            if (__node == NULL)
                return NULL;
            if (__comp(__data.first, __node->data.first))
                return __search_node(__node->left, __data);
            else if (__comp(__node->data.first, __data.first))
                return __search_node(__node->right, __data);
            else
                return __node;
        }
        node_type* __new_node(const _T& __data)
        {
            node_type* __node = __alloc.allocate(1);
            __alloc.construct(__node, __data);
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
            // std::cout << "left: " << __height(__node->left) << ", right: " << __height(__node->right) << std::endl;
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

            // return new root
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

            // return new root
            return __y;
        }
        node_type* __insert_node(node_type* __node, const _T& __data)
        {
            /* 1. Perform the normal BST insertion */
            if (__node == NULL)
            {
                std::cout << "new node: (" << __data.first << ',' << __data.second << ')' << std::endl;
                __node = __new_node(__data);
                ++__size;
                std::cout << "new node done" << std::endl;
                return __node;
            }

            if (__comp(__data.first, __node->data.first))
            // if (__data.first < __node->data.first)
            {
                // std::cout << "else if (" << __data.first << " < " << __node->data.first << ")" << std::endl;
                __node->left = __insert_node(__node->left, __data);
                __node->left->parent = __node;
            }
            else if (__comp(__node->data.first, __data.first))
            // else if (__data.first > __node->data.first)
            {
                // std::cout << "else if (" << __data.first << " > " << __node->data.first << ")" << std::endl;
                __node->right = __insert_node(__node->right, __data);
                __node->right->parent = __node;
            }
            else    // Equal keys are not allowed in BST
                return __node;

            /* 2. Update height of this ancestor node */
            __node->height = 1 + std::max(__height(__node->left), __height(__node->right));

             /* 3. Get the balance factor of this ancestor
                   node to check whether this node became
                   unbalanced */
            int __balance = __get_balance(__node);
            // std::cout << "debug balance: " << __balance << std::endl;

            // If this node becomes unbalanced, then there are 4 cases

            // Left Left Case
            if (__balance > 1 && __comp(__data.first, __node->left->data.first))
            // if (__balance > 1 && __data.first < __node->left->data.first)
                return __right_rotate(__node);

            // Right Right Case
            if (__balance < -1 && __comp(__node->right->data.first, __data.first))
            // if (__balance < -1 && __data.first > __node->right->data.first)
                return __left_rotate(__node);

            // Left Right Case
            if (__balance > 1 && __comp(__node->left->data.first, __data.first))
            // if (__balance > 1 && __data.first > __node->left->data.first)
            {
                __node->left = __left_rotate(__node->left);
                return __right_rotate(__node);
            }

            // Right Left Case
            if (__balance < -1 && __comp(__data.first, __node->right->data.first))
            // if (__balance < -1 && __data.first < __node->right->data.first)
            {
                __node->right = __right_rotate(__node->right);
                return __left_rotate(__node);
            }

            return __node;
        }
        node_type* __min_node(node_type* __node)
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
                // std::cout << "delete: " << __node->data.first << std::endl;
                __delete_node(__node);
            }
        }
        void __delete_node(node_type* __node)
        {
            __alloc.destroy(__node);
            __alloc.deallocate(__node, 1);
            --__size;
        }
        node_type* __erase_node(node_type* __node, _T __data)
        {
            /* 1: PERFORM STANDARD BST DELETE */
            if (__node == NULL)
                return __node;

            // If the key to be deleted is smaller than the root's key, then it lies in left subtree
            // TODO: use comp
            if (__data.first < __node->data.first)
            {
                __node->left = __erase_node(__node->left, __data);
                // if (__node->left)
                //     __node->left->parent = __node;
            }
            // If the key to be deleted is greater than the root's key, then it lies in right subtree
            else if (__data.first > __node->data.first)
            {
                __node->right = __erase_node(__node->right, __data);
                // if (__node->right)
                //     __node->right->parent = __node;
            }
            //  if key is same as root's key, then this is the node to be deleted
            else
            {
                // node with only one child or no child
                if ((__node->left == NULL) || (__node->right == NULL))
                {
                    node_type* __temp = __node->left ? __node->left : __node->right;

                    // No child case
                    if (__temp == NULL)
                    {
                        __temp = __node;
                        __node = NULL;
                    }
                    else // One child case
                    {
                        node_type* __p = __node->parent;
                        *__node = *__temp; // Copy
                        __node->parent = __p;
                    }
                    __delete_node(__temp);
                }
                else
                {
                    node_type* __temp = __min_node(__node->right);

                    // Copy the inorder successor's data to this node
                    __node->data = __temp->data;

                    // Delete the inorder successor
                    __node->right = __erase_node(__node->right, __temp->data);
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
