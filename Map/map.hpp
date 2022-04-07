#pragma once

# include <iostream>
# include "../Utils/pair.hpp"
# include "../Utils/iterator.hpp"
# include "../Utils/reverse_iterator.hpp"
# include "../Utils/scratch_avl.hpp"
# include "../Utils/bidirectional_iterator.hpp"
// # include "../Utils/avl.hpp"

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
            typedef Compare key_compare;
            // typedef typename Compare value_compare;
            typedef Alloc allocator_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef mapiterator< Key, T, Compare, Alloc> iterator;
            typedef mapiterator< Key, T, Compare, Alloc> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename iterator_traits<iterator>::difference_type difference_type;
            typedef size_t size_type;
            // typedef node<key_type, mapped_type, key_compare ,allocator_type> node;

            allocator_type  _allocator;
            key_compare     _keyc;
            avl<const Key, T, Compare, Alloc> _tree;
            size_type       _size;

            explicit Map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            
                _allocator = alloc;
                _keyc = comp;
                _size = 0;
            }

            template <class InputIterator>
            Map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            // typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator(_tree.root)) {
            
                _keyc = comp;
                _allocator = alloc;
                // _rp = NULL;
                for (iterator it = first; it != last; it++) {

                    _tree.root = _tree.insert(_tree.root, *it);
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
                for (iterator it = x.begin(); it != x.end(); it++) {

                    _tree.insert(*it);
                    _size++;
                }
                return *this;
            }

            iterator begin() {

                return iterator(_tree.treeMinimum(_tree.root));
            }

            const_iterator begin() const {
        
                return iterator(_tree.treeMinimum(_tree.root));
            }

            iterator end() {

                return iterator(NULL);
            }
            const_iterator end() const {

                return iterator(NULL);
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
            size_type max_size() const  {return _allocator.max_size(); }
            
            iterator find (const key_type& k) {

                for (iterator it = begin(); it != end(); it++) {
                    
                    if ((*it).first == k)
                        return it;
                }
                return end();
            }
            const_iterator find (const key_type& k) const {
                if (_size == 0)
                    return end();
                for (iterator it = begin(); it != end(); it++) {
                    
                    if (*it->first == k)
                        return it;
                }
                return end();
            }
            mapped_type& operator[] (const key_type& k) {
            
                iterator it = find(k);

                if (it == end()) {
                    _tree.root = _tree.insert(_tree.root, make_pair< key_type, mapped_type>(k, mapped_type()));
                    return find(k)->second;
                }
                return (*it).second;
            }

            void clear() {
            
                _size = 0;
            }

            pair<iterator,bool> insert (const value_type& val) {

                iterator it = find(val.first); 

                std::cout << std::addressof(it) << " | " << std::addressof(*end()) << std::endl;
                std::cout << (it != end()) << std::endl;
                if (it != end()) { return pair<iterator, bool>(it, false); }

                _tree.insert(_tree.root, val);
                // _root.insert(val);
                _size++;
                return pair<const_iterator, bool>(begin(), true);
            }

            // iterator insert (iterator position, const value_type& val) {


            // }

            // template <class InputIterator>
            // void insert (InputIterator first, InputIterator last) {


            // }


    };

}
