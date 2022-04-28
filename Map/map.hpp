#pragma once

# include <iostream>
# include "../Utils/pair.hpp"
# include "../Utils/iterator.hpp"
# include "../Utils/reverse_iterator.hpp"
# include "../Utils/tree.hpp"
# include "../Utils/bidirectional_iterator.hpp"
# include <vector>

namespace ft {


    template < class Key,                                     // map::key_type
    class T,                                                 // map::mapped_type
    class Compare = std::less<Key>,                         // map::key_compare
    class Alloc = std::allocator<pair<const Key,T> > >     // map::allocator_type
    class map {

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
            size_type _size;
            Alloc _allocator;
            typedef node<key_type, mapped_type> node;

            node *root;
            avl<key_type, mapped_type> tree;
            Compare _cmp;
            explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            
                _size = 0;
                root = NULL;
                _cmp = comp;
                _allocator = alloc;
            }

            template <class InputIterator>
            map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            // typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator(_tree.root)) {
            
                // _rp = NULL;
                _size = 0;
                root = NULL;
                for (iterator it = first; it != last; it++) {

                    root = tree.Insert(root, NULL, *it);
                    _size += 1;
                }
            }

            map (const map& x) {
            
                *this = x;
            }

            ~map() { clear(); }

            map& operator= (const map& x) {
            
                _size = 0;
                root = NULL;
                for (iterator it = x.begin(); it != x.end(); it++) {

                    root = tree.Insert(root, NULL, *it);
                    _size += 1;
                }
                return *this;
            }

            iterator begin() {

                return iterator(tree.TreeMinimum(root));
            }

            const_iterator begin() const {
        
                return iterator(tree.TreeMinimum(root));
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

            allocator_type get_allocator() const { return _allocator;}
            bool empty() const { return _size == 0; }
            size_type size() const { return _size; }
            size_type max_size() const  {return _allocator.max_size(); }
            
            iterator find (const key_type& k) {

                for (iterator it = begin(); it != end(); it++) {
                    
                    if (it->first == k)
                        return it;
                }
                return end();
            }
            const_iterator find (const key_type& k) const {

                for (iterator it = begin(); it != end(); it++) {
                    
                    if (*it->first == k)
                        return it;
                }
                return end();
            }
            mapped_type& operator[] (const key_type& k) {
            
                iterator it = find(k);

                if (it == end()) {
                    root = tree.Insert(root, NULL, make_pair< key_type, mapped_type>(k, mapped_type()));
                    return find(k)->second;
                }
                return (*it).second;
            }

            void clear() {
            
                _size = 0;
            }

            pair<iterator,bool> insert (const value_type& val) {

                iterator it = find(val.first); 

                // std::cout << std::addressof(it) << " | " << std::addressof(*end()) << std::endl;
                // std::cout << (it != end()) << std::endl;
                if (it != end()) { return pair<iterator, bool>(it, false); }

                // _tree.root = _tree.insert(_tree.root, val);
                root = tree.Insert(root, NULL, val);
                _size++;
                return pair<iterator, bool>(begin(), true);
            }

            iterator insert (iterator position, const value_type& val) {

                iterator it = find(val.first); 

                if (it != end()) { return it; }

                root = tree.Insert(root, NULL, val);
                _size++;
                return begin();
            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) {

                
                for (InputIterator it = first; it != last; it++) {
                
                    root = tree.Insert(root , NULL, *it);
                }
            }


            size_type erase (const key_type& k) {
            
                // iterator it = find(k);
                root = tree.Delete(root, make_pair<Key, T>(k, T()));
                _size--;
                return _size;
            }
            void erase (iterator position) {
            
                // if (position != end())
                root = tree.Delete(root, *position);
                _size--;
            }


            void erase (iterator first, iterator last) {
            
                std::vector<Key> tmp;

                while (first != last) {

                    tmp.push_back(first->first);
                    first++;
                }
                for (int i = 0; i < tmp.size(); i++) { erase(tmp[i]); }
            }

            key_compare key_comp() const {
            
                return _cmp;
            }
    };

}
