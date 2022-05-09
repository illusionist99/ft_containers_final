# include <iostream>

# include "Map/map.hpp"
# include "Vector/vector.hpp"
# include "Stack/stack.hpp"

# include <vector>
# include <stack>
# include <map>


void testVector() {

    // ft::Vector<int > ftVector;
    // std::vector<int> stdVector;

    // ft::Map<int , int> ftMap;
    // std::map<int, int> stdMap;

    // ft::Stack<int > ftStack;
    // std::stack<int > stdStack;


    // std::cout << " Inserting Elements To Vector \n";

    // for (int i = 0; i < 5000; i++) {
    
    //     ftVector.push_back( i );
    //     stdVector.push_back( i );
    // }

    // std::cout << " Comparing Size and Capacity \n";

    // std::cout << (ftVector.size() == stdVector.size()) << " " <<  (ftVector.capacity() == stdVector.capacity()) << std::endl;
 
    // std::cout << " Creating other vectors \n";

    // ft::Vector<int> ftSecond(ftVector);
    // std::vector<int> stdSecond(stdVector);

    // std::cout << " Comparing Size and Capacity \n";

    // std::cout << (ftVector.size() == stdVector.size()) << " " <<  (ftVector.capacity() == stdVector.capacity()) << std::endl;
 
    


    // std::vector<std::string> v;
    // ft::Vector<std::string> ft_v;
    // std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
    // size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
    // size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
    // ft::Vector<std::string>::iterator ft_it;
    // // test for an empty vector
    // v.push_back("hello");
    // ft_v.push_back("hello");
    // ft_it = ft_v.begin();
    // ft_it->length();

    // z1 = v.size();
    // c1 = v.capacity();
    // ft_z1 = ft_v.size();
    // ft_c1 = ft_v.capacity();
    // for (size_t i = 0; i < v.size(); ++i)
    //     s1 += v.at(i);

    // for (size_t i = 0; i < ft_v.size(); ++i)
    //     ft_s1 += ft_v.at(i);
    // /*---------------------------------------------*/
    // // test for a vector with capacity >= size + the new element
    // v.reserve(30);
    // ft_v.reserve(30);
    // v.push_back("string");
    // ft_v.push_back("string");
    // v.push_back("string");
    // ft_v.push_back("string");

    // z2 = v.size();
    // c2 = v.capacity();
    // ft_z2 = ft_v.size();
    // ft_c2 = ft_v.capacity();
    // for (size_t i = 0; i < v.size(); ++i)
    //     s2 += v.at(i);

    // for (size_t i = 0; i < ft_v.size(); ++i)
    //     ft_s2 += ft_v.at(i);
    // /*---------------------------------------------------------*/
    // // test for a vector with capactiy < size + the new element
    // for (size_t i = 0; i < 100; ++i)
    //     v.push_back("string");

    // for (size_t i = 0; i < 100; ++i)
    //     ft_v.push_back("string");

    // z3 = v.size();
    // c3 = v.capacity();
    // ft_z3 = ft_v.size();
    // ft_c3 = ft_v.capacity();
    // for (size_t i = 0; i < v.size(); ++i)
    //     s3 += v.at(i);

    // for (size_t i = 0; i < ft_v.size(); ++i)
    //     ft_s3 += ft_v.at(i);

    // std::cout << " Deleting Vector and cheking leaks \n";
    // // ftSecond.clear();
    // // ftVector.clear();
    // // stdVector.clear();


    ft::Map<int, int >a;

    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    // a.~Map();
}

int main( void ) {

    testVector();

    system("leaks a.out");
    return 0;
}