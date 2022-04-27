# pragma once

# include <iostream>
# include "pair.hpp"

namespace ft {



    // AVL tree node
    template<class Key, class T>
    struct node {

        node* left;
        node* right;
        int key;
        pair<Key, T> *data;
        node* parent;
        int height;
    };

    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
    class avl {
    
        typedef node< Key, T> node;
        
        typedef typename Alloc::template rebind<node>::other rebind_allocator;
        typedef typename Alloc::template rebind<pair<Key, T> >::other _allocator;
    
        rebind_allocator _NodeAlloc;
        _allocator  _PairAlloc;
        Compare _cmp;
    public: 

        // node *root;
        avl() {} 
            // root = NULL; }
        int max( int a, int b) { return a > b ?  a : b; }
        // Function to print the preorder
        // traversal of the AVL tree
        void printpreorder(node* root)
        {
            // Print the node's value along
            // with its parent value
            std::cout << "Node: " << root->data->first << ", Parent Node: ";
        
            if (root->parent != NULL)
                std::cout << root->parent->data->first << std::endl;
            else
                std::cout << "NULL" << std::endl;
        
            // Recur to the left subtree
            if (root->left != NULL) {
                printpreorder(root->left);
            }
        
            // Recur to the right subtree
            if (root->right != NULL) {
                printpreorder(root->right);
            }
        }
    
    // Function to update the height of
    // a node according to its children's
    // node's heights
    void Updateheight(node* root)
    {
        if (root != NULL) {
    
            // Store the height of the
            // current node
            int val = 1;
    
            // Store the height of the left
            // and right substree
            if (root->left != NULL)
                val = root->left->height + 1;
    
            if (root->right != NULL)
                val = max(val, root->right->height + 1);
    
            // Update the height of the
            // current node
            root->height = val;
        }
    }
    
        node* LLR(node* root) {
            // Create a reference to the
            // left child
            node* tmpnode = root->left;

            // Update the left child of the
            // root to the right child of the
            // current left child of the root
            root->left = tmpnode->right;

            // Update parent pointer of the
            // left child of the root node
            if (tmpnode->right != NULL)
                tmpnode->right->parent = root;

            // Update the right child of
            // tmpnode to root
            tmpnode->right = root;

            // Update parent pointer of
            // the tmpnode
            tmpnode->parent = root->parent;

            // Update the parent pointer
            // of the root
            root->parent = tmpnode;

            // Update tmpnode as the left or the
            // right child of its parent pointer
            // according to its key value
            if (tmpnode->parent != NULL
                && _cmp(root->key, tmpnode->parent->key)) {
                tmpnode->parent->left = tmpnode;
            }
            else {
                if (tmpnode->parent != NULL)
                    tmpnode->parent->right = tmpnode;
            }

            // Make tmpnode as the new root
            root = tmpnode;

            // Update the heights
            Updateheight(root->left);
            Updateheight(root->right);
            Updateheight(root);
            Updateheight(root->parent);

            // Return the root node
            return root;
        }

        // Function to handle Right Right Case
        node* RRR(node* root) {
            // Create a reference to the
            // right child
            node* tmpnode = root->right;

            // Update the right child of the
            // root as the left child of the
            // current right child of the root
            root->right = tmpnode->left;

            // Update parent pointer of the
            // right child of the root node
            if (tmpnode->left != NULL)
                tmpnode->left->parent = root;

            // Update the left child of the
            // tmpnode to root
            tmpnode->left = root;

            // Update parent pointer of
            // the tmpnode
            tmpnode->parent = root->parent;

            // Update the parent pointer
            // of the root
            root->parent = tmpnode;

            // Update tmpnode as the left or
            // the right child of its parent
            // pointer according to its key value
            if (tmpnode->parent != NULL
                && _cmp(root->key, tmpnode->parent->key)) {
                tmpnode->parent->left = tmpnode;
            }
            else {
                if (tmpnode->parent != NULL)
                    tmpnode->parent->right = tmpnode;
            }

            // Make tmpnode as the new root
            root = tmpnode;

            // Update the heights
            Updateheight(root->left);
            Updateheight(root->right);
            Updateheight(root);
            Updateheight(root->parent);

            // Return the root node
            return root;
        }

