#pragma once

# include <iostream>
# include "../Utils/pair.hpp"
# include "../Utils/iterator.hpp"
# include "../Utils/reverse_iterator.hpp"

namespace ft {



    // template <class Key, class T, class Compare, class Alloc>
    // class map<Key,T,Compare,Alloc>::value_compare
    // {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
    //     friend class map;
    //     protected:
    //     Compare comp;
    //     value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
    //     public:
    //     typedef bool result_type;
    //     typedef value_type first_argument_type;
    //     typedef value_type second_argument_type;
    //     bool operator() (const value_type& x, const value_type& y) const
    //     {
    //         return comp(x.first, y.first);
    //     }
    // };

    template < class Key,                                     // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,                     // map::key_compare
    class Alloc = std::allocator<pair<const Key,T> > >   // map::allocator_type
    class map {

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
            typedef myiterator<value_type> iterator;
            typedef myiterator<const value_type> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef iterator_traits<iterator>::difference_type difference_type;
            typedef size_t size_type;

            allocator_type  _allocator;
            key_compare     _keyc;
            
            explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {
            
                _allocator = alloc;
                _keyc = comp;
            }

            template <class InputIterator>
            map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {

            }

            map (const map& x) {

            }
    };

}
