#pragma once

# include <iostream>
# include "pair.hpp"
// # include "scratch_avl.hpp"
# include "iterator.hpp"
# include "avlTree.hpp"

namespace ft {

    template < class Key,                           // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,               // map::key_compare
    class Alloc = std::allocator<pair<const Key,T> > >
    class mapiterator {

        public:

            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::difference_type    difference_type;
            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::value_type         value_type;
            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::pointer            pointer;
            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::reference          reference;
            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::iterator_category  iterator_category;
            
            
            typedef pair<const Key, T>              pair;
    
            operator mapiterator<const Key, T, Compare, Alloc> () const { return mapiterator<const Key, T, Compare, Alloc>(_current); }

            typedef node<const Key, T> node;
            node *_current;
            pair *currentData;
            mapiterator( ) { _current = NULL;}
        
            mapiterator( node * current ) {
            
                if (current)
                    currentData = current->data;
                _current = current;
            }
            ~mapiterator() {
            
        
            }
            node *treeMaximum(node *x) const {
            
                if (x == NULL)
                    return NULL;
                while (x->right != NULL)
                    x = x->right;
                return x;
            }
            node *treeMinimum(node *x) const {
            
                if (x == NULL)
                    return NULL;
                while (x->left != NULL)
                    x = x->left;
                return x;
            }

            node *treeSuccessor(node *x) {
            
                if (x == NULL)
                    return NULL;
                if (x->right != NULL)
                    return treeMinimum(x->right);
                node *y = x->parent;
                while (y != NULL && (x == y->right)) {
                
                    x = y;
                    y = y->parent;
                }
                return y;
            }
            node *treePredecessor(node *x) {

                if (x->left != NULL)
                    return treeMaximum(x->left);
                node *y = x->parent;
                while (y != NULL && (x = y->left)) {
                
                    x = y;
                    y = y->parent;
                }
                return y;
            }
            mapiterator( const mapiterator& obj ) {

                _current = obj._current;
                currentData = obj.currentData;
            }
    
            mapiterator &operator=(const mapiterator& obj ) {

                _current = obj._current;
                currentData = obj.currentData;
                return *this;
            }

            pair& operator*() const { if (_current == NULL) {return *currentData;} return *_current->data;}
            pair* operator->() const { return _current->data;}
            
            mapiterator& operator--() {
            
                _current = treePredecessor(_current);
                return *this;
            }
            mapiterator operator++(int)  {

                _current = treeSuccessor(_current);
                return *this;
            }
            // mapiterator operator--(int)  {mapiterator tmp(_current);  node *tmpo = _current->parent; _current = tmpo->left; return tmp;}
            // mapiterator operator+(const mapiterator& rhs) {return mapiterator(_root+rhs._root);}
            bool operator==(const mapiterator& rhs) const {if (_current && rhs._current) {return _current->data == rhs._current->data;} return (_current == rhs._current);}
            bool operator!=(const mapiterator& rhs) const {if (_current && rhs._current) {return _current->data != rhs._current->data;} return (_current != rhs._current);}

    };
}