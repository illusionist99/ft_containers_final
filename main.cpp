# include <iostream>

# include "Map/map.hpp"
# include "Vector/vector.hpp"
# include "Stack/stack.hpp"

# include <vector>
# include <stack>
# include <map>


void testVector() {

/*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v1(300, "string");
            std::vector<std::string> v;
            ft::Vector<std::string> ft_v;
            v.insert(v.begin(), v1.begin(), v1.end());
            ft_v.insert(ft_v.begin(), v1.begin(), v1.end());
            ft_v.begin()->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::Vector<std::string> v1(300, "string");
            ft::Vector<std::string> ft_v;

            v.insert(v.end(), v1.begin(), v1.end());
            ft_v.insert(ft_v.end(), v1.begin(), v1.end());
            ft_v.begin()->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/
        {
            std::vector<std::string> v1(70, "hello");
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");
            ft::Vector<std::string>::iterator valid_it;

            v.reserve(100);
            ft_v.reserve(100);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 15, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 15, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + n && n > size ----------------------------------------*/
        {
            ft::Vector<std::string> v1(100, "hello");
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 4: the vector capacity < size + n && n <= size ----------------------------------------*/
        {
            std::vector<std::string> v1(15, "hello");
            std::vector<std::string> v(20, "string");
            ft::Vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
    std::cout<< cond <<std::endl;
}

int main( void ) {

    testVector();

    system("leaks a.out");
    return 0;
}