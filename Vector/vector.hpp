#pragma once

# include <iostream>
# include "../Utils/iterator.hpp"
# include "../Utils/reverse_iterator.hpp"


namespace ft {

    template < class T, class Alloc = std::allocator<T> >
    class Vector {
    
        public:

            typedef Alloc allocator_type;
            typedef T value_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const pointer const_pointer;
            typedef myiterator<T> iterator;
            typedef myiterator<const T> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef size_t size_type;            
        
        public:

            pointer         _c;
            allocator_type  _allocator;
            size_type       _size;
            size_type       _capacity;

        public:

            explicit Vector (const allocator_type& alloc = allocator_type()) {
            
                _allocator = alloc;
                _c = NULL;
                _size = 0;
                _capacity = 0;
            }

            explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {

                _allocator = alloc; 
                _c = _allocator.allocate(n);
                _size = 0;
                _capacity = n;
                for (size_type i = 0; i < n; i++) {
                 
                    _allocator.construct(_c + i, val);
                    _size++;
                }
            }

            template <class InputIterator>
            Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) {
            
                _allocator = alloc;
                difference_type size = std::distance(first, last);

                _c = _allocator.allocate(size);
                _size = 0;
                _capacity = size;
                for (InputIterator it = first; it != last; it++) {
                
                    _allocator.construct(_c + _size, *it);
                    _size++; 
                }
            }

            Vector (const Vector& x) {
            
                _size = x.size();
                _capacity = x.capacity();
                _allocator = x.get_allocator();
                _c = _allocator.allocate(_capacity);
                for (size_type i = 0; i < _size; i++) {
                
                    _allocator.construct(_c + i, x[i]);
                }

            }
            
            ~Vector() {
            
            }
            
            Vector& operator= (Vector const &x) {
            
                if (_size != 0) {

                    for (size_type i = 0; i < _size; i++) {
                    
                        _allocator.destroy(_c + i);
                    }

                    _size = 0;
                    _allocator.deallocate(_c, _capacity);
                    _capacity = 0;
                }
                if (_size == 0) {
                
                    _size = x.size();
                    _capacity = x.capacity();
                    _c = _allocator.allocate(_capacity);
                    for (size_type i = 0; i < _size; i++) {
                    
                        _allocator.construct(_c + i, x[i]);
                    }
                }
                return *this;

            }

            iterator begin( void ) {

                return iterator(&_c[0]);
            }

            const_iterator begin( void ) const {
            
                return (iterator(&_c[0]));
            }

            iterator end() {

                return (iterator(&_c[_size]));
            }

            const_iterator end() const {

                return (iterator(&_c[_size]));
            }

            reverse_iterator rbegin() {

                return (reverse_iterator(end()));
            }

            const_reverse_iterator rbegin() const {

                return (const_reverse_iterator (end()));
            }

            reverse_iterator rend() { 

                return (reverse_iterator(begin()));
            }

            const_reverse_iterator rend() const {

                return (const_reverse_iterator(begin()));
            }

            size_type size() const {
            
                return _size;
            }

            size_type max_size() const {
            
                return _allocator.max_size();
            }

            void resize (size_type n, value_type val = value_type()) {
             
                if (n > _capacity)
                    reserve(n); 
                if (n < _size) {
                
                    while (_size - n >= 1)
                        pop_back();

                }
                else {
                
                    while (n - _size >= 1)
                        push_back(val);
                }
            }
            size_type capacity() const { return _capacity; }
            bool empty() const { return _size == 0; }
            void reserve (size_type n) {
            
                if (n > _capacity) {

                    // std::cout << "reserved\n";

                    pointer new_data = _allocator.allocate(n);
                    
                    for (size_type i = 0; i < _size; i++) {
                    
                        _allocator.construct(new_data + i, _c[i]);
                    }
                    _capacity = n;
                    std::swap(_c, new_data); 
                    for (size_type i = 0; i < _size; i++) {
                    
                        _allocator.destroy(new_data + i);
                    }
                    _allocator.deallocate(new_data, _size);
                } 
            }
    
    
            reference operator[] (size_type n) {

                if (n >= 0 && n < _size)
                    return _c[n];
                else 
                    throw std::out_of_range("");               
            }

            const_reference operator[] (size_type n) const {

                if (n >= 0 && n < _size)
                    return _c[n];
                else 
                    throw std::out_of_range("");  
            }
            reference at (size_type n) {

                if (n >=0 && n < _size) 
                    return _c[n];
                else 
                    throw std::out_of_range(""); 
            }

            const_reference at (size_type n) const {

                if (n >= 0 && n < _size)
                    return _c[n];
                else 
                    throw std::out_of_range("");
            }

            reference front() {

                return _c[0];
            }

            const_reference front() const {

                return _c[0];
            }
            reference back() {

                if ((_size - 1) >= 0)
                    return _c[_size - 1];
                else 
                    throw std::out_of_range("");
            }


