#pragma once

# include <iostream>
# include "pair.hpp"

namespace ft {

    template < class T,
    class Compare = std::less<typename T::first_type>,
    class Alloc = std::allocator<T> >
    class avl {
    
        struct avl_node {

            T               *data;
            struct avl_node *left;
            struct avl_node *right;
            size_t          height;
            struct avl_node *parent;
        };

        public:

            typedef typename Alloc::template rebind<avl_node>::other rebind_allocator;


            avl_node *root;
            Alloc _alloc;
            Compare _cmp;
            rebind_allocator _rebind_alloc;
        
            // avl() {}
            ~avl() {}

            int max(int left,int right)
            {
                return (left >= right) ? left : right;
            }

            avl_node* insert(T _data, avl_node* t) {
            
                if (t == NULL)
                {
                    t = _rebind_alloc.allocate(1);
                    t->data = _alloc.allocate(1);
                    _alloc.construct(t->data, _data);
                    t->height = 0;
                    t->left = t->right = NULL;
                }
                else if (_cmp(_data, *t->data))
                {
                    t->left = insert(_data, t->left);
                    if(height(t->left) - height(t->right) == 2)
                    {
                        if(_data < *t->left->data)
                            t = singleRightRotate(t);
                        else
                            t = doubleRightRotate(t);
                    }
                }
                else if (!_cmp(_data, *t->data))
                {
                    t->right = insert(_data, t->right);
                    if(height(t->right) - height(t->left) == 2)
                    {
                        if(_data > *t->right->data)
                            t = singleLeftRotate(t);
                        else
                            t = doubleLeftRotate(t);
                    }
                }

                t->height = max(height(t->left), height(t->right))+1;
                return t;
            }
            avl_node* singleRightRotate(avl_node* &t)
            {
                if (t == NULL)
                    return t;
                avl_node* u = t->left;
                if (u == NULL)
                    return t;
                t->left = u->right;
                u->right = t;
                t->height = max(height(t->left), height(t->right))+1;
                u->height = max(height(u->left), t->height)+1;
                return u;
            }

            avl_node* singleLeftRotate(avl_node* &t)
            {
                if (t == NULL)
                    return t;
                avl_node* u = t->right;
                if (u == NULL)
                    return t;
                t->right = u->left;
                u->left = t;
                t->height = max(height(t->left), height(t->right))+1;
                u->height = max(height(t->right), t->height)+1 ;
                return u;
            }

            avl_node* doubleLeftRotate(avl_node* &t)
            {
                t->right = singleRightRotate(t->right);
                return singleLeftRotate(t);
            }

            avl_node* doubleRightRotate(avl_node* &t)
            {
                t->left = singleLeftRotate(t->left);
                return singleRightRotate(t);
            }

            avl_node* &findMin(avl_node* t)
            {
                if (t == NULL)
                    return NULL;
                else if (t->left == NULL)
                    return t;
                else
                    return findMin(t->left);
            }

            avl_node* &findMax(avl_node* t)
            {
                if (t == NULL)
                    return NULL;
                else if (t->right == NULL)
                    return t;
                else
                    return findMax(t->right);
            }

            avl_node* remove(T _data, avl_node* t)
            {
                avl_node* temp;

                // Element not found
                if (t == NULL)
                    return NULL;

                // Searching for element
                else if (_data < t->data)
                    t->left = remove(_data->first, t->left);
                else if (_data > t->data)
                    t->right = remove(_data->first, t->right);

                // Element found
                // With 2 children
                else if (t->left && t->right)
                {
                    temp = findMin(t->right);
                    t->data = temp->data;
                    t->right = remove(t->data, t->right);
                }
                // With one or zero child
                else
                {
                    temp = t;
                    if (t->left == NULL)
                        t = t->right;
                    else if (t->right == NULL)
                        t = t->left;
                    delete temp;
                }
                if (t == NULL)
                    return t;

                t->height = max(height(t->left), height(t->right))+1;

                // If avl_node is unbalanced
                // If left avl_node is deleted, right case
                if (height(t->left) - height(t->right) == 2)
                {
                    // right right case
                    if (height(t->left->left) - height(t->left->right) == 1)
                        return singleLeftRotate(t);
                    // right left case
                    else
                        return doubleLeftRotate(t);
                }
                // If right avl_node is deleted, left case
                else if (height(t->right) - height(t->left) == 2)
                {
                    // left left case
                    if (height(t->right->right) - height(t->right->left) == 1)
                        return singleRightRotate(t);
                    // left right case
                    else
                        return doubleRightRotate(t);
                }
                return t;
            }

            int height(avl_node* t)
            {
                return (t == NULL ? -1 : t->height);
            }

            int getBalance(avl_node* t)
            {
                if(t == NULL)
                    return 0;
                else
                    return height(t->left) - height(t->right);
            }

            void inorder(avl_node* &t)
            {
                if(t == NULL)
                    return;
                inorder(t->left);
                std::cout << *t->data << " ";
                inorder(t->right);
            }

            avl()
            {
                root = NULL;
            }
            template <class Key>
            void insert(pair< Key, T> x)
            {
                root = insert(x.first, root);
            }
            template <class Key>
            void remove(pair< Key, T> x)
            {
                root = remove(x.first, root);
            }

            void display()
            {
                inorder(root);
                std::cout << std::endl;
            }
    };
}