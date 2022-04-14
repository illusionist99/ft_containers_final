#include <iostream>
#include <map>
# include "Map/map.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  ft::Map<char,int> first;

  ft::pair<char, int> a, b, c;

  // a.first = 'a';
  // a.second = 10;
  // b.first = 'b';
  // b.second = 30;
  // c.first = 'c';
  // c.second = 50;
  // first['a']=10;
  // first['b']=30;
  // first['c']=50;
  first.insert(a);
  first.insert(b);
  first.insert(c);
  // first['d']=70;

  ft::Map<char,int> second (first.begin(),first.end());

  ft::Map<char,int> third (second);

  ft::Map<char,int,classcomp> fourth;                 // class as Compare

  bool(*fn_pt)(char,char) = fncomp;
  ft::Map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
  for (ft::Map<char, int>::iterator it = first.begin(); it != first.end(); it++) { std::cout << it->first << std::endl;}
  return 0;
}

// # include "Vector/vector.hpp"
// # include "Utils/iterator.hpp"
// # include "Utils/reverse_iterator.hpp"
// # include "Utils/pair.hpp"
// # include "Map/map.hpp"
// # include <iostream>
// # include <vector>
// # include <map>


// int main ()
// {
//     std::map<int, int > h;
//     ft::Map<int, int> a;

//     ft::pair<int , int > b,c, d;
//     std::pair<int , int > b0,c0, d0;
//     c.first = 1;
//     c.second = 1;

//     d.second = 2;
//     d.first = 2;
    
//     b.first = 3;
//     b.second = 3;

//     c0.first = 1;
//     c0.second = 1;

//     d0.second = 2;
//     d0.first = 2;
    
//     b0.first = 3;
//     b0.second = 3;
//     ft::Map<int, int>::iterator u(NULL);
//     ft::Map<int, int>::iterator u2(NULL);

//     std::cout << (u != u2) << std::endl;
//     // ft::Map<int, int>::iterator y = a.end();
//     // ft::pair<ft::Map<int, int>::iterator, bool> it = a.insert(b);
//     // std::cout << (it).first << std::endl;

//     a.insert(d);
//     a.insert(c);
//     a.insert(b);
//     h.insert(c0);
//     h.insert(d0);
//     h.insert(b0); 
//     // a.ins
//     // a._tree.remove(c);
//     // std::cout << a.size() << std::endl;
//     // // ft::node<int, int, std::__1::less<int>, std::__1::allocator<ft::pair<const int, int> > > *g = a._root->getRoot();
//     // // std::cout << a._root << std::endl;
//     // // std::cout  << a._root->_root << std::endl;
//     // // // std::cout << g << std::endl;
//     std::cout << "root  " << a._tree.root << "\n" << "Left  " << a._tree.root->left << "\n" << "Right " << a._tree.root->right << std::endl;
//     // std::cout << "Iterators" << std::endl;
//     // ft::Map<int, int>::iterator u = a.begin();
//     // ft::Map<int, int>::iterator y = a.end();
//     // int z = 0;
//     // std::cout << ( u == y ) << std::endl;
//     // std::cout << u->first <<  "  " << y->first << std::endl;
//     // u++;
//     // std::cout << u->first << std::endl;
//     // return 0;
//     for (ft::Map<int, int>::iterator it = a.begin(); it != a.end(); it++) {
    
//       // std::cout << "|" << a[z++] << "|" << std::endl;
//       // std::cout << ( it == a.end() ) << std::endl;
//       std::cout  << it->first << " ";
//     //   y++;
//       // std::cout << ( u == y ) << std::endl;
//     }
//     std::cout << std::endl;
//     for (std::map<int, int>::iterator it = h.begin(); it != h.end(); it++) {
    
//        std::cout  << it->first << " ";
//     }
//     // system("leaks a.out");
//     // a._tree.display();
//     return 0;
// }

