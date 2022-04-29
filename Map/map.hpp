#pragma once

# include <iostream>
# include "../Utils/pair.hpp"
# include "../Utils/iterator.hpp"
# include "../Utils/reverse_iterator.hpp"
# include "../Utils/tree.hpp"
# include "../Utils/bidirectional_iterator.hpp"
# include <vector>

namespace ft {


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
            typedef Compare value_compare;
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
            explicit Map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            
                _size = 0;
                root = NULL;
                _cmp = comp;
                _allocator = alloc;
            }

            template <class InputIterator>
            Map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            // typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator(_tree.root)) {
            
                _size = 0;
                root = NULL;
                _cmp = comp;
                _allocator = alloc;
                for (iterator it = first; it != last; it++) {

                    root = tree.Insert(root, NULL, *it);
                    _size += 1;
                }
            }

            Map (const Map& x) {
            
                *this = x;
            }

            ~Map() { clear(); }

            Map& operator= (const Map& x) {
            
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
            

            pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
            
                
            }
            pair<iterator, iterator>             equal_range (const key_type& k) {
            
                
            }

            size_type count (const key_type& k) const {
            
                iterator it = find(k);
            
                if (it == end())
                    return 0;
                return 1;
            }

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

                if (it != end()) { return pair<iterator, bool>(it, false); }

                root = tree.Insert(root, NULL, val);
                _size++;
                return pair<iterator, bool>(begin(), true);
            }

            iterator insert (iterator position, const value_type& val) {

                iterator it = find(val.first); 

                if (it != end()) { return position; }

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

            iterator lower_bound (const key_type& k) {

                for ( iterator it = begin() ; it != end() ; ++it ) {
                
                    if (!_cmp(it->first, k))
                        return it;
                }
                return end();
            }

            const_iterator lower_bound (const key_type& k) const {

                for ( iterator it = begin() ; it != end() ; ++it ) {
                
                    if (!_cmp(it->first, k))
                        return it;
                }
                return end();
            }
            iterator upper_bound (const key_type& k) {
            
                for ( iterator it = begin() ; it != end() ; ++it ) {
                
                    if (_cmp(k, it->first))
                        return it;
                }
                return end();
            }

            const_iterator upper_bound (const key_type& k) const {
            
                for ( iterator it = begin() ; it != end() ; ++it ) {
                
                    if (_cmp(k, it->first))
                        return it;
                }
                return end();
            }
            void swap (Map& x) {
            
                std::swap(root, x.root);
            }
        };


        template <class Key, class T, class Compare, class Alloc>
        bool operator== ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
        
            return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator!= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
        
            return !(lhs == rhs);
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator<  ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
        
            return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator<= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
        
            return !( rhs < lhs );
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator>  ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
        
            return rhs < lhs;
        }

        template <class Key, class T, class Compare, class Alloc>
        bool operator>= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs ) {
        
            return !(lhs < rhs);
        }

        template <class Key, class T, class Compare, class Alloc>
        void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y) {
        
            std::swap(x.root, y.root);
            std::swap(x._size, y._size);
        }
}
