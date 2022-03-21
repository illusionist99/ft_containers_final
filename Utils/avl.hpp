#pragma once


# include <iostream>
# include "pair.hpp"
namespace ft {

    // An AVL tree node
    template < class Key,                           // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,               // map::key_compare
    class Alloc = std::allocator<pair<const Key,T> > > 
    class Node
    {

        
        public:
            typename Alloc::template rebind<Node<Key, T> >::other rebind_allocator;

            Alloc _allocator;
            Key _key;
            T _data;
            Node *_left;
            Node *_right;
            int _height;
            Node *_parrent;
            int height(Node *N)
            {
                if (N == NULL)
                    return 0;
                return N->_height;
            }
            
            // A utility function to get maximum
            // of two integers
            int max(int a, int b)
            {
                return (a > b)? a : b;
            }
            
            /* Helper function that allocates a
            new node with the given key and
            NULL left and right pointers. */
            Node* newNode(Key key)
            {
                Node* node = rebind_allocator.allocate(1);
                node->_key = key;
                node->_left = NULL;
                node->_right = NULL;
                node->_height = 1; // new node is initially
                node->_parrent = this;               // added at leaf
                return(node);
            }
            
            // A utility function to right
            // rotate subtree rooted with y
            // See the diagram given above.
            Node *rightRotate(Node *y)
            {
                Node *x = y->_left;
                Node *T2 = x->_right;
            
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
            
            // A utility function to left
            // rotate subtree rooted with x
            // See the diagram given above.
            Node *leftRotate(Node *x)
            {
                Node *y = x->_right;
                Node *T2 = y->_left;
            
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
            
            // Get Balance factor of node N
            int getBalance(Node *N)
            {
                if (N == NULL)
                    return 0;
                return height(N->_left) - height(N->_right);
            }
            
            // Recursive function to insert a key
            // in the subtree rooted with node and
            // returns the new root of the subtree.
            Node* insert(Node* node, Key key)
            {
                /* 1. Perform the normal BST insertion */
                if (node == NULL)
                    return(newNode(key));
            
                if (key < node->_key)
                    node->_left = insert(node->_left, key);
                else if (key > node->_key)
                    node->_right = insert(node->_right, key);
                else // Equal keys are not allowed in BST
                    return node;
            
                /* 2. Update height of this ancestor node */
                node->_height = 1 + max(height(node->_left),
                                    height(node->_right));
            
                /* 3. Get the balance factor of this ancestor
                    node to check whether this node became
                    unbalanced */
                int balance = getBalance(node);
            
                // If this node becomes unbalanced, then
                // there are 4 cases
            
                // Left Left Case
                if (balance > 1 && key < node->_left->_key)
                    return rightRotate(node);
            
                // Right Right Case
                if (balance < -1 && key > node->_right->_key)
                    return leftRotate(node);
            
                // Left Right Case
                if (balance > 1 && key > node->_left->_key)
                {
                    node->_left = leftRotate(node->_left);
                    return rightRotate(node);
                }
            
                // Right Left Case
                if (balance < -1 && key < node->_right->_key)
                {
                    node->_right = rightRotate(node->_right);
                    return leftRotate(node);
                }
            
                /* return the (unchanged) node pointer */
                return node;
            }
        };
    
    
    // A utility function to get the
    // height of the tree
    
}

