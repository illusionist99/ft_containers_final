# include <iostream>

# include "avlTree.hpp"
# include "pair.hpp"

int main( void ) {

    ft::avl_tree<char, int> p;



     ft::pair<const char, int> a('a',10), b('b',30), c('c',50);

    // a.first = 'a';
    // a.second = 10;
    // b.first = 'b';
    // b.second = 30;
    // c.first = 'c';
    // c.second = 50;
    // first['a']=10;
    // first['b']=30;
    // first['c']=50;
    p.insert(a);
    // std::cout << p._root->data->first << std::endl;
    p.insert(b);
    // std::cout << std::addressof(p._root->right) << " " << std::addressof(p._root->left) << std::endl;
    p.insert( c);
    p.Delete(a);
    p.print2D();
    //    tree.print2D();
    // p.TreeDelete(p, p._root->right->right);
    // std::cout << p._root->left->data->first << std::endl;
    // p.InorderTreeWalk(p._root, "root");
    return 0;
}