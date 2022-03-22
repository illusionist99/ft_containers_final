#pragma once

# include <iostream>
# include "pair.hpp"
# include "avl.hpp"
# include "iterator.hpp"

namespace ft {



    template < class Key,                           // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,               // map::key_compare
    class Alloc = std::allocator<pair<const Key,T> > >
    class mapiterator {

        public:

            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::difference_type    difference_type;
            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::value_type         value_type;
            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::pointer            pointer;
            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::reference          reference;
            typedef typename iterator<std::random_access_iterator_tag, pair<Key, T> >::iterator_category  iterator_category;
            
            typedef Node<Key, T, Compare, Alloc>    node; 
            typedef pair<const Key, T>              pair;
    
            node *_root;
            node *_current;
            pair *_data;

            mapiterator( void  ) {

                _root = node();
                _current = _root;
                _data = pair();
            }
            mapiterator( const mapiterator& obj ) {

                *this = obj;
            }

            operator mapiterator<const Key, T, Compare, Alloc> () const { return mapiterator<const Key, T, Compare, Alloc>(_root, _data); }
    
            mapiterator(node * root, pair *data) {

                _root = copy(root);
                _data = &data;
                _current = root;
            }
            mapiterator &operator=(const mapiterator& obj ) {
            
                _root = copy(obj._root);
                _data = obj._data;
                _current = obj._current;
                return *this;
            }

            T& operator*() const {return *_data;}
            T* operator->() const {return _data;}
            
            mapiterator& operator++() {
                _current = _root->next(_current, 1);
                _data = _root->_data;

                return *this;
            }
            
            mapiterator& operator--() {
                _current = _root->previous(_current, 1);
                _data->_root->_data;
                return *this;
            }
            mapiterator operator++(int)  {mapiterator tmp(*this); _current = _root->next(_current, 1); return tmp;}
            mapiterator operator--(int)  {mapiterator tmp(*this); _current = _root->previous(_current, 1); return tmp;}
            // mapiterator operator+(const mapiterator& rhs) {return mapiterator(_root+rhs._root);}
            bool operator==(const mapiterator& rhs) const {return _data == rhs._data;}
            bool operator!=(const mapiterator& rhs) const {return _data != rhs._data;}

 

    };
}