        // Function to handle Left Right Case
        node* LRR( node* root ) {
            
            root->left = RRR(root->left);
            return LLR(root);
        }

        // Function to handle right left case
        node* RLR( node* root ) {
        
            root->right = LLR(root->right);
            return RRR(root);
        }

    // Function to balance the tree after
    // deletion of a node
    node* Balance(node* root)
    {
        // Store the current height of
        // the left and right subtree
        int firstheight = 0;
        int secondheight = 0;
    
        if (root->left != NULL)
            firstheight = root->left->height;
    
        if (root->right != NULL)
            secondheight = root->right->height;
    
        // If current node is not balanced
        if (abs(firstheight - secondheight) == 2) {
            if (firstheight < secondheight) {
    
                // Store the height of the
                // left and right subtree
                // of the current node's
                // right subtree
                int rightheight1 = 0;
                int rightheight2 = 0;
                if (root->right->right != NULL)
                    rightheight2 = root->right->right->height;
    
                if (root->right->left != NULL)
                    rightheight1 = root->right->left->height;
    
                if (rightheight1 > rightheight2) {
    
                    // Right Left Case
                    root = RLR(root);
                }
                else {
    
                    // Right Right Case
                    root = RRR(root);
                }
            }
            else {
    
                // Store the height of the
                // left and right subtree
                // of the current node's
                // left subtree
                int leftheight1 = 0;
                int leftheight2 = 0;
                if (root->left->right != NULL)
                    leftheight2 = root->left->right->height;
    
                if (root->left->left != NULL)
                    leftheight1 = root->left->left->height;
    
                if (leftheight1 > leftheight2) {
    
                    // Left Left Case
                    root = LLR(root);
                }
                else {
    
                    // Left Right Case
                    root = LRR(root);
                }
            }
        }
    
        // Return the root node
        return root;
    }
    node *TreeMinimum(node *root)  {
    
        if (root)
            while (root->left != NULL)
                root = root->left;
        return root;
    }
    // void insert(pair<Key, T> key) {

    //     root = Insert(root, root, key);
    // }

    // Function to insert a node in
    // the AVL tree
    node* Insert(node* root, node* parent, pair<Key, T> key)
    {
        if (root == NULL) {
    
            // Create and assign values
            // to a new node
            root = _NodeAlloc.allocate(1);
            root->data = _PairAlloc.allocate(1);
            _PairAlloc.construct(root->data, key);
            if (root == NULL)
                std::cout << "Error in memory" << std::endl;
            else {
                root->height = 1;
                root->left = NULL;
                root->right = NULL;
                root->parent = parent;
                // root->data = &key;
            }
            // return root;
        }
        else if (!_cmp(root->data->first, key.first)) {
    
            // Recur to the left subtree
            // to insert the node
            root->left = Insert(root->left, root, key);
    
            // Store the heights of the
            // left and right subtree
            int firstheight = 0;
            int secondheight = 0;
    
            if (root->left != NULL)
                firstheight = root->left->height;
    
            if (root->right != NULL)
                secondheight = root->right->height;
    
            // Balance the tree if the
            // current node is not balanced
            if (abs(firstheight - secondheight) == 2) {
    
                if (root->left != NULL && _cmp(key.first, root->left->data->first)) {
    
                    // Left Left Case
                    root = LLR(root);
                }
                else {
    
                    // Left Right Case
                    root = LRR(root);
                }
            }
        }
        else if (_cmp(root->data->first, key.first)) {
    
            // Recur to the right subtree
            // to insert the node
            root->right = Insert(root->right, root, key);
    
            // Store the heights of the left
            // and right subtree
            int firstheight = 0;
            int secondheight = 0;
    
            if (root->left != NULL)
                firstheight = root->left->height;
    
            if (root->right != NULL)
                secondheight = root->right->height;
    
            // Balance the tree if the
            // current node is not balanced
            if (abs(firstheight - secondheight) == 2) {
                if (root->right != NULL  && _cmp(key.first, root->right->data->first)) {
    
                    // Right Left Case
                    root = RLR(root);
                }
                else {
    
                    // Right Right Case
                    root = RRR(root);
                }
            }
        }
    
        // Case when given key is
        // already in tree
        else {
        }
    
        // Update the height of the
        // root node
        Updateheight(root);
    
        // Return the root node
        return root;
    }
    
