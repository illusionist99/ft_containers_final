#pragma once

# include "iterator.hpp"

namespace ft {

    template <class Iterator>
    class reverse_iterator : public iterator_traits<Iterator> {

           

        public:

            Iterator _it;
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
            typedef typename iterator_traits<Iterator>::value_type value_type;
            typedef typename iterator_traits<Iterator>::difference_type difference_type;
            typedef typename iterator_traits<Iterator>::pointer pointer;
            typedef typename iterator_traits<Iterator>::reference reference;
    
            reverse_iterator( void ) {

            }
            explicit reverse_iterator (iterator_type it) {
            
                _it = it;
            }
            template <class Iter>
            reverse_iterator<Iter>(const reverse_iterator<Iter>& rev_it) {
            
                _it = rev_it._it;
            }
            iterator_type base() const { iterator_type p = _it; p++; return p ; }
            reference operator*() const { return *_it; }
            reverse_iterator operator+ (difference_type n) const {
            
                return reverse_iterator(_it -  n);
            }
            reverse_iterator& operator++() {
            
                --_it;
                return *this;
            }
            reverse_iterator  operator++(int) {
            
                reverse_iterator temp = *this;
                ++(*this);
                return temp;
            }
            reverse_iterator& operator+= (difference_type n) { 
            
                _it -= n;
                return *this;
            }
            reverse_iterator operator- (difference_type n) const { return reverse_iterator(_it + n);}
    
            reverse_iterator& operator--() {

                ++_it;
                return *this;
            }

            reverse_iterator  operator--(int) {

                reverse_iterator temp = *this;
                --(*this);
                return temp;
            }
            reverse_iterator& operator-= (difference_type n) {
            
                _it += n;
                return *this;
            }
            pointer operator->() const {
            
                return std::addressof(operator*());
            }
            reference operator[] (difference_type n) const { return _it[n - 1]; }
    
    };

    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._it == rhs._it);
    }
	
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._it != rhs._it);
    }

    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._it > rhs._it);
    }

    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._it >= rhs._it);
    }

    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {

        return (lhs._it < rhs._it);
    }

    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs) {

        return (lhs._it <= rhs._it);
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& rev_it) {
    
        return reverse_iterator<Iterator>(rev_it._it - n);
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    
        return  (lhs._it - rhs._it);
    }
}


