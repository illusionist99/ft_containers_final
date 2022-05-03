#pragma once

# include "bidirectional_iterator.hpp"
// # include "iterator.hpp"
// # include "tree.hpp"

namespace ft {

    template < class Iterator >
    class reverse_map : public iterator_traits<Iterator> {
        

        public:
            Iterator _curr;

            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
    

            // reverse_map(Iterator &it) {
            
            //     _curr = it;
            // }
            reverse_map( ) {
            
                // _curr = NULL;
            }

            // reverse_map(Iterator curr) {
            
            //     _curr = curr;
            // }

            reverse_map( const iterator_type  &it ) {
            
                _curr = it;
                // root
            }
            template <class Iter>
            reverse_map( const reverse_map<Iter>& obj ) {
            
                _curr = --obj.base();
            }
            ~reverse_map() {
            
            }


            reverse_map& operator+= ( difference_type rhs ) { while (rhs && (_curr != NULL)) { --_curr; } return *this; };
            reverse_map& operator-= ( difference_type rhs ) {  while (rhs && (_curr != NULL)) { ++_curr; } return *this; };

            reference operator*() const { return *_curr; }
            pointer   operator->() const { return std::addressof(*_curr); }

            reference operator[]( difference_type rhs ) const { return base()[-rhs-1]; }


            reverse_map& operator++() { --_curr; return *this; }
            reverse_map& operator--() { ++_curr; return *this; }
            reverse_map  operator++( int ) { --_curr; return *this; }
            reverse_map  operator--( int ) { ++_curr; return *this; }

            reverse_map operator+( difference_type rhs ) const { return reverse_map(_curr - (rhs - 1)); }
            reverse_map operator-( difference_type rhs ) const { return reverse_map(_curr + (rhs + 1)); }

            operator reverse_map<const iterator_type> () const { return reverse_map<const iterator_type>(_curr) ; }

            iterator_type base() const {
            
                iterator_type tmp = _curr;
                ++tmp;
                return tmp;
            }

    };

    template <class Iterator>
    bool operator== (const reverse_map<Iterator>& lhs,
    const reverse_map<Iterator>& rhs) {

        return (lhs._curr == rhs._curr);
    }
	
    template <class Iterator>
    bool operator!= (const reverse_map<Iterator>& lhs,
    const reverse_map<Iterator>& rhs) {

        return (lhs._curr != rhs._curr);
    }

    template <class Iterator>
    bool operator<  (const reverse_map<Iterator>& lhs,
    const reverse_map<Iterator>& rhs) {

        return (lhs._curr > rhs._curr);
    }

    template <class Iterator>
    bool operator<= (const reverse_map<Iterator>& lhs,
    const reverse_map<Iterator>& rhs) {

        return (lhs._curr >= rhs._curr);
    }

    template <class Iterator>
    bool operator>  (const reverse_map<Iterator>& lhs,
    const reverse_map<Iterator>& rhs) {

        return (lhs._curr < rhs._curr);
    }

    template <class Iterator>
    bool operator>= (const reverse_map<Iterator>& lhs,const reverse_map<Iterator>& rhs) {

        return (lhs._curr <= rhs._curr);
    }
    template <class Iterator>
    reverse_map<Iterator> operator+ ( typename reverse_map<Iterator>::difference_type n,
    const reverse_map<Iterator>& rev_it) {
    
        return reverse_map<Iterator>(rev_it._curr - n);
    }

    template <class Iterator>
    typename reverse_map<Iterator>::difference_type operator- (const reverse_map<Iterator>& lhs,
    const reverse_map<Iterator>& rhs) {
    
        return  (rhs._curr - lhs._curr);
    }
}