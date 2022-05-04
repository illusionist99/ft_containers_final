#pragma once

# include "bidirectional_iterator.hpp"


namespace ft {

    template < class Iterator >
    class reverse_iterator : public iterator_traits<Iterator> {
        

        public:
            Iterator _curr;

            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
    

            reverse_iterator( ) {
            
                _curr = Iterator();
            }


            reverse_iterator( const iterator_type  &it ) {
            
                _curr = it;
            }
            template <class Iter>
            reverse_iterator( const reverse_iterator<Iter>& obj ) {
            
                _curr = --obj.base();
            }

            ~reverse_iterator() {
            
            }


            // reverse_iterator& operator+= ( difference_type rhs ) { while (rhs && (_curr != NULL)) { --_curr; } return *this; };
            // reverse_iterator& operator-= ( difference_type rhs ) {  while (rhs && (_curr != NULL)) { ++_curr; } return *this; };

            reference operator*()  { return *_curr; }
            pointer   operator->()  { return std::addressof(*_curr); }

            reference operator[]( difference_type rhs ) const { return base()[-rhs-1]; }


            reverse_iterator& operator++() { --_curr; return *this; }
            reverse_iterator& operator--() { ++_curr; return *this; }
        
            reverse_iterator  operator++( int ) { reverse_iterator tmp(_curr); _curr--; return tmp; }
            reverse_iterator  operator--( int ) { reverse_iterator tmp(_curr); _curr++; return tmp; }

            reverse_iterator operator+( difference_type rhs ) const { return reverse_iterator(_curr - (rhs - 1)); }
            reverse_iterator operator-( difference_type rhs ) const { return reverse_iterator(_curr + (rhs + 1)); }

            operator reverse_iterator<const iterator_type> () const { return reverse_iterator<const iterator_type>(_curr) ; }

            iterator_type base() const {
            
                iterator_type tmp = _curr;
                ++tmp;
                return tmp;
            }

    };

    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._curr == rhs._curr);
    }
	
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._curr != rhs._curr);
    }

    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._curr > rhs._curr);
    }

    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._curr >= rhs._curr);
    }

    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._curr < rhs._curr);
    }

    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs) {

        return (lhs._curr <= rhs._curr);
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it) {
    
        return reverse_iterator<Iterator>(rev_it._curr - n);
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    
        return  (rhs._curr - lhs._curr);
    }
}