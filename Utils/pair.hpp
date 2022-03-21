#pragma once


namespace ft {

    template <class T1, class T2>
    struct pair {


        public:

            typedef T1 first_type;
            typedef T2 second_type;

            first_type _first;
            second_type _second;

            pair() {

                _first = first_type();
                _second = second_type();
            }

            template<class U, class V>
            pair (const pair<U,V>& pr) {
            
                *this = pr;
            }

            pair (const first_type& a, const second_type& b) {

                _first = a;
                _second = b;
            }

            pair& operator= (const pair& pr) {
                
                
                _first = pr._first;
                _second = pr._second;
                return *this;
            }
    };

    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first && lhs.second==rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }

}