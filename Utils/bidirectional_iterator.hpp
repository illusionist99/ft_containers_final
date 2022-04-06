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
            typedef avl<const Key, T, Compare, Alloc> tree;
            node *_current;
            tree root;
            pair *_safe;
            Alloc _alloc;
            typedef typename Alloc::template rebind<node>::other rebind_allocator;
            rebind_allocator _alloc_rebind;
            mapiterator( ) { _current = NULL;}
            mapiterator( node * current ) : _current(current) {

                root.root = current;
                if (_current == NULL) {
                    
                    // pair *_safe;
                    // _current = _alloc_rebind.allocate(1);
                    // _current->data = _alloc.allocate(1);
                    // _alloc.construct(_current->data, pair());
                    // _safe = _alloc.allocate(1);
                    // node tmp;
                    // _current = &tmp;
                } 
            }
            ~mapiterator() {
            
        
            }
            mapiterator( const mapiterator& obj ) {

                _current = obj._current;
            }
    
            mapiterator &operator=(const mapiterator& obj ) {

                _current = obj._current;
                return *this;
            }

            pair& operator*() const { if (_current == NULL) {return *_safe;} return *_current->data;}
            pair* operator->() const { if (_current) {return _current->data;} return NULL;}
            
            mapiterator& operator--() {
            
                _current = root.treePredecessor(_current);
                return *this;
            }
            mapiterator operator++(int)  {

                _current = root.treeSuccessor(_current);
                // _save = _current;
                
                return *this;
            }
            mapiterator operator--(int)  {mapiterator tmp(_current);  node *tmpo = _current->parent; _current = tmpo->left; return tmp;}
            // mapiterator operator+(const mapiterator& rhs) {return mapiterator(_root+rhs._root);}
            bool operator==(const mapiterator& rhs) const {if (_current && rhs._current) {return _current->data == rhs._current->data;} return (_current == rhs._current);}
            bool operator!=(const mapiterator& rhs) const {if (_current && rhs._current) {return _current->data != rhs._current->data;} return (_current != rhs._current);}

    };
}