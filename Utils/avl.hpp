#pragma once

# include <iostream>
# include <cstdio>
# include <sstream>
# include <algorithm>
# include "pair.hpp"
# define pow2(n) (1 << (n))
using namespace std;

template < class Key,                           // map::key_type
class T,                                       // map::mapped_type
class Compare = std::less<Key>,               // map::key_compare
class Alloc = std::allocator<T> >
struct avl {

    int _height;
    ft::pair<const Key, T> *_data;
    int d;
    struct avl *l;
    struct avl *r;
};

template < class Key,                           // map::key_type
class T,                                       // map::mapped_type
class Compare = std::less<Key>,               // map::key_compare
class Alloc = std::allocator<T> >
class avl_tree {

        typedef avl<Key, T, Compare, Alloc> avl;
        avl *r;
        
    public:

        typename Alloc::template rebind<ft::pair<const Key, T> >::other rebind_allocator;
    // int height(avl *);
    // int difference(avl *);
    // avl *rr_rotat(avl *);
    // avl *ll_rotat(avl *);
    // avl *lr_rotat(avl*);
    // avl *rl_rotat(avl *);
    // avl * balance(avl *);
    // avl * insert(avl*, int);
    // void show(avl*, int);
    // void inorder(avl *);
    // void preorder(avl *);
    // void postorder(avl*);
    
    avl_tree( void ) {
    
        r = NULL;
    }

    ~avl_tree( void ) {

    }
    avl *leftmostNode(avl *rr) {
    
        // if (r == NULL)
        //     return NULL;
        avl *tmp = rr;
    
        while (tmp && tmp->l)
            tmp = tmp->l;
        return tmp;
    }
    
    avl *rightmostNode(avl *rr) {
    
        avl *tmp = rr;
    
        while (tmp && tmp->r)
            tmp = tmp->r;
        
        return tmp;
    }
    avl *next(avl *current, int n) {

        if (current == NULL)
            return current;
        return current->r;
    }
    avl *previous(avl * current, int n) {
        
        if (current == NULL)
            return current;
        return current->l;
    }
    int height(avl *t) {
    
        int h = 0;
        if (t != NULL) {
            int l_height = height(t->l);
            int r_height = height(t->r);
            int max_height = max(l_height, r_height);
            h = max_height + 1;
        }
        return h;
    }
    int difference(avl *t) {

        int l_height = height(t->l);
        int r_height = height(t->r);
        int b_factor = l_height - r_height;
        return b_factor;
    }
    avl *rr_rotat(avl *parent) {
    
        avl *t;
        t = parent->r;
        parent->r = t->l;
        t->l = parent;
        // cout<<"Right-Right Rotation";
        return t;
    }
    avl *ll_rotat(avl *parent) {

        avl *t;
        t = parent->l;
        parent->l = t->r;
        t->r = parent;
        // cout<<"Left-Left Rotation";
        return t;
    }
    avl* newNode(ft::pair<const Key, T> data)
    {
        avl *Node = std::allocator<avl>().allocate(1);
        Node->_data = rebind_allocator.allocate(1);
        Node->_data = &data;
        Node->l = NULL;
        Node->r = NULL;
        // Node->_height = 1;
        // Node->_parent = this;
        return (Node);
    }
    avl *lr_rotat(avl *parent) {

        avl *t;
        t = parent->l;
        parent->l = rr_rotat(t);
        // cout<<"Left-Right Rotation";
        return ll_rotat(parent);
    }

    avl *rl_rotat(avl *parent) {

        avl *t;
        t = parent->r;
        parent->r = ll_rotat(t);
        // cout<<"Right-Left Rotation";
        return rr_rotat(parent);
    }

    avl *balance(avl *t) {
    
        int bal_factor = difference(t);
        if (bal_factor > 1) {
            if (difference(t->l) > 0)
                t = ll_rotat(t);
            else
                t = lr_rotat(t);
        } else if (bal_factor < -1) {
            if (difference(t->r) > 0)
                t = rl_rotat(t);
            else
                t = rr_rotat(t);
        }
        return t;
    }

    avl *insert(avl *r, ft::pair<Key, T> v) {
    
        if (r == NULL) {
        
            r = newNode(v);
            // r->d = v;
            r->l = NULL;
            r->r = NULL;
            return r;
        }
        else if (v.first < r->_data->first) {
        
            r->l = insert(r->l, v);
            r = balance(r);
        }
        else if (v.first >= r->_data->first) {
        
            r->r = insert(r->r, v);
            r = balance(r);
        }
        return r;
    }
    
    void show(avl *p, int l) {
    
        int i;
        if (p != NULL) {
            show(p->r, l+ 1);
            // cout<<" ";
            if (p == r)
                // cout << "Root -> ";
            for (i = 0; i < l&& p != r; i++)
                // cout << " ";
                // cout << p->d;
                show(p->l, l + 1);
        }
    }
    void inorder(avl *t) {
    
        if (t == NULL)
            return;
            inorder(t->l);
            // cout << t->d << " ";
            inorder(t->r);
    }
    void preorder(avl *t) {
    
        if (t == NULL)
            return;
            // cout << t->d << " ";
            preorder(t->l);
            preorder(t->r);
    }
    void postorder(avl *t) {
    
        if (t == NULL)
            return;
            postorder(t ->l);
            postorder(t ->r);
            // cout << t->d << " ";
    }
};