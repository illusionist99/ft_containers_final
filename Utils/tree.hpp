#pragma once

# include <iostream>
# include "pair.hpp"

namespace ft {


    template < class Key,                           // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,               // map::key_compare
    class Alloc = std::allocator<T> > 
    struct node {

        node *_parent;
        node *_left;
        node *_right;
        node *_previous;
        int _height;
        pair<const Key, T> *_data;

        size_t  getHeight( void ) const { return _height; }
        int getBalance(node *N)
        {
            if (N == NULL)
                return 0;
            return height(N->_left) - height(N->_right);
        }
        node ( void ) {

            _parent = NULL;
            _left = NULL;
            _right = NULL;
            _previous = NULL;
            _height = 1;
            _data = NULL;
            
        }
        node(const node &obj) {
        
            _parent = obj._parent;
            _previous = obj._previous;
            _left = obj._left;
            _right = obj._right;
            _height = obj._height;
            _data = obj._data;
        }
        node &operator=(const node &obj) {
        
            _parent = obj._parent;
            _left = obj._left;
            _right = obj._right;
            _height = obj._height;
            _data = obj._data;
            return *this;
        }
    
        int max(int a, int b)
        {
            return (a > b)? a : b;
        }

        node<Key, T, Compare, Alloc>* insert(node<Key, T, Compare, Alloc>* node,
        const pair<const Key, T> &obj)
        {
            /* 1. Perform the normal BST insertion */
            if (node == NULL) {
                // _previous = NULL;
                return(newNode(obj));
            }
            if (obj.first < node->_data->first) {
                node->_previous = node->_left;
                node->_left = insert(node->_left, obj);
            }
            else if (obj.first > node->_data->first) {
                node->_previous = node->_right;
                node->_right = insert(node->_right, obj);
            }
            else // Equal keys are not allowed in BST
                return node;

            /* 2. Update height of this ancestor node */
            node->_height = 1 + max(height(node->_left), height(node->_right));

            /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
            int balance = getBalance(node);

            // If this node becomes unbalanced, then
            // there are 4 cases

            // Left Left Case
            if (balance > 1 && obj.first < node->_left->_data->first)
                return rightRotate(node);

            // Right Right Case
            if (balance < -1 && obj.first > node->_right->_data->first)
                return leftRotate(node);

            // Left Right Case
            if (balance > 1 && obj.first > node->_left->_data->first)
            {
                node->_left = leftRotate(node->_left);
                return rightRotate(node);
            }

            // Right Left Case
            if (balance < -1 && obj.first < node->_right->_data->first)
            {
                node->_right = rightRotate(node->_right);
                return leftRotate(node);
            }

            /* return the (unchanged) node pointer */
            return node;
        }

        node *next(node *root, int n) {
        
            if (root == NULL)
                return NULL;
            if (n == 0)
                return root->_parent;
            if (root->_left || root->_right) {
            
                if (root->_left && !root->_right)
                {
                    return root->_left;
                }
                else if (root->_right && !root->_left) { return root->_right; }
                else {
                
                    if (root->_data->first < root->_left->_data->first) { return next(root->_left, n - 1); }
                    else if (root->_data->first > root->_right->_data->first) { return next(root->_right, n - 1); }
                }
            }
            return NULL;
        }
        node *previous(node *root, int n) {
        
            if (root == NULL)
                return NULL;
            if (n == 0) return root->_parent;
            root = root->_parent;
            return (previous(root, n - 1));
        }
        typename Alloc::template rebind<pair<const Key, T> >::other rebind_allocator;


        node* newNode(pair<const Key, T> data)
        {
            node* Node = std::allocator<node>().allocate(1);
            Node->_data = rebind_allocator.allocate(1);
            Node->_data = &data;
            Node->_left = NULL;
            Node->_right = NULL;
            Node->_height = 1;
            Node->_parent = this;
            return (Node);
        }

        node *rightRotate(node *y)
        {
            if (y == NULL)
                return NULL;
            node *x = y->_left;
            if (x == NULL)
                return y;
            node *T2 = x->_right;
        
            // Perform rotation
            x->_right = y;
            y->_left = T2;
        
            // Update heights
            y->_height = max(height(y->_left),
                            height(y->_right)) + 1;
            x->_height = max(height(x->_left),
                            height(x->_right)) + 1;
        
            // Return new root
            return x;
        }
        int height(node *N)
        {
            if (N == NULL)
                return 0;
            return N->_height;
        }
        node *leftRotate(node *x)
        {
            node *y = x->_right;
            node *T2 = y->_left;
        
            // Perform rotation
            y->_left = x;
            x->_right = T2;
        
            // Update heights
            x->_height = max(height(x->_left),   
                            height(x->_right)) + 1;
            y->_height = max(height(y->_left),
                            height(y->_right)) + 1;
        
            // Return new root
            return y;
        }

        node *leftMostNode(node *root) {

            if (root == NULL)
                return NULL;
            return leftMostNode(root->_left);
        }

        node *rightMostNode(node *root) {

            if (root == NULL)
                return NULL;
            return rightMostNode(root->_right);
        }
    };

    template < class Key,                           // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,               // map::key_compare
    class Alloc = std::allocator<T> > 
    class tree {


        public:

        node<Key, T, Compare, Alloc> *_root;
        size_t                        _size;
        node<Key, T, Compare, Alloc> p;

            tree( void ) {
            
                _size = 0;
                _root = NULL;
            }
            tree(node<Key, T, Compare, Alloc> *root) {
            
                _root = root;
            }
            tree(const tree &obj) {
            
                _root = obj.getRoot();
                _size = obj.getSize();
            }

            tree &operator=(const tree &obj) {
            
                _root = obj.getRoot();
                _size = obj.getSize();
                return *this;
            }
            tree( pair<const Key, T> &data ) {
                _root = newNode(data);
            }
            void    insert(const pair<const Key, T> &data) {

                _root = _root->insert(_root, data);
                _size++;
            }
            size_t getSize( void ) const { return _size; }
            node<Key, T, Compare, Alloc> *leftMostNode( void ) const {

                if (_root == NULL)
                    return NULL;
                // node<Key, T, Compare, Alloc> *tmp = _root;
                tree tmp(_root);
            
                tmp._root = _root;

                while (tmp._root->_left != NULL)
                    tmp._root = tmp._root->_left;

                return  tmp._root->newNode(*(tmp._root->_data));
            }
            node<Key, T, Compare, Alloc> *getRoot( void ) const { return _root; }
            node<Key, T, Compare, Alloc> *rightMostNode( void ) const {
            
                if (_root == NULL)
                    return NULL;
                node<Key, T, Compare, Alloc> *tmp = _root;
        
                while (tmp->_right != NULL)
                    tmp = tmp->_right;

                return tmp;
            }
            ~tree( void ) { }        

    
    };
}
