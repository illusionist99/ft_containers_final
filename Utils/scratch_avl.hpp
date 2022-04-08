#pragma once

# include <iostream>
# include "pair.hpp"
#include <functional>
# include <queue>
namespace ft {


    template < class Key,
    class T,
    class Compare = std::less<Key>,
    class Alloc = std::allocator<T> >
    class avl {

        public:
        
            struct avl_node {

                // T               *data;
                pair<const Key, T>    *data;
                struct avl_node *left;
                struct avl_node *right;
                size_t          height;
                struct avl_node *parent;

                avl_node() {
                
                    data = NULL;
                    left = NULL;
                    right = NULL;
                    height = 0;
                    parent = NULL;
                }
            };

        // template <typename A, typename B, typename U = Compare>
        // bool _cmp(A a, B b, U u = U())
        // {
        //     return u(a, b);
        // }

        // public:

            typedef typename Alloc::template rebind<avl_node>::other rebind_allocator;
            typedef typename Alloc::template rebind<pair<const Key, T> >::other _allocator;


            avl_node *root;
            _allocator _alloc;
            Compare _cmp;
            rebind_allocator _rebind_alloc;
        
            // avl() {}
            ~avl() {}

            int max(int left,int right)
            {
                return (left >= right) ? left : right;
            }
            int calheight(avl_node *p){

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

                int bf(avl_node *n){
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

                avl_node * llrotation(avl_node *n){
                    avl_node *p;
                    avl_node *tp;
                    p = n;
                    tp = p->left;

                    p->left = tp->right;
                    tp->right = p;

                    return tp; 
                }


                avl_node * rrrotation(avl_node *n){
                    avl_node *p;
                    avl_node *tp;
                    p = n;
                    tp = p->right;

                    p->right = tp->left;
                    tp->left = p;

                    return tp; 
                }


                avl_node * rlrotation(avl_node *n){
                    avl_node *p;
                    avl_node *tp;
                    avl_node *tp2;
                    p = n;
                    tp = p->right;
                    tp2 =p->right->left;

                    p -> right = tp2->left;
                    tp ->left = tp2->right;
                    tp2 ->left = p;
                    tp2->right = tp; 
                    
                    return tp2; 
                }

                avl_node * lrrotation(avl_node *n){
                    avl_node *p;
                    avl_node *tp;
                    avl_node *tp2;
                    p = n;
                    tp = p->left;
                    tp2 =p->left->right;

                    p -> left = tp2->right;
                    tp ->right = tp2->left;
                    tp2 ->right = p;
                    tp2->left = tp; 
                    
                    return tp2; 
                }

                avl_node* insert(avl_node *r,pair<const Key, T> data){
                    
                    if(r==NULL){


                        avl_node *n;
                        n = _rebind_alloc.allocate(1);
                        
                        n->data = _alloc.allocate(1);
                        _alloc.construct(n->data, data);
                        // n->data = data;
                        r = n;
                        r->left = r->right = NULL;
                        r->height = 1; 
                        return r;             
                    }
                    else{
                        if(_cmp(data.first,r->data->first))
                        r->left = insert(r->left,data);
                        else
                        r->right = insert(r->right,data);
                    }

                    r->height = calheight(r);

                    if(bf(r)==2 && bf(r->left)==1){
                        r = llrotation(r);
                    }
                    else if(bf(r)==-2 && bf(r->right)==-1){
                        r = rrrotation(r);
                    }
                    else if(bf(r)==-2 && bf(r->right)==1){
                        r = rlrotation(r);
                    }
                    else if(bf(r)==2 && bf(r->left)==-1){
                        r = lrrotation(r);
                    }        

                    return r;

                    }

                void levelorder_newline(){
                    if (this->root == NULL){
                        std::cout<<"\n"<<"Empty tree"<<"\n";
                        return;            
                    }
                    levelorder_newline(this->root);
                }

                void levelorder_newline(avl_node *v){
                    std::queue <avl_node *> q;
                    avl_node *cur;
                    q.push(v);
                    q.push(NULL);      

                    while(!q.empty()){
                        cur = q.front();
                        q.pop();
                        if(cur == NULL && q.size()!=0){
                            std::cout<<"\n";
                            
                            q.push(NULL);
                            continue;
                        }
                        if(cur!=NULL){
                            std::cout<<" "<<cur->data;

                            if (cur->left!=NULL){
                            q.push(cur->left);
                            }
                            if (cur->right!=NULL){
                                q.push(cur->right);
                            }
                        }
                        
                        
                    }
                }
            
                avl_node * deleteNode(avl_node *p,pair<const Key, T> data){

                    if(p->left == NULL && p->right == NULL){
                            if(p==this->root)
                                this->root = NULL;
                        delete p;
                        return NULL;
                    }

                    avl_node *t;
                    avl_node *q;
                    if(_cmp(p->data->first, data.first)) {
                        p->right = deleteNode(p->right,data);
                    }
                    else if(!_cmp(p->data->first, data.first)) {
                        p->left = deleteNode(p->left,data);
                    }
                    else{
                        if(p->left != NULL){
                            q = inpre(p->left);
                            p->data = q->data;
                            p->left=deleteNode(p->left,*q->data);
                        }
                        else{
                            q = insuc(p->right);
                            p->data = q->data;
                            p->right = deleteNode(p->right,*q->data);
                        }
                    }

                    if(bf(p)==2 && bf(p->left)==1){ p = llrotation(p); }                  
                    else if(bf(p)==2 && bf(p->left)==-1){ p = lrrotation(p); }
                    else if(bf(p)==2 && bf(p->left)==0){ p = llrotation(p); }
                    else if(bf(p)==-2 && bf(p->right)==-1){ p = rrrotation(p); }
                    else if(bf(p)==-2 && bf(p->right)==1){ p = rlrotation(p); }
                    else if(bf(p)==-2 && bf(p->right)==0){ p = llrotation(p); }

                    
                    return p;
                }

                avl_node* inpre(avl_node* p){
                    while(p->right!=NULL)
                        p = p->right;
                    return p;    
                }

                avl_node* insuc(avl_node* p){
                    while(p->left!=NULL)
                        p = p->left;

                    return p;    
                }
            // avl_node *newNode(pair<const Key, T> _data) {
            
            //     avl_node *t = _rebind_alloc.allocate(1);
            //     t->data = _alloc.allocate(1);
            //     _alloc.construct(t->data, _data);
            //     t->height = 0;
            //     t->left = NULL;
            //     t->right = NULL;
            //     t->parent = NULL;
            //     return t;
            // }
            // int getBalanceFactor(avl_node *N) {
            
            //     if (N == NULL)
            //         return 0;
            //     return height(N->left) - height(N->right);
            // }
            // avl_node* insert(pair<const Key, T> _data, avl_node* node) {
            
            //     if (node == NULL)
            //         return (newNode(_data));
            //     if (_cmp(_data.first, node->data->first))
            //         node->left = insert(_data, node->left);
            //     else if (!_cmp(_data.first, node->data->first))
            //         node->right = insert(_data, node->right);
            //     else
            //         return node;

            //     // Update the balance factor of each node and
            //     // balance the tree
            //     node->height = 1 + max(height(node->left),
            //     height(node->right));
            //     // int balanceFactor = getBalanceFactor(node);
            //     // if (balanceFactor > 1) {
            //     //     if (_cmp(_data.first, node->left->data->first)) {

            //     //         return rightRotate(node);
            //     //     }
            //     //     else if (!_cmp(_data.first, node->left->data->first)) {

            //     //         node->left = leftRotate(node->left);
            //     //         return rightRotate(node);
            //     //     }
            //     // }
            //     int balance = getBalance(node);
            //     if (balance > 1 && _data.first < node->left->data->first)
            //         return rightRotate(node);
            
            //     // Right Right Case
            //     if (balance < -1 && _data.first > node->right->data->first)
            //         return leftRotate(node);
            
            //     // Left Right Case
            //     if (balance > 1 && _data.first > node->left->data->first)
            //     {
            //         node->left = leftRotate(node->left);
            //         return rightRotate(node);
            //     }
            
            //     // Right Left Case
            //     if (balance < -1 && _data.first < node->right->data->first)
            //     {
            //         node->right = rightRotate(node->right);
            //         return leftRotate(node);
            //     }
            
            //     /* return the (unchanged) node pointer */
            //     return node;
            //     // avl_node *y = NULL;
            //     // avl_node *x = t;

            //     // while (x != NULL)
            //     // {
            //     //     y = x;
            //     //     if (_cmp(t->data->first, x->data->first))
            //     //         x = x->left;
            //     //     else
            //     //         x = x->right;
            //     // }
            //     // if (t)
            //     //     t->parent = y;
            //     // if (y == NULL)
            //     //     t = newNode(_data);
            //     // else if (_cmp(t->data->first, y->data->first))
            //     //     y->left = newNode(_data);
            //     // else
            //     //     y->right = newNode(_data);
            //     // return t;
            //     // if (t == NULL)
            //     // {
            //     //     t = _rebind_alloc.allocate(1);
            //     //     t->data = _alloc.allocate(1);
            //     //     _alloc.construct(t->data, _data);
            //     //     t->height = 0;
            //     //     t->left = NULL;
            //     //     t->right = NULL;
            //     //     t->parent = NULL;
            //     // }
            //     // else if (_cmp(_data.first, t->data->first))
            //     // {
            //     //     t->left = insert(_data, t->left);
            //     //     t->left->parent = t;
            //     //     if(height(t->left) - height(t->right) == 2)
            //     //     {
            //     //         if(_data.first < t->left->data->first)
            //     //             t = singleRightRotate(t);
            //     //         else
            //     //             t = doubleRightRotate(t);
            //     //     }
            //     // }
            //     // else if (!_cmp(_data.first, t->data->first))
            //     // {
            //     //     t->right = insert(_data, t->right);
            //     //     t->right->parent = t;
            //     //     if(height(t->right) - height(t->left) == 2)
            //     //     {
            //     //         if(!_cmp(_data.first, t->right->data->first))
            //     //             t = singleLeftRotate(t);
            //     //         else
            //     //             t = doubleLeftRotate(t);
            //     //     }
            //     // }
            //     // t->height = max(height(t->left), height(t->right))+1;
            //     // return t;
            // }
            // // Rotate right
            // avl_node *rightRotate(avl_node *y) {
            
            //     if (y) {

            //         avl_node *x = y->left;
            //         avl_node *T2 = x->right;
            //         x->right = y;
            //         y->left = T2;
            //         y->height = max(height(y->left), height(y->right)) + 1;
            //         x->height = max(height(x->left), height(x->right)) + 1;
            //         return x;
            //     }
            //     return y;
            // }

            // // Rotate left
            // avl_node *leftRotate(avl_node *x) {

            //     if (x) {
            //         avl_node *y = x->right;
            //         avl_node *T2 = y->left;
                
            //         y->left = x;
            //         x->right = T2;
            //         x->height = max(height(x->left), height(x->right)) + 1;
            //         y->height = max(height(y->left), height(y->right)) + 1;
            //         return y;
            //     }
            //     return x;
            // }


            avl_node *treeMaximum(avl_node *x) const {
            
                if (x == NULL)
                    return x;
                while (x->right != NULL)
                    x = x->right;
                return x;
            }
            avl_node *treeMinimum(avl_node *x) const {
            
                if (x == NULL)
                    return x;
                while (x->left != NULL)
                    x = x->left;
                return x;
            }
            avl_node *treeSuccessor(avl_node *x) {
            
                if (x->right != NULL)
                    return treeMinimum(x->right);
                avl_node *y = x->parent;
                if (!y)
                    return NULL;
                while (y != NULL && (x == y->right)) {
                
                    x = y;
                    y = y->parent;
                }
                return y;
            }
            avl_node *treePredecessor(avl_node *x) {

            
                if (x->left != NULL)
                    return treeMaximum(x->left);
                avl_node *y = x->parent;
                while (y != NULL && (x = y->left)) {
                
                    x = y;
                    y = y->parent;
                }
                return y;
            }

            // avl_node* doubleLeftRotate(avl_node* &t)
            // {
            //     t->right = singleRightRotate(t->right);
            //     return singleLeftRotate(t);
            // }

            // avl_node* doubleRightRotate(avl_node* &t)
            // {
            //     t->left = singleLeftRotate(t->left);
            //     return singleRightRotate(t);
            // }

            // avl_node* findMin(avl_node* t)
            // {
            //     if (t == NULL)
            //         return NULL;
            //     else if (t->left == NULL)
            //         return t;
            //     else
            //         return findMin(t->left);
            // }

            // avl_node* findMax(avl_node* t)
            // {
            //     if (t == NULL)
            //         return NULL;
            //     else if (t->right == NULL)
            //         return t;
            //     else
            //         return findMax(t->right);
            // }

            // avl_node* remove(pair<Key, T> _data, avl_node* t)
            // {
            //     avl_node* temp;

            //     // Element not found
            //     if (t == NULL)
            //         return NULL;

            //     // Searching for element
            //     else if (_cmp(_data.first, t->data->first))
            //         t->left = remove(_data, t->left);
            //     else if (!_cmp(_data.first, t->data->first))
            //         t->right = remove(_data, t->right);

            //     // Element found
            //     // With 2 children
            //     else if (t->left && t->right)
            //     {
            //         temp = findMin(t->right);
            //         t->data = temp->data;
            //         t->right = remove(*t->data, t->right);
            //     }
            //     else
            //     {
            //         temp = t;
            //         if (t->left == NULL)
            //             t = t->right;
            //         else if (t->right == NULL)
            //             t = t->left;
            //         // delete temp;
            //         t->data = NULL;
            //         _alloc.destroy(t->data);
            //         _rebind_alloc.destroy(t);
            //         t = NULL;

            //     }
            //     if (t == NULL)
            //         return t;

            //     t->height = max(height(t->left), height(t->right))+1;

            //     // If avl_node is unbalanced
            //     // If left avl_node is deleted, right case
            //     if (height(t->left) - height(t->right) == 2)
            //     {
            //         // right right case
            //         if (height(t->left->left) - height(t->left->right) == 1)
            //             return singleLeftRotate(t);
            //         // right left case
            //         else
            //             return doubleLeftRotate(t);
            //     }
            //     // If right avl_node is deleted, left case
            //     else if (height(t->right) - height(t->left) == 2)
            //     {
            //         // left left case
            //         if (height(t->right->right) - height(t->right->left) == 1)
            //             return singleRightRotate(t);
            //         // left right case
            //         else
            //             return doubleRightRotate(t);
            //     }
            //     return t;
            // }

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
                std::cout << t->data->first << "|";
                std::cout << " " << t->data->second << " " << "parent : " << t->parent << std::endl;
                inorder(t->right);
            }
            avl()
            {
                root = NULL;
            }

            void insert(pair< Key, T> x)
            {
                root = insert(root, x);
            }

            void remove(pair< Key, T> x)
            {
                root = remove(x, root);
            }

            void display()
            {
                inorder(root);
                std::cout << std::endl;
            }
    };
}
