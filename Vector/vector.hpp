#pragma once

# include <iostream>
# include "../Utils/iterator.hpp"
# include "../Utils/reverse_iterator.hpp"


namespace ft {

    template < class T, class Alloc = std::allocator<T> >
    class vector {
    
        public:

            typedef Alloc allocator_type;
            typedef T value_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const pointer const_pointer;
            typedef myiterator<T> iterator;
            typedef const iterator const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef const ft::reverse_iterator<iterator> const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef size_t size_type;            
        
        private:

            pointer         _container;
            allocator_type  _allocator;
            size_type       _size;
            size_type       _capacity;

        public:

            explicit vector (const allocator_type& alloc = allocator_type()) {
            
                _allocator = alloc;
                _container = _allocator.allocate(2);
                _size = 0;
                _capacity = 2;
            }

            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {

                _allocator = alloc;
                _container = _allocator.allocate(n * 2);
                _size = 0;
                _capacity = n * 2;
                for (size_type i = 0; i < n; i++) {
                 
                    _allocator.construct(_container + i, val);
                    _size++;
                }
            }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) {
            
                _allocator = alloc;
                difference_type size = std::distance(first, last);

                _container = _allocator.allocate(size * 2);
                _size = 0;
                _capacity = size * 2;
                for (iterator it = first; it != last; it++) {
                
                    _allocator.construct(_container + _size, *it);
                    _size++;
                }
            }

            vector (const vector& x) {
            
                _size = x.size();
                _capacity = x.capacity() * 2;
                _allocator = x.get_allocator();
                _container = _allocator.allocate(_capacity);
                for (size_type i = 0; i < _size; i++) {
                
                    _allocator.construct(_container + i, x[i]);
                }

            }
            
            ~vector() {
            
            }
            
            vector& operator= (const vector& x) {
            
                if (_size != 0) {

                    for (size_type i = 0; i < _size; i++) {
                    
                        _allocator.destroy(_container + i);
                    }

                    _size = 0;
                    _allocator.deallocate(_container, _capacity);
                    _capacity = 0;
                }
                if (_size == 0) {
                
                    _size = x.size();
                    _capacity = x.capacity() * 2;
                    _container = _allocator.allocate(_capacity);
                    for (size_type i = 0; i < _size; i++) {
                    
                        _allocator.construct(_container + i, x[i]);
                    }
                }
                return *this;

            }

            iterator begin( void ) {

                return iterator(&_container[0]);
            }

            const_iterator begin( void ) const {
            
                return (iterator(&_container[0]));
            }

            iterator end() {

                return (iterator(&_container[_size]));
            }

            const_iterator end() const {

                return (iterator(&_container[_size]));
            }

            reverse_iterator rbegin() {

                return (reverse_iterator(iterator(&_container[_size - 1])));
            }

            const_reverse_iterator rbegin() const {

                return (reverse_iterator(iterator(&_container[_size - 1])));
            }

            reverse_iterator rend() {

                return (reverse_iterator(iterator(&_container[ - 1])));
            }

            const_reverse_iterator rend() const {

                return (reverse_iterator(iterator(&_container[-1])));
            }

            size_type size() const {
            
                return _size;
            }

            size_type max_size() const {
            
                return _allocator.max_size() / sizeof(value_type);
            }

            void resize (size_type n, value_type val = value_type()) {
            
            
                if (n < _size) {
                
                    while (_size > n)
                        pop_back();

                }
                else if (n > _size) {
                
                    while (n > _size)
                        push_back(val);
                }
                
            }
            size_type capacity() const { return _capacity; }
            bool empty() const { return _size == 0; }
            void reserve (size_type n) {
            
                if (n > _capacity) {
                
                    pointer new_data = _allocator.allocate(n);
                    for (int i = 0; i < _size; i++) {
                    
                        _allocator.construct(new_data + i, _container[i]);
                    }
                    _capacity = n;
                    std::swap(_container, new_data);
                    for (int i = 0; i < _size; i++) {
                    
                        _allocator.destroy(new_data + i);
                    }
                    _allocator.deallocate(new_data, _size);
                }
            }
    
    
            reference operator[] (size_type n) {

                if (n >= 0 && n < _size)
                    return _container[n];
                else 
                    throw std::out_of_range("");               
            }

