# include "Vector/vector.hpp"
# include "Utils/iterator.hpp"
# include "Utils/reverse_iterator.hpp"
# include "Utils/pair.hpp"
# include "Map/map.hpp"
# include <iostream>
# include <vector>
# include <map>


int main ()
{

    ft::Map<int, int> a;

    ft::pair<int , int > b,c, d;
    c.first = 1;
    c.second = 1;
    d.second = 2;
    d.first = 2;
    b.first = 3;
    b.second = 3;
    a.insert(b);
    a.insert(c);
    a.insert(d);

    std::cout << a.size() << std::endl;
    ft::node<int, int, std::__1::less<int>, std::__1::allocator<ft::pair<const int, int> > > *g = a._root->getRoot();
    std::cout << a._root << std::endl;
    std::cout  << a._root->_root << std::endl;
    // std::cout << g << std::endl;
    // std::cout << a.begin()->first << "    " << a.end()->first << std::endl;

    // for (ft::Map<int, int>::iterator it = a.begin(); it != a.end(); it++) {
    
    //   std::cout << it->first << " ";
    // }
    return 0;
}