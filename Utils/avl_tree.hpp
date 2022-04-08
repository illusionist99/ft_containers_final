#pragma once

# include "pair.hpp"
# include <iostream>

namespace ft {

    template < class Key,
    class T>
    struct BstNode {

        int height;
        pair<const Key, T> *data;
        BstNode *left;
        BstNode *right;
        BstNode *parent;
    };

    template < class Key,
    class T,
    class Compare = std::less<Key>,
    class Alloc = std::allocator<T> >
    class BstTree {
public:
        typedef    BstNode<Key, T> BstNode;
        BstNode *_root;
    
        typedef typename Alloc::template rebind<BstNode>::other rebind_allocator;
        typedef typename Alloc::template rebind<pair<const Key, T> >::other _allocator;
        rebind_allocator _NodeAlloc;
        _allocator  _PairAlloc;
        Compare _cmp;

        public:

        BstTree( void ) {
        
            _root  = NULL;
        }

        BstNode*    TreeSearch(BstNode *x, pair<const Key, T> data) {
        
            if (x == NULL || x->data == data)
                return x;
            if (_cmp(data.first, x->data->first))
                return TreeSearch(x->left, data);
            else
                return TreeSearch(x->right, data);
        }

        BstNode *TreeMaximum(BstNode *x) {
        
            while (x && x->right != NULL)
            {
                x = x->right;
            }
            return x;
        }
        BstNode *TreeMinimum(BstNode *x) {
        
            while (x && x->left != NULL)
            {
                x = x->left;
            }
            return x;
        }
        BstNode *TreePredecessor(BstNode *x) {
        
            if (x->left != NULL)
                return TreeMaximum(x->left);
            BstNode *y = x->parent;
        
            while (y != NULL && (x == y->left))
            {
                x = y;
                y = y->parent;
            }
            return y;
        }
        BstNode *TreeSuccesor(BstNode *x) {
        
            if (x == NULL)
                return x;
            if (x->right != NULL)
                return TreeMinimum(x->right);
            BstNode *y = x->parent;
            while (y != NULL && (x == y->right))
            {
                x = y;
                y = y->parent;
            }
            return y;
        }

        void InorderTreeWalk( BstNode *x, char *msg) {
        
            if (x != NULL) {
            
                InorderTreeWalk(x->left, " left");
                std::cout << "data: " << (char )x->data->first << " Parent : " << x->parent << " at :" << msg << std::endl;
                InorderTreeWalk(x->right, " right");
            }
        }


        int bf(BstNode *n){
            if(n->left && n->right){
                return n->left->height - n->right->height; 
            }
            else if(n->left && n->right == NULL){
                return n->left->height; 
            }
            else if(n->left== NULL && n->right ){
                return -n->right->height;
            }
            return 0;
        }

        BstNode * llrotation(BstNode *n){
            BstNode *p;
            BstNode *tp;
            p = n;
            tp = p->left;

            p->left = tp->right;
            tp->right = p;

            return tp; 
        }


        BstNode * rrrotation(BstNode *n){
            BstNode *p;
            BstNode *tp;
            p = n;
            tp = p->right;

            p->right = tp->left;
            tp->left = p;

            return tp; 
        }


        BstNode * rlrotation(BstNode *n){
            BstNode *p;
            BstNode *tp;
            BstNode *tp2;
            p = n;
            tp = p->right;
            tp2 =p->right->left;

            p -> right = tp2->left;
            tp ->left = tp2->right;
            tp2 ->left = p;
            tp2->right = tp; 
            
            return tp2; 
        }

        BstNode * lrrotation(BstNode *n){
            BstNode *p;
            BstNode *tp;
            BstNode *tp2;
            p = n;
            tp = p->left;
            tp2 =p->left->right;

            p -> left = tp2->right;
            tp ->right = tp2->left;
            tp2 ->right = p;
            tp2->left = tp; 
            
            return tp2; 
        }

