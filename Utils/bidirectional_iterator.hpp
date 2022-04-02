#pragma once

# include <iostream>
# include "pair.hpp"
# include "scratch_avl.hpp"
# include "iterator.hpp"

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

            typedef typename avl<const Key, T, Compare, Alloc>::avl_node node;
            node *_current;

            mapiterator( node * current ) : _current(current) {

                if (_current == NULL) {
                    
                    node tmp;
                    _current = &tmp;
                } 
            }
            mapiterator( const mapiterator& obj ) {

                _current = obj._current;
            }
    
            mapiterator &operator=(const mapiterator& obj ) {

                _current = obj._current;
                return *this;
            }

            pair& operator*() const {return *_current->data;}
            pair* operator->() const {return _current->data;}
            
            mapiterator& operator++() {

                node *tmp = _current->parent;
                _current = tmp->right;
                return *this;
            }
            
            mapiterator& operator--() {
               node *tmp = _current->parent;
                _current = tmp->left;
                return *this;
            }
            mapiterator operator++(int)  {
            
                if (_current) {
                
                    if (_current->parent == NULL) {
                    
                        if (_current->right)
                            return mapiterator(_current->right);
                     
                        return mapiterator(_current);
                    }
                    
                }
                mapiterator tmp(_current);
                if (_current) {
                
                    if (_current->right)
                        _current = _current->right;
                    else
                        _current = _current->parent;
                }
                
                return tmp;
            }
            mapiterator operator--(int)  {mapiterator tmp(_current);  node *tmpo = _current->parent; _current = tmpo->left; return tmp;}
            // mapiterator operator+(const mapiterator& rhs) {return mapiterator(_root+rhs._root);}
            bool operator==(const mapiterator& rhs) const {return _current->data == rhs._current->data;}
            bool operator!=(const mapiterator& rhs) const {return _current->data != rhs._current->data;}

    };
}