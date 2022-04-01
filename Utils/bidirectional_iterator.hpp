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
            
            avl<>     tree;
            typedef pair<const Key, T>              pair;
    
            operator mapiterator<const Key, T, Compare, Alloc> () const { return mapiterator<const Key, T, Compare, Alloc>(_tree, _current); }
            avl_node *_root;
            avl_tree _tree;
            node *_current;
            pair *_data;

            mapiterator( void ) {

                _root = NULL;
                _current = _root;

            }
            mapiterator( const mapiterator& obj ) {

                _root = obj._root;
                _current = _root;
                _tree = obj._tree;
                _data = NULL;
                if (_root != NULL)
                    _data = _root->_data;

            }
    
            mapiterator(avl_tree tree, node * root) {

                _root = root;
                _data = NULL;
                _current = _root;
                _tree = tree;
                if (_root != NULL)
                    _data = _root->_data;

            }
 
            mapiterator &operator=(const mapiterator& obj ) {

                _root = obj._root;
                _tree = obj._tree;
                _current = obj._current;
                return *this;
            }

            pair& operator*() const {return *_data;}
            pair* operator->() const {return _data;}
            
            mapiterator& operator++() {
                
                _tree.next();
                return *this;
            }
            
            mapiterator& operator--() {
                _tree.prevoius();
                return *this;
            }
            mapiterator operator++(int)  {mapiterator tmp(_tree, _root); _root = _tree.next(_root, 1); return tmp;}
            mapiterator operator--(int)  {mapiterator tmp(_tree, _root); _root = _tree.previous(_root, 1); return tmp;}
            // mapiterator operator+(const mapiterator& rhs) {return mapiterator(_root+rhs._root);}
            bool operator==(const mapiterator& rhs) const {return _data == rhs._data;}
            bool operator!=(const mapiterator& rhs) const {return _data != rhs._data;}

    };
}