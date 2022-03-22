#pragma once

# include <iostream>
# include "../Utils/pair.hpp"
# include "../Utils/iterator.hpp"
# include "../Utils/reverse_iterator.hpp"
# include "../Utils/avl.hpp"
# include "../Utils/bidirectional_iterator.hpp"

namespace ft {



    // template <class Key, class T, class Compare, class Alloc>
    // class Map<Key,T,Compare,Alloc>::value_compare
    // {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
    //     friend class Map;
    //     protected:
    //     Compare comp;
    //     value_compare (Compare c) : comp(c) {}  // constructed with Map's comparison object
    //     public:
    //     typedef bool result_type;
    //     typedef value_type first_argument_type;
    //     typedef value_type second_argument_type;
    //     bool operator() (const value_type& x, const value_type& y) const
    //     {
    //         return comp(x.first, y.first);
    //     }
    // };

    template < class Key,                                     // Map::key_type
    class T,                                                 // Map::mapped_type
    class Compare = std::less<Key>,                         // Map::key_compare
    class Alloc = std::allocator<pair<const Key,T> > >     // Map::allocator_type
    class Map {

        public:

            typedef Key key_type;
            typedef T mapped_type;
            typedef pair<const key_type, mapped_type> value_type;
            typedef std::less<key_type> key_compare;
            // typedef typename Compare value_compare;
            typedef Alloc allocator_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef mapiterator<Key, T, Compare, Alloc> iterator;
            typedef mapiterator<Key, T, Compare, Alloc> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename iterator_traits<iterator>::difference_type difference_type;
            typedef size_t size_type;
            typedef  Node<key_type, mapped_type, key_compare ,allocator_type> node;

            allocator_type  _allocator;
            key_compare     _keyc;
            node            *_root;
            size_type       _size;

            explicit Map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            
                _allocator = alloc;
                _keyc = comp;
                _root = NULL;
                _size = 0;
            }

            template <class InputIterator>
            Map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            
                _keyc = comp;
                _allocator = alloc;
                for (iterator it = first; it < last; it++) {

                    _root = _root->insert(_root, *it);
                    _size++;
                }
            }

            Map (const Map& x) {
            
                *this = x;
            }
            ~Map() { clear(); }
            Map& operator= (const Map& x) {
            
                if (_size > 0)
                    clear();
                for (iterator it = x.begin(); it < x.end(); it++) {

                    _root = _root->insert(_root, *it);
                    _size++;
                }
            }

            iterator begin() {

                return iterator(_root, &_root->_data);
            }

            const_iterator begin() const {

                return iterator(_root, _root->_data);
            }


            size_type find_size(node *gua) {
            
                if (gua)
                    return (find_size(gua->_left) + 1 + find_size(gua->_right));
                return 0;
            }

            node    *last( node *gua ) {
            
                
                size_type size = find_size(gua);
                
                if (gua == NULL)
                    return NULL;
                for (size_type i = 0; i < size ; i++) {
                
                    if (gua->_left) { return last(gua->_left); }
                    else if (gua->_right) { return last(gua->_right); }
                    else { break ; }
                }
                return gua->_parrent;
            }
            
            iterator end() {

                return iterator(_root, last(_root)->_data);
            }
            const_iterator end() const {

                return iterator(_root, last(_root)->_data);
            }

            reverse_iterator rbegin() {

                return (reverse_iterator(end()));
            }
            const_reverse_iterator rbegin() const {

                return (reverse_iterator(end()));
            }

            reverse_iterator rend() {
            
                return (reverse_iterator(begin()));
            }
            const_reverse_iterator rend() const {
            
                return (reverse_iterator(begin()));
            }
            bool empty() const { return _size == 0; }
            size_type size() const { return _size; }
            size_type max_size() const  {return node::_allocator.max_size(); }
            
            iterator find (const key_type& k) {
                
                for (iterator it = begin(); it != end(); it++) {
                    
                    if ((*it).first == k)
                        return it;
                }
                return end();
            }
            const_iterator find (const key_type& k) const {
    
                for (iterator it = begin(); it < end(); it++) {
                    
                    if (*it->first == k)
                        return it;
                }
                return end();
            }
            mapped_type& operator[] (const key_type& k) {
            
                iterator it = find(k);

                if (it == end()) {
                    _root = _root->insert(_root, pair<key_type, mapped_type>(k, mapped_type()));
                    return find(k)->second;
                }
                return (*it)->second;
            }

            void clear() {
            
                _size = 0;
            }

            pair<iterator,bool> insert (const value_type& val) {

                iterator it = find(val.first);

                if (it != end()) { return pair<iterator, bool>(it, false); }

                _root = _root->insert(_root, val);
                return pair<iterator, bool>(find(val.first), true);
            }

            // iterator insert (iterator position, const value_type& val) {


            // }

            // template <class InputIterator>
            // void insert (InputIterator first, InputIterator last) {


            // }


    };

}