        int calheight(BstNode *p){

                if(p->left && p->right){
                if (p->left->height < p->right->height)
                    return p->right->height + 1;
                else return  p->left->height + 1;
                }
                else if(p->left && p->right == NULL){
                return p->left->height + 1;
                }
                else if(p->left ==NULL && p->right){
                return p->right->height + 1;
                }
                return 0;

        }
        int max(int a, int b)
        {
            return (a > b)? a : b;
        }
    
    // A utility function to get the
    // height of the tree
    int height(BstNode *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }
        BstNode *rightRotate(BstNode *y)
        {
            BstNode *x = y->left;
            BstNode *T2 = x->right;
        
            // Perform rotation
            x->right = y;
            y->left = T2;
        
            // Update heights
            y->height = max(height(y->left),
                            height(y->right)) + 1;
            x->height = max(height(x->left),
                            height(x->right)) + 1;
        
            // Return new root
            return x;
        }
        int getBalance(BstNode *N)
        {
            if (N == NULL)
                return 0;
            return height(N->left) - height(N->right);
        }
        // A utility function to left
        // rotate subtree rooted with x
        // See the diagram given above.
        BstNode *leftRotate(BstNode *x)
        {
            BstNode *y = x->right;
            BstNode *T2 = y->left;
        
            // Perform rotation
            y->left = x;
            x->right = T2;
        
            // Update heights
            x->height = max(height(x->left),   
                            height(x->right)) + 1;
            y->height = max(height(y->left),
                            height(y->right)) + 1;
        
            // Return new root
            return y;
        }
        void    insert(BstTree  &src, pair<const Key, T> data) {
        
            BstNode *y = nullptr;
            BstNode *x = src._root;
            BstNode *n = _NodeAlloc.allocate(1);
            n->data = _PairAlloc.allocate(1);
            _PairAlloc.construct(n->data, data);
            n->left = NULL;
            n->right = NULL;
            n->height = 1;
            while (x != NULL)
            {
                y = x;
                if (_cmp(n->data->first, x->data->first))
                    x = x->left;
                else
                    x = x->right;
            }
            n->parent = y;

            if (y == NULL)
                src._root = n;
            else if (_cmp(n->data->first, y->data->first))
                y->left = n;
            else
                y->right = n;            
            src._root->height = 1 + max(height(src._root->left), height(src._root->right));
            int balance = getBalance(src._root);
            std::cout << "Balance " << balance << std::endl;
            // If this src._root becomes unbalanced, then
            // there are 4 cases
        
            // Left Left Case
            if (balance > 1 && _cmp(n->data->first, src._root->left->data->first))
                src._root = rightRotate(src._root);
        
            // Right Right Case
            if (balance < -1 && !_cmp(n->data->first, src._root->right->data->first))
                src._root = leftRotate(src._root);
        
            // Left Right Case
            if (balance > 1 && !_cmp(n->data->first, src._root->left->data->first))
            {
                src._root->left = leftRotate(src._root->left);
                src._root = rightRotate(src._root);
            }
        
            // Right Left Case
            if (balance < -1 && _cmp(n->data->first, src._root->right->data->first))
            {
                src._root->right = rightRotate(src._root->right);
                src._root = leftRotate(src._root);
            }
        }

        void    SubTreeShift(BstTree const &src, BstNode *u, BstNode *v) {
        
            if (u->parent == NULL)
                src._root = v;
            else if ((u == u->parent->left))
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v == NULL)
                v->parent = u->parent;
        }

        void    TreeDelete(BstTree const &src, BstNode *z) {
        
            if (z->left == NULL)
                SubTreeShift(src, z, z->right);
            else if (z->right == NULL)
                SubTreeShift(src, z, z->left);
            else {
            
                BstNode * y = TreeSuccesor(z);
                if (y->parent != z) {
                
                    SubTreeShift(src, y,y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                SubTreeShift(src, z, y);
                y->left = z->left;
                y->left->parent = y;
            }
        }

        BstTree(const BstTree &obj) {
        
            _root  = obj._root;
        }
        BstTree &operator=(const BstTree& obj) {
        
            *this = obj;
            return *this;
        }
        ~BstTree() {
        
        }
    };
};