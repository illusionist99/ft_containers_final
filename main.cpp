# include "Vector/vector.hpp"
# include "Utils/iterator.hpp"
# include "Utils/reverse_iterator.hpp"
# include "Utils/pair.hpp"
# include "Map/map.hpp"
# include <iostream>
# include <vector>
class A {
public:

  A() {}
  ~A() {}
};

int main ()
{

    ft::map<int, int> a;

    ft::pair<int , int > b,c, d;
    a.insert(b);
    a.insert(c);
    a.insert(d);

    return 0;
}