    // Function to delete a node from
    // the AVL tree
    node* Delete(node* root, pair<Key, T> key)
    {
        if (root != NULL) {
    
            // If the node is found
            if (root->data->first == key.first) {
    
                // Replace root with its
                // left child
                if (root->right == NULL && root->left != NULL) {
                    
                    if (root->parent != NULL) {
                        
                        if (_cmp(root->parent->data->first, root->data->first))
                            root->parent->right = root->left;
                        else
                            root->parent->left = root->left;
    
                        // Update the height
                        // of root's parent
                        Updateheight(root->parent);
                    }
    
                    root->left->parent = root->parent;
    
                    // Balance the node
                    // after deletion
                    root->left = Balance(root->left);
    
                    return root->left;
                }
    
                // Replace root with its
                // right child
                else if (root->left == NULL && root->right != NULL) {
                
                    if (root->parent != NULL) {
                    
                        if (_cmp(root->parent->data->first, root->data->first))
                            root->parent->right = root->right;
                        else
                            root->parent->left = root->right;
    
                        // Update the height
                        // of the root's parent
                        Updateheight(root->parent);
                    }
    
                    root->right->parent = root->parent;
    
                    // Balance the node after
                    // deletion
                    root->right = Balance(root->right);
                    return root->right;
                }
    
                // Remove the references of
                // the current node
                else if (root->left == NULL && root->right == NULL) {
                    
                    if (_cmp(root->parent->data->first, root->data->first)) {
                        root->parent->right = NULL;
                    }
                    else {
                        root->parent->left = NULL;
                    }
    
                    if (root->parent != NULL)
                        Updateheight(root->parent);
    
                    root = NULL;
                    return NULL;
                }
    
                // Otherwise, replace the
                // current node with its
                // successor and then
                // recursively call Delete()
                else {
                    node* tmpnode = root;
                    tmpnode = tmpnode->right;
                    while (tmpnode->left != NULL) {
                        tmpnode = tmpnode->left;
                    }
    
                    Key val = tmpnode->data->first;
    
                    root->right = Delete(root->right, *tmpnode->data);
    
                    root->data->first = val;
    
                    // Balance the node
                    // after deletion
                    root = Balance(root);
                }
            }
    
            // Recur to the right subtree to
            // delete the current node
            else if (_cmp(root->data->first, key.first)) {

                root->right = Delete(root->right, key);
                root = Balance(root);
            }
    
            // Recur into the right subtree
            // to delete the current node
            else if (!_cmp(root->data->first, key.first)) {
                root->left = Delete(root->left, key);
    
                root = Balance(root);
            }
    
            // Update height of the root
            if (root != NULL) {
                Updateheight(root);
            }
        }
    
        // Handle the case when the key to be
        // deleted could not be found
        else {
            std::cout << "Key to be deleted " << "could not be found\n";
        }
    
        // Return the root node
        return root;
    }
        void print2DUtil(node *root, int space)
            {
                // Base case
                if (root == NULL)
                    return; 
            
                // Increase distance between levels
                space += 5;
            
                // Process right child first
                print2DUtil(root->right, space);
            
                // Print current node after space
                // count
                std::cout << std::endl;
                for (int i = 1; i < space; i++)
                    std::cout<<" ";
                std::cout<<root->data->first<<" ";
                std::cout << root->parent << "\n";
                // Process left child
                print2DUtil(root->left, space);
            }
            
            // Wrapper over print2DUtil()
            void print2D( node *root )
            {
                // Pass initial space count as 0
                print2DUtil(root, 0);
            }
    };
}