#pragma once

# include <iostream>

namespace ft {

    template <typename T> struct is_integral{static const bool value = false;};
    template <> struct is_integral<bool>{static const bool value = true;};
    template <> struct is_integral<char>{static const bool value = true;};
    // template <> struct is_integral<char16_t>{static const bool value = true;};
    // template <> struct is_integral<char32_t>{static const bool value = true;};
    // template <> struct is_integral<wchar_t>{static const bool value = true;};
    template <> struct is_integral<signed char>{static const bool value = true;};
    template <> struct is_integral<short int>{static const bool value = true;};
    template <> struct is_integral<int>{static const bool value = true;};
    template <> struct is_integral<long int>{static const bool value = true;};
    template <> struct is_integral<long long int>{static const bool value = true;};
    template <> struct is_integral<unsigned char>{static const bool value = true;};
    template <> struct is_integral<unsigned short int>{static const bool value = true;};
    template <> struct is_integral<unsigned int>{static const bool value = true;};
    template <> struct is_integral<unsigned long int>{static const bool value = true;};
    template <> struct is_integral<unsigned long long int>{static const bool value = true;};

    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };


    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
            InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }


    template<class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, 
            InputIt2 first2)
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!(*first1 == *first2)) {
                return false;
            }
        }
        return true;
    }

    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator {

        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };



    template< class iterator >
    struct iterator_traits {

        public: 

            typedef typename iterator::difference_type difference_type;
            typedef typename iterator::value_type value_type;
            typedef typename iterator::pointer pointer;
            typedef typename iterator::reference reference;
            typedef typename iterator::iterator_category iterator_category;
    };

    template< class T >
    struct iterator_traits<T*> {

        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template< class T >
    struct iterator_traits<const T*> {

        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };


    template <class T>
    class myiterator {

        public:
            T   *_pointer;
            typedef typename iterator<std::random_access_iterator_tag, T>::difference_type    difference_type;
            typedef typename iterator<std::random_access_iterator_tag, T>::value_type         value_type;
            typedef typename iterator<std::random_access_iterator_tag, T>::pointer            pointer;
            typedef typename iterator<std::random_access_iterator_tag, T>::reference          reference;
            typedef typename iterator<std::random_access_iterator_tag, T>::iterator_category  iterator_category;


            myiterator( void  ) {

                _pointer = NULL;
            }

            operator myiterator<const value_type> () const { return myiterator<const value_type>(_pointer); }
    
            myiterator( pointer p  ) {

                _pointer = p;
            }

            myiterator     &operator=(const myiterator &obj) {
            
                _pointer = obj._pointer;
                return (*this);
            }
            myiterator(const myiterator &obj) {
            
                *this = obj;
            }
            
            ~myiterator( void ) { }
            myiterator& operator+=(difference_type rhs)  {_pointer += rhs; return *this;}
            myiterator& operator-=(difference_type rhs)  {_pointer -= rhs; return *this;}
            T& operator*() const {return *_pointer;}
            T* operator->() const {return _pointer;}
            T& operator[](difference_type rhs) const {return _pointer[rhs];}
            
            myiterator& operator++() {++_pointer; return *this;}
            myiterator& operator--() {--_pointer; return *this;}
            myiterator operator++(int)  {myiterator tmp(*this); ++_pointer; return tmp;}
            myiterator operator--(int)  {myiterator tmp(*this); --_pointer; return tmp;}
            // myiterator operator+(const myiterator& rhs) {return myiterator(_pointer+rhs._pointer);}
        
            difference_type operator-(const myiterator& rhs) const {return _pointer-rhs._pointer;}
            // difference_type operator+(const myiterator& rhs) const {return _pointer+rhs._pointer;}
            myiterator operator+(difference_type rhs) const {return myiterator(_pointer+rhs);}
            myiterator operator-(difference_type rhs) const {return myiterator(_pointer-rhs);}
        
            friend myiterator operator+(difference_type lhs, const myiterator& rhs) {return myiterator(lhs+rhs._pointer);}
            friend myiterator operator-(difference_type lhs, const myiterator& rhs) {return myiterator(lhs-rhs._pointer);}
            
            bool operator==(const myiterator& rhs) const {return _pointer == rhs._pointer;}
            bool operator!=(const myiterator& rhs) const {return _pointer != rhs._pointer;}
            bool operator>(const myiterator& rhs) const {return _pointer > rhs._pointer;}
            bool operator<(const myiterator& rhs) const {return _pointer < rhs._pointer;}
            bool operator>=(const myiterator& rhs) const {return _pointer >= rhs._pointer;}
            bool operator<=(const myiterator& rhs) const {return _pointer <= rhs._pointer;}

    };

};
