#pragma once

# include "iterator.hpp"

namespace ft {

    template <class Iterator>
    class reverse_iterator : public Iterator {

           

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
            reverse_iterator (const reverse_iterator<Iter>& rev_it) {
            
                _it = rev_it.base();
            }
            iterator_type base( void ) const {
            
                return _it--;
            }
            reference operator*() const {
            
                return *_it;
            }
            reverse_iterator operator+ (difference_type n) const {
            
                _it -= n;
                return *this;

            }

            reverse_iterator& operator++() {
            
                _it--;
                return *this;
            }

            reverse_iterator  operator++(int) {
            
                reverse_iterator temp = *this;
                ++(*this);
                return temp;
            }

            reverse_iterator& operator+= (difference_type n) {
            
                _it -= n;
                return (*this);
            }

            reverse_iterator operator- (difference_type n) const {
            
                _it += n;
                return *this;
            }

            reverse_iterator& operator--() {
                
                _it++;
                return *this;
            }

            reverse_iterator  operator--(int) {

                reverse_iterator temp = *this;
                --(*this);
                return temp;
            }
            
            reverse_iterator& operator-= (difference_type n) {
            
                _it += n;
                return (*this);
            }

            pointer operator->() const {
            
                return &(operator*());
            }

            reference operator[] (difference_type n) const {
            
                return (_it[n]);
            }
    };

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {

    return lhs._it == rhs._it;
}

	

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs,
const reverse_iterator<Iterator>& rhs) {

    return lhs._it != rhs._it;
}

	

template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs,
const reverse_iterator<Iterator>& rhs) {

    return lhs._it > rhs._it;
}

	

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs,
const reverse_iterator<Iterator>& rhs) {

    return lhs._it >= rhs._it;
}


template <class Iterator>
bool operator>  (const reverse_iterator<Iterator>& lhs,
const reverse_iterator<Iterator>& rhs) {

    return lhs._it < rhs._it;
}

template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs,
const reverse_iterator<Iterator>& rhs) {

    return lhs._it <= rhs._it;
}

}