# include <iostream>

# include "avl_tree.hpp"
# include "pair.hpp"

int main( void ) {

    ft::BstTree<int, int> p;



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
    p.insert(p, a);
    // std::cout << p._root->data->first << std::endl;
    p.insert(p, b);
    // std::cout << std::addressof(p._root->right) << " " << std::addressof(p._root->left) << std::endl;
    p.insert(p, c);
    p.InorderTreeWalk(p._root, "root");
    // p.TreeDelete(p, p._root->right->right);
    // std::cout << p._root->left->data->first << std::endl;
    // p.InorderTreeWalk(p._root, "root");
    return 0;
}