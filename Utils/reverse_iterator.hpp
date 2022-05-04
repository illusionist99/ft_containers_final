#pragma once

# include "iterator.hpp"

namespace ft {

    template <class Iterator>
    class reverse_iterator : public iterator_traits<Iterator> {

        public:

            Iterator _iter;
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
    
        
            reverse_iterator() {
            
                _iter = Iterator();
            }

            reverse_iterator( iterator_type const &it ) {
            
                iterator_type tmp = it;
                --tmp;
                _iter = tmp;
            }
            template <class Iter>
            reverse_iterator( const reverse_iterator<Iter>& obj ) {
            
                _iter = --obj.base();
            }
            ~reverse_iterator() {
            
            }


            reverse_iterator& operator+= ( difference_type rhs ) { _iter -= rhs; return *this; };
            reverse_iterator& operator-= ( difference_type rhs ) { _iter += rhs; return *this; };

            reference operator*() const { return *_iter; }
            pointer   operator->() const { return std::addressof(*_iter); }

            reference operator[]( difference_type rhs ) const { return base()[-rhs-1]; }


            reverse_iterator& operator++() { --_iter; return *this; }
            reverse_iterator& operator--() { ++_iter; return *this; }
            reverse_iterator  operator++( int ) { reverse_iterator tmp = *this; ++(*this); return tmp; }
            reverse_iterator  operator--( int ) { reverse_iterator tmp = *this; --(*this); return tmp; }

            reverse_iterator operator+( difference_type rhs ) const { return reverse_iterator(_iter - (rhs - 1)); }
            reverse_iterator operator-( difference_type rhs ) const { return reverse_iterator(_iter + (rhs + 1)); }

            operator reverse_iterator<const iterator_type> () const { return reverse_iterator<const iterator_type>(_iter) ; }

            iterator_type base() const {
            
                iterator_type tmp = _iter;
                ++tmp;
                return tmp;
            }

    
    };

    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._iter == rhs._iter);
    }
	
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._iter != rhs._iter);
    }

    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._iter > rhs._iter);
    }

    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._iter >= rhs._iter);
    }

    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._iter < rhs._iter);
    }

    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs) {

        return (lhs._iter <= rhs._iter);
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it) {
    
        return reverse_iterator<Iterator>(rev_it._iter - n);
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    
        return  (rhs._iter - lhs._iter);
    }
}


