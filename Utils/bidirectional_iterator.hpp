#pragma once

# include <iostream>
# include "pair.hpp"
# include "iterator.hpp"
# include "tree.hpp"
// # include "reverse_map.hpp"

namespace ft {

    template < class Key,                           // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,               // map::key_compare
    class Alloc = std::allocator<pair< const Key,T> > >
    class mapiterator {

        public:

            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::difference_type    difference_type;
            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::value_type         value_type;
            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::pointer            pointer;
            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::reference          reference;
            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::iterator_category  iterator_category;
            
            
            typedef pair< Key, T> pair;
            typedef node< Key, T> node;
            operator mapiterator<Key, T, Compare, Alloc> () const { return mapiterator<Key, T, Compare, Alloc>(_current); }

            node *_current;
            pair *currentData;
            node *_root;
        
            mapiterator( ) { _current = NULL; currentData = NULL; _root = NULL;}
        
            mapiterator( node * root, node * current ) {
            
                if (current == NULL) { currentData = NULL; } else {currentData = current->data;}
                _current = current;
                _root = root;
            }
            ~mapiterator() {
            
        
            }
            node *treeMaximum(node *x)  {
            
                if (x == NULL)
                    return NULL;
                while (x->right != NULL)
                    x = x->right;
                return x;
            }
            node *treeMinimum(node *x)  {
            
                if (x == NULL)
                    return NULL;
                while (x->left != NULL)
                    x = x->left;
                return x;
            }

            node *treeSuccessor(node *x) {
            
                if (x == NULL)
                    return x;
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

                if (x == NULL)
                    return x;
                if (x->left != NULL)
                    return treeMaximum(x->left);
                node *y = x->parent;
                while (y != NULL && (x == y->left)) {
                
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
            pair* operator->() const { if (_current == NULL) {return currentData;} return _current->data;}
            mapiterator& operator+= ( difference_type rhs ) { _current += rhs; return *this; };
            mapiterator& operator-= ( difference_type rhs ) { _current -= rhs; return *this; };

            mapiterator& operator--() {
            
                if (_root != NULL && _current == NULL && currentData == NULL) {
                
                    _current = treeMaximum(_root);
                    currentData = _current->data;
                    return *this;
                }

                _current = treePredecessor(_current);
                if (_current != NULL)
                    currentData = _current->data;
                else
                    currentData = NULL;

                return *this;
            }
            mapiterator operator++(int)  {

                mapiterator tmp(*this);
            
                _current = treeSuccessor(_current);
                if (_current != NULL)
                    currentData = _current->data;
                else
                    currentData = NULL;
                return tmp;
            }

            mapiterator& operator++() {

                _current = treeSuccessor(_current);
                if (_current != NULL)
                    currentData = _current->data;
                else
                    currentData = NULL;
                return *this;
            }

            mapiterator operator--(int)  {

                mapiterator tmp(*this);
                if (_root != NULL && _current == NULL && currentData == NULL) {
                
                    _current = treeMaximum(_root);
                    currentData = _current->data;
                    return *this;
                }
                _current = treePredecessor(_current);
                if (_current != NULL)
                    currentData = _current->data;
                else
                    tmp.currentData = NULL;
                return tmp;
            }
            // mapiterator operator+(const mapiterator& rhs) {return mapiterator(_root+rhs._root);}
            bool operator==(const mapiterator& rhs) const {if (_current && rhs._current) {return _current->data == rhs._current->data;} return (currentData == rhs.currentData);}
            bool operator!=(const mapiterator& rhs) const {if (_current  && rhs._current) {return _current->data != rhs._current->data;} return (currentData != rhs.currentData);}

    };
}