            const_reference operator[] (size_type n) const {

                if (n >= 0 && n < _size)
                    return _container[n];
                else 
                    throw std::out_of_range("");  
            }
            reference at (size_type n) {

                return _container[n];
            }

            const_reference at (size_type n) const {

                return *this[n];
            }

            reference front() {

                return _container[0];
            }

            const_reference front() const {

                return _container[0];
            }
            reference back() {

                return _container[_size - 1];
            }


            const_reference back() const {

                return _container[_size - 1];
            }


            template <class InputIterator>
            void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) {
                
                difference_type size = std::distance(first, last);
            
                clear();
                reserve(size);
                for (int i = 0; i< size; i++) {
                
                    _allocator.construct(_container + i, *(first++));
                    _size++;
                }
            }

            void clear() {
            
                for (size_type i = 0; i < _size; i++) {
                
                    _allocator.destroy(_container + i);
                }
                _allocator.deallocate(_container, _capacity);
                _size = 0;
                _capacity = 0;
        
            }

            void assign (size_type n, const value_type& val) {

                clear();
                reserve(n);
                for (int i = 0; i< n; i++) {
                
                    _allocator.construct(_container + i, val);
                    _size++;
                }
            }

            void pop_back() {
            
                if (_size >= 1) {
                    _allocator.destroy(_container + _size);
                    _size--;
                }
            }

            void push_back (const value_type& val) {
            
                if (_size + 1 > _capacity) {
                    reserve(_capacity * 2);
                }
                _container[_size] = val;
                _size++;
            }
            allocator_type get_allocator() const {
            
                return _allocator;
            }

            iterator insert (iterator position, const value_type& val) {

                vector<T> a;
                for (iterator it = begin(); it < end() ; ++it) {
                
                    if (it == position) {
                        break ;
                    }
                    a.push_back(*it);
                }
                a.push_back(val);
                for (iterator it = position ; it < end(); ++it) {
                
                    a.push_back(*it);
                }
                *this = a;
                return begin();
            };

            void insert (iterator position, size_type n, const value_type& val) {

                vector<T> a;
            
                for (iterator it = begin(); it < end(); ++it) {
                
                    if (it == position) {
                        break ;
                    }
                    a.push_back(*it);
                }
                while (n-- > 0)
                {
                    a.push_back(val);
                }
                for (iterator it = position ; it < end(); ++it) {
                
                    a.push_back(*it);
                }
                swap(a);
                a.clear();
            };

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last,  typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) {

                vector<T> a;
            
                for (iterator it = begin(); it < end(); ++it) {
                
                    if (it == position) {
                        break ;
                    }
                    a.push_back(*it);
                }
                for (iterator it = first; it < last; ++it)
                {
                    a.push_back(*it);
                }
                for (iterator it = position ; it < end(); ++it) {
                
                    a.push_back(*it);
                }
                swap(a);
                a.clear();
            }

            void swap (vector<T>& x) {


                std::swap(_container, x._container);
                std::swap(_capacity, x._capacity);
                std::swap(_size, x._size);
            }

              iterator erase (iterator position) {

                difference_type pos =  std::distance(begin(), position);

                _allocator.destroy(_container + pos);
                while (pos < _size) {
                
                    _container[pos] = _container[pos + 1];
                    pos++;
                }
                _size--;
                return begin();
            }

            iterator erase (iterator first, iterator last) {

                difference_type pos = std::distance(first, last);

                while (pos > 0)
                {
                    first = erase(first);
                    pos--;
                }
                return begin();
            }
    };

    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));

    };

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {


        return !(lhs == rhs);
    };

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    };

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {


        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));

    };

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {


        return !(lhs <= rhs);

    };

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {


        return !(lhs < rhs);
    };


    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {

        std::swap(x._capacity, y._capacity);
        std::swap(x._size, y._size);
        std::swap(x._c, y._c);
    };
};
