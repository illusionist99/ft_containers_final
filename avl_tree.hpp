# pragma once

# include <iostream>

// each node of avl tree has
// parent 
// left and right
// height
// Data (pair)

struct node {

    struct node *parent;
    struct node *right;
    struct node *left;

    int height;
    int data;

};

class avl
{
    private:
    // public:

        node * _root;

    public:

        avl() {
        
            _root = nullptr;
        }
        ~avl() {

        }

        int max(int a, int b) { return a > b ? a : b;}
        int height(node *node) { if (!node) return 0; return node->height; };
    
        node *allocateNode( int data ) {
        
            node * n = new node();
        
            n->data = data;
            n->parent = nullptr;
            n->right = nullptr;
            n->left = nullptr;
            n->height = 1;
            
            return (n);
        }
        int     getBalance(node *n) {
        
            if (n == nullptr)
                return 0;
            return (height(n->left) - height(n->right));
        }

        node *rightRotate(node *y)
        {
            node *x = y->left;
            node *T2 = x->right;
        
            // Perform rotation
            x->right = y;
            y->left = T2;
        
            // Update heights
            y->height = max(height(y->left), height(y->right)) + 1;
            x->height = max(height(x->left),height(x->right)) + 1;
        
            // Return new root
            return x;
        }
        
        // A utility function to left
        // rotate subtree rooted with x
        // See the diagram given above.
        node *leftRotate(node *x)
        {
            node *y = x->right;
            
            node *T2 = (y == NULL) ? NULL : y->left;
        
            // Perform rotation
            y->left = x;
            x->right = T2;
    
            // Update heights
            x->height = max(height(x->left), height(x->right)) + 1;
            y->height = max(height(y->left), height(y->right)) + 1;
            // Return new root
            return y;
        }
 
        node    *insertNode(node *root, int data ) {
        
            if (root == nullptr) {

                return allocateNode(data);
            }
            
            if (data < root->data) {
        
                root->left = insertNode(root->left, data);
            }
            else if (data > root->data) {
            
                root->right = insertNode(root->right, data);
            }
            else
                return root;
            root->height = 1 + max(height(root->left), height(root->right));
        
            int balance = getBalance(root);
 
            // If this node becomes unbalanced, then
            // there are 4 cases
        
            // Left Left Case
            if (balance > 1  && data < root->left->data)
                return rightRotate(root);
        
            // Right Right Case
            if (balance < -1  && data > root->right->data)
                return leftRotate(root);
        
            // Left Right Case
            if (balance > 1  && data > root->left->data)
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        
            // Right Left Case
            if (balance < -1   && data < root->right->data)
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        
            /* return the (unchanged) node pointer */
            return root;
        }

        void    insert(int data) {
        
            _root = insertNode(_root, data);
        }

        // void    deleteNode(int data) {
        
        
        // }

        // Function to print binary tree in 2D
        // It does reverse inorder traversal
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
            std::cout<<root->data<<"\n";
        
            // Process left child
            print2DUtil(root->left, space);
        }
        
        // Wrapper over print2DUtil()
        void print2D( void )
        {
            // Pass initial space count as 0
            print2DUtil(_root, 0);
        }
 

};
