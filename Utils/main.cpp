# include <iostream>

# include "tree.hpp"
# include "pair.hpp"

int main( void ) {

    ft::avl<char, int> p;



    ft::pair<const char, int> a('a',10), b('b',30), c('c',50);
    ft::node<const char, int> *root = NULL;
    // a.first = 'a';
    // a.second = 10;
    // b.first = 'b';
    // b.second = 30;
    // c.first = 'c';
    // c.second = 50;
    // first['a']=10;
    // first['b']=30;
    // first['c']=50;

        // // std::cout << p._root->data->first << std::endl;
    root = p.Insert(root, NULL, b);
    root =  p.Insert(root, NULL, c);

    root = p.Insert(root, NULL, a);


    // std::cout << std::addressof(p._root->right) << " " << std::addressof(p._root->left) << std::endl;
    // p.Delete(a);
    p.print2D(root);
    //    tree.print2D();
    // p.TreeDelete(p, p._root->right->right);
    // std::cout << p._root->left->data->first << std::endl;
    // p.InorderTreeWalk(p._root, "root");
    return 0;
}

// # include "tree.hpp"

// int main()
// {
//     ft::node* root;
//     root = NULL;
  
//     // Function call to insert the nodes
//     root = Insert(root, NULL, 9);
//     root = Insert(root, NULL, 5);
//     root = Insert(root, NULL, 10);
//     root = Insert(root, NULL, 0);
//     root = Insert(root, NULL, 6);
//     root = Insert(root, NULL, 8);
//     // Print the tree before deleting node
//     std::cout << "Before deletion:\n";
//     printpreorder(root);
  
//     // Function Call to delete node 10
//     root = Delete(root, 6);
  
//     // Print the tree after deleting node
//     std::cout << "After deletion:\n";
//     printpreorder(root);
//     print2D(root);
// }