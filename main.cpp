#include "Vector/vector.hpp"



#include <iostream>

class A {
public:

  A() {}
  ~A() {}
};

int main ()
{

  // constructors used in the same order as described above:
  // ft::vector<int> first;                                // empty vector of ints
  // ft::vector<int> second (4,100);                       // four ints with value 100
  // ft::vector<int> third (second.begin(),second.end());  // iterating through second
  // ft::vector<int> fourth (third);                       // a copy of third

  // // the iterator constructor can also be used to construct from arrays:
  // int myints[] = {16,2,77,29};
  // ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  // std::cout << "The contents of fifth are:";
  // for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
  //   std::cout << ' ' << *it;
  // std::cout << '\n';
 
  // ft::vector<int> foo (3,0);
  // ft::vector<int> bar (5,0);

  // bar = foo;
  // foo = ft::vector<int>();

  // std::cout << "Size of foo: " << int(foo.size()) << '\n';
  // std::cout << "Size of bar: " << int(bar.size()) << '\n';
 
  // ft::vector<int> myvector;
  // for (int i=1; i<=5; i++) myvector.push_back(i);

  // std::cout << "myvector contains:";
  // for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
  //   std::cout << ' ' << *it;
  // std::cout << '\n';
 
  //  ft::vector<int> end;
  // for (int i=1; i<=5; i++) end.push_back(i);

  // std::cout << "end contains:";
  // for (ft::vector<int>::iterator it = end.begin() ; it != end.end(); ++it)
  //   std::cout << ' ' << *it;
  // std::cout << '\n';
 
  // ft::vector<int> rever (5);  // 5 default-constructed ints
  // // rever.push_back(5);
  // int i=0;

  // ft::vector<int>::reverse_iterator rit = rever.rbegin();
  // // std::cout << *(rever.rbegin() + 4) << std::endl;
  // for (; rit!= rever.rend(); ++rit)
  //   *rit = ++i;

  // std::cout << "rever contains:";
  // for (ft::vector<int>::iterator it = rever.begin(); it != rever.end(); ++it)
  //   std::cout << ' ' << *it;
  // std::cout << '\n';
//  unsigned int i;
//   ft::vector<int> foo (3,100);   // three ints with a value of 100
//   ft::vector<int> bar (5,200);   // five ints with a value of 200

//   foo.swap(bar);

//   std::cout << "foo contains:";
//   for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

//   std::cout << "bar contains:";
//   for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';
//   system("leaks a.out");
  return 0;
}