// // #include<iostream>
// // #include<cstdio>
// # include "Utils/scratch_avl.hpp"
// # include "Utils/pair.hpp"
// // #include<sstream>
// // #include<algorithm>
// // #define pow2(n) (1 << (n))
// // using namespace std;
// // struct avl {
// //    int d;
// //    struct avl *l;
// //    struct avl *r;
// // }*r;
// // class avl_tree {
// //    public:
// //       int height(avl *);
// //       int difference(avl *);
// //       avl *rr_rotat(avl *);
// //       avl *ll_rotat(avl *);
// //       avl *lr_rotat(avl*);
// //       avl *rl_rotat(avl *);
// //       avl * balance(avl *);
// //       avl * insert(avl*, int);
// //       void show(avl*, int);
// //       void inorder(avl *);
// //       void preorder(avl *);
// //       void postorder(avl*);
// //       avl_tree() {
// //          r = NULL;
// //       }
// // };
// // int avl_tree::height(avl *t) {
// //    int h = 0;
// //    if (t != NULL) {
// //       int l_height = height(t->l);
// //       int r_height = height(t->r);
// //       int max_height = max(l_height, r_height);
// //       h = max_height + 1;
// //    }
// //    return h;
// // }
// // int avl_tree::difference(avl *t) {
// //    int l_height = height(t->l);
// //    int r_height = height(t->r);
// //    int b_factor = l_height - r_height;
// //    return b_factor;
// // }
// // avl *avl_tree::rr_rotat(avl *parent) {
// //    avl *t;
// //    t = parent->r;
// //    parent->r = t->l;
// //    t->l = parent;
// //    cout<<"Right-Right Rotation";
// //    return t;
// // }
// // avl *avl_tree::ll_rotat(avl *parent) {
// //    avl *t;
// //    t = parent->l;
// //    parent->l = t->r;
// //    t->r = parent;
// //    cout<<"Left-Left Rotation";
// //    return t;
// // }
// // avl *avl_tree::lr_rotat(avl *parent) {
// //    avl *t;
// //    t = parent->l;
// //    parent->l = rr_rotat(t);
// //    cout<<"Left-Right Rotation";
// //    return ll_rotat(parent);
// // }
// // avl *avl_tree::rl_rotat(avl *parent) {
// //    avl *t;
// //    t = parent->r;
// //    parent->r = ll_rotat(t);
// //    cout<<"Right-Left Rotation";
// //    return rr_rotat(parent);
// // }
// // avl *avl_tree::balance(avl *t) {
// //    int bal_factor = difference(t);
// //    if (bal_factor > 1) {
// //       if (difference(t->l) > 0)
// //          t = ll_rotat(t);
// //       else
// //          t = lr_rotat(t);
// //    } else if (bal_factor < -1) {
// //       if (difference(t->r) > 0)
// //          t = rl_rotat(t);
// //       else
// //          t = rr_rotat(t);
// //    }
// //    return t;
// // }
// // avl *avl_tree::insert(avl *r, int v) {
// //    if (r == NULL) {
// //       r = new avl;
// //       r->d = v;
// //       r->l = NULL;
// //       r->r = NULL;
// //       return r;
// //    } else if (v< r->d) {
// //       r->l = insert(r->l, v);
// //       r = balance(r);
// //    } else if (v >= r->d) {
// //       r->r = insert(r->r, v);
// //       r = balance(r);
// //    } return r;
// // }
// // void avl_tree::show(avl *p, int l) {
// //    int i;
// //    if (p != NULL) {
// //       show(p->r, l+ 1);
// //       cout<<" ";
// //       if (p == r)
// //          cout << "Root -> ";
// //       for (i = 0; i < l&& p != r; i++)
// //          cout << " ";
// //          cout << p->d;
// //          show(p->l, l + 1);
// //    }
// // }
// // void avl_tree::inorder(avl *t) {
// //    if (t == NULL)
// //       return;
// //       inorder(t->l);
// //       cout << t->d << " ";
// //       inorder(t->r);
// // }
// // void avl_tree::preorder(avl *t) {
// //    if (t == NULL)
// //       return;
// //       cout << t->d << " ";
// //       preorder(t->l);
// //       preorder(t->r);
// // }
// // void avl_tree::postorder(avl *t) {
// //    if (t == NULL)
// //       return;
// //       postorder(t ->l);
// //       postorder(t ->r);
// //       cout << t->d << " ";
// // }
// // int main() {
// //    int c, i;
// //    avl_tree avl;
// //    while (1) {
// //       cout << "1.Insert Element into the tree" << endl;
// //       cout << "2.show Balanced AVL Tree" << endl;
// //       cout << "3.InOrder traversal" << endl;
// //       cout << "4.PreOrder traversal" << endl;
// //       cout << "5.PostOrder traversal" << endl;
// //       cout << "6.Exit" << endl;
// //       cout << "Enter your Choice: ";
// //       cin >> c;
// //       switch (c) {
// //          case 1:
// //             cout << "Enter value to be inserted: ";
// //             cin >> i;
// //             r = avl.insert(r, i);
// //          break;
// //          case 2:
// //             if (r == NULL) {
// //                cout << "Tree is Empty" << endl;
// //                continue;
// //             }
// //             cout << "Balanced AVL Tree:" << endl;
// //             avl.show(r, 1);
// //             cout<<endl;
// //          break;
// //          case 3:
// //             cout << "Inorder Traversal:" << endl;
// //             avl.inorder(r);
// //             cout << endl;
// //          break;
// //          case 4:
// //             cout << "Preorder Traversal:" << endl;
// //             avl.preorder(r);
// //             cout << endl;
// //          break;
// //          case 5:
// //             cout << "Postorder Traversal:" << endl;
// //             avl.postorder(r);
// //             cout << endl;
// //          break;
// //          case 6:
// //             exit(1);
// //          break;
// //          default:
// //             cout << "Wrong Choice" << endl;
// //       }
// //    }
// //    return 0;
// // }


// // int main()
// // {
// //     ft::avl<int, std::string> t;
// //     ft::pair<int , std::string> a0(60, "dfdf60");
// //     ft::pair<int , std::string> a1(20, "sdf20");

// //     ft::pair<int , int> a2(25, 25);

// //     ft::pair<int , int> a3(15, 15);

// //     ft::pair<int , int> a4(10, 10);
// //     ft::pair<int , int> a5(30, 30);

// //     t.insert(a0);
// //     t.insert(a1);
// //     // t.insert(a4);
// //     // t.insert(a5);
// //     // t.insert(a0);
// //     // t.insert(a2);

// //    //  t.insert(35);
// //    //  t.insert(67);
// //    //  t.insert(43);
// //    //  t.insert(21);
// //    //  t.insert(10);
// //    //  t.insert(89);
// //    //  t.insert(38);
// //    //  t.insert(69);
// //    //  t.display();
// //     // t.remove(a1);
// //     // t.remove(a3);
// //     // t.remove(a4);
// //     // t.remove(a0);
// //     t.remove(a0);
// //     t.remove(a1);
// //    //  t.remove(20);
// //    //  t.remove(38);
// //     t.display();
// // }