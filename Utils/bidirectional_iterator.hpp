#pragma once

# include <iostream>
# include "pair.hpp"
# include "scratch_avl.hpp"
# include "iterator.hpp"

namespace ft {



    template < class Key,                           // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,               // map::key_compare
    class Alloc = std::allocator<pair<const Key,T> > >
    class mapiterator {

        public:

            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::difference_type    difference_type;
            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::value_type         value_type;
            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::pointer            pointer;
            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::reference          reference;
            typedef typename iterator<std::random_access_iterator_tag, pair<const Key, T> >::iterator_category  iterator_category;
            
            
            typedef pair<const Key, T>              pair;
    
            operator mapiterator<const Key, T, Compare, Alloc> () const { return mapiterator<const Key, T, Compare, Alloc>(_current); }

            typedef typename avl<const Key, T, Compare, Alloc>::avl_node node;
            typedef avl<const Key, T, Compare, Alloc> tree;
            node *_current;
            tree root;
            pair *_safe;
            Alloc _alloc;
            typedef typename Alloc::template rebind<node>::other rebind_allocator;
            rebind_allocator _alloc_rebind;
            mapiterator( ) { _current = NULL;}
            mapiterator( node * current ) : _current(current) {

                root.root = current;
                if (_current == NULL) {
                    
                    // pair *_safe;
                    // _current = _alloc_rebind.allocate(1);
                    // _current->data = _alloc.allocate(1);
                    // _alloc.construct(_current->data, pair());
                    // _safe = _alloc.allocate(1);
                    // node tmp;
                    // _current = &tmp;
                } 
            }
            ~mapiterator() {
            
        
            }
            mapiterator( const mapiterator& obj ) {

                _current = obj._current;
            }
    
            mapiterator &operator=(const mapiterator& obj ) {

                _current = obj._current;
                return *this;
            }

            pair& operator*() const { if (_current == NULL) {return *_safe;} return *_current->data;}
            pair* operator->() const { if (_current) {return _current->data;} return NULL;}
            
            mapiterator& operator--() {
               node *tmp = _current->parent;
                _current = tmp->left;
                return *this;
            }
            mapiterator operator++(int)  {

                _current = root.treeSuccessor(_current);
                // node *p;
                
                // if (_current == nullptr)
                //     {
                //     // ++ from end(). get the root of the tree
                //     // _current = tree->root;
                    
                //     // error! ++ requested for an empty tree
                //     // if (_current == nullptr)
                //     //     throw UnderflowException { };
                    
                //     // move to the smallest value in the tree,
                //     // which is the first node inorder
                //         while (_current->left != nullptr) {
                //             _current = _current->left;
                //         }
                //     }
                //     else if (_current->right != nullptr)
                //     {
                //         // successor is the farthest left node of
                //         // right subtree
                //         _current = _current->right;
                        
                //         while (_current->left != nullptr) {
                //          _current = _current->left;
                //         }
                //     }
                //     else
                //     {
                //         // have already processed the left subtree, and
                //         // there is no right subtree. move up the tree,
                //         // looking for a parent for which _current is a left child,
                //         // stopping if the parent becomes NULL. a non-NULL parent
                //         // is the successor. if parent is NULL, the original node
                //         // was the last node inorder, and its successor
                //         // is the end of the list
                //         p = _current->parent;
                //         while (p != nullptr && _current == p->right)
                //         {
                //             _current = p;
                //             p = p->parent;
                //         }
                        
                //         // if we were previously at the right-most node in
                //         // the tree, _current = nullptr, and the iterator specifies
                //         // the end of the list
                //         _current = p;
                //     }
                
                return *this;
            }
            mapiterator operator--(int)  {mapiterator tmp(_current);  node *tmpo = _current->parent; _current = tmpo->left; return tmp;}
            // mapiterator operator+(const mapiterator& rhs) {return mapiterator(_root+rhs._root);}
            bool operator==(const mapiterator& rhs) const {if (_current && rhs._current) {return _current->data == rhs._current->data;} return (_current == rhs._current);}
            bool operator!=(const mapiterator& rhs) const {if (_current && rhs._current) {return _current->data != rhs._current->data;} return (_current != rhs._current);}

    };
}