            const_reference back() const {

                if ((_size - 1) >= 0)
                    return _c[_size - 1];
                else 
                    throw std::out_of_range("");
            }


            template <class InputIterator>
            void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) {
                
                size_type size = std::distance(first, last);
            
                if (_size > 0)
                    clear();
                reserve(size);
                for (size_type i = 0; i < size; i++) {
                
                    _allocator.construct(_c + i, *(first++));
                    _size++;
                }
            }

            void clear() {
            
                for (size_type i = 0; i < _size; i++) {
                
                    _allocator.destroy(_c + i);
                }
                // _allocator.deallocate(_c, _capacity);
                _size = 0;
                // _capacity = 0;
                // _c = NULL;
            }

            void assign (size_type n, const value_type& val) {

                if (n > _capacity) {
                    clear();
                    reserve(n);
                }
                else {
                   
                    size_type tmp = _capacity;

                    clear();
                    reserve(tmp);
                }
                
                for (size_type i = 0; i < n; i++) {
                
                    _allocator.construct(_c + i, val);
                    _size++;
                }
            }

            void pop_back() {
            
                if (_size >= 1) {
                    _allocator.destroy(_c + _size);
                    _size--;
                }
            }

            void push_back (const value_type& val) {
            
                if (_size + 1 > _capacity) {
                    reserve((_capacity == 0 ? (float)1/2 : _capacity ) * 2);
                }
                _c[_size] = val;
                _size++;
            }
            allocator_type get_allocator() const {
            
                return _allocator;
            }

            iterator insert (iterator position, const value_type& val) {

              
                difference_type pos = position - begin();
                
                if (_size == 0)
                    reserve(1);
                else if (_size + 1 > _capacity)
                    reserve(_capacity * 2);
                for (size_t i = pos + 1; i <= _size; i++) {
                
                    std::swap(_c[pos], _c[i]);
                }
                _allocator.construct(_c + pos, val);
                _size++; 
                return begin() + pos;
            };

            void insert (iterator position, size_type n, const value_type& val) {

                difference_type pos = position - begin();
                
                if (_size == 0)
                    reserve(n);
                else if ( n + _size > _capacity) {
                
                    if (n > _size)
                        reserve((n + _size) );
                    else
                        reserve((_capacity) * 2);
                }
                for (size_t i = pos; i < pos + n; i++) {
                
                    _allocator.construct(_c + i + n, _c[i]);
                }
                for (size_t i = pos; i < pos + n;i++) {
                
                    _allocator.construct(_c + i, val);
                    _size++;
                }
                
            };

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value,InputIterator >::type = InputIterator()) {

                difference_type pos = position - begin();
                unsigned long diff = last - first;

                if (_size == 0)
                    reserve(diff);
                else if ( diff + _size > _capacity) {
                
                    if (diff > _size)
                        reserve((diff + _size) );
                    else
                        reserve((_capacity) * 2);
                }
                for (size_t i = pos - 1; i < pos + diff; i++) {
                
                    _allocator.construct(_c + i + diff, _c[i]);
                }
                for (size_t i = pos; i < pos + diff;i++) {
                
                    _allocator.construct(_c + i, *(first++));
                    _size++;
                }
            }

            void swap (Vector<T>& x) {


                std::swap(_c, x._c);
                std::swap(_capacity, x._capacity);
                std::swap(_size, x._size);
                std::swap(_allocator, x._allocator);
            }

            iterator erase (iterator position) {

                size_type pos = std::distance(begin(), position);

                _allocator.destroy(_c + pos);
                for  ( size_t i = pos; i < _size - 1; i++) {
                
                    _c[i] = _c[i + 1];
                }
                _size--;
                return begin() + pos;
            }

            iterator erase (iterator first, iterator last) {

                iterator pos(first);
                int i = 0;
                while (last != end())
                {
                    *first = *last;
                    first++;
                    last++;
                }
                for (;first != last;first++)
                    i++;
                _size -= i;
                return (pos);
            }
    };

    template <class T, class Alloc>
    bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {

        if (lhs._size == rhs._size)
            return (equal(lhs.begin(), lhs.end(), rhs.begin()));
        return false;
    };

    template <class T, class Alloc>
    bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {


        return !(lhs == rhs);
    };

    template <class T, class Alloc>
    bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {

        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    };

    template <class T, class Alloc>
    bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {

        return !(lhs > rhs);
    };

    template <class T, class Alloc>
    bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {
 
        return (lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

    };

    template <class T, class Alloc>
    bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) {


        return !(lhs < rhs);
    };


    template <class T, class Alloc>
    void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {

        std::swap(x._capacity, y._capacity);
        std::swap(x._size, y._size);
        std::swap(x._c, y._c);
        std::swap(x._allocator, y._allocator);
    };
};
