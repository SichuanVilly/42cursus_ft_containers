/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:43:11 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/29 17:30:52 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <functional>
# include "RbTreeIterator.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"
# include "pair.hpp"

# define RED 0
# define BLACK 1

# define RDCOL "\001\e[38;5;206m"
# define BKCOL "\001\e[38;5;110m"
# define NOCOL "\001\e[0m\002"

namespace ft
{
    // ************************
    // ******** RBTREE ********
    // ************************
    
    template<typename T>
    class Node
    {
        public:
            T data;
            Node * left;
            Node * right;
            Node * parent;
            bool color;
        
        Node(const T & value) : data(value), left(0), right(0), parent(0), color(BLACK) {}

        ~Node() {}
        
    };

    template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T> >
    class RbTree
    {
        public:
            typedef T                                                       value_type;
            typedef ft::Node<T>                                             node_type;
            typedef size_t                                                  size_type;
            typedef Compare                                                 compare;
            typedef Allocator                                               allocator_type;
            typedef typename Allocator::template rebind<node_type>::other   node_allocator;
            
            typedef typename node_allocator::reference                      reference;
            typedef typename node_allocator::const_reference                const_reference;
            typedef typename node_allocator::pointer                        pointer;
            typedef typename node_allocator::const_pointer                  const_pointer;

            typedef ft::RbTreeIterator<pointer, T>                          iterator;
            typedef ft::RbTreeIterator<const_pointer, const T>              const_iterator;
            typedef ft::reverse_iterator<iterator>                          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
            
        protected:
            pointer _root;
            pointer _nil;
            size_type _size;
            node_allocator _node_alloc;
            allocator_type _pair_alloc;
            compare _compare;

        public:
        
            /* CONSTRUCTORS */

            RbTree() : _size(0), _compare(compare())
            {
                _nil = _node_alloc.allocate(1);
                _node_alloc.construct(_nil, value_type());
                _root = _nil;
                _nil->parent = _nil;
                _nil->left = _nil;
                _nil->right = _nil;
            }
            
            RbTree(const RbTree & other) {*this = other;}

            /* DESTRUCTOR */

            ~RbTree() 
            {
                destructor(_root);
                _node_alloc.destroy(_nil);
                _node_alloc.deallocate(_nil, 1);
            }
            
            /* EQUAL OPERATOR */

            RbTree & operator=(const RbTree & other)
            {
                if (this == & other)
                    return (*this);
                destructor(_root);
                _node_alloc.destroy(_nil);
                _node_alloc.deallocate(_nil, 1);
                _node_alloc = other._node_alloc;
                _pair_alloc = other._pair_alloc;
                _size = 0;
                _compare = other._compare;
                _nil = _node_alloc.allocate(1);
                _node_alloc.construct(_nil, value_type());
                _nil->parent = _nil;
                _nil->left = _nil;
                _nil->right = _nil;
                _root = _nil;
                copyHelp(other._root, other._nil);
                relink_tree();
                return (*this);
            }

            /* ELEMENT ACCESS */
            
            pointer getRoot() const {return (_root);}
            size_type getSize() const {return (_size);}
            pointer getNil() const {return (_nil);}
            size_type getMaxSize() const {return (_node_alloc.max_size());}

            /* ITERATORS */

            iterator begin() {return (iterator(min(), _nil));}
            iterator end() { return (iterator(_nil, _nil));}
            const_iterator begin() const {return (const_iterator(min(), _nil));}
            const_iterator end() const { return (const_iterator(_nil, _nil));}

            reverse_iterator rbegin() {return (reverse_iterator(end()));}
            reverse_iterator rend() {return (reverse_iterator(begin()));}
            const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));}
            const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}
            

            /* INSERT */

            ft::pair<iterator, bool> insert(const value_type & value)
            {
                pointer temp = _root;

                if (_root == _nil)
                {
                    _root = newNode(value);
                    _size++;
                    relink_tree();
                    return (ft::make_pair(iterator(_root, _nil), true));
                }
                while (temp)
                {
                    if (_compare(value, temp->data))
                    {
                        if (temp->left == _nil)
                        {
                            temp->left = newNode(value);
                            temp->left->parent = temp;
                            temp = temp->left;
                            break ;
                        }
                        temp = temp->left;
                    }
                    else if (_compare(temp->data, value))
                    {
                        if (temp->right == _nil)
                        {
                            temp->right = newNode(value);
                            temp->right->parent = temp;
                            temp = temp->right;
                            break ;
                        }
                        temp = temp->right;
                    }
                    else
                        return (ft::make_pair(iterator(temp, _nil), false));
                }
                fix_insertion(temp);
                _size++;
                relink_tree();
                return (ft::make_pair(iterator(temp, _nil), true));
            }

            /* ERASE */

            void erase(const value_type & value)
            {
                bool original_color;
                pointer node_er;
                pointer x;
                  
                if ((node_er = find(value)) == _nil)
                    return ;
                original_color = node_er->color;
                if (node_er->left == _nil)
                {
                    x = node_er->right;
                    transplant(node_er, x);
                }
                else if (node_er->right == _nil)
                {
                    x = node_er->left;
                    transplant(node_er, x);
                }
                else
                {
                    pointer y = node_er->right;

                    while (y != _nil && y->left != _nil)
                        y = y->left;
                    original_color = y->color;
                    x = y->right;
                    if (y->parent == node_er)
                        x->parent = y;
                    else
                    {
                        transplant(y, y->right);
                        y->right = node_er->right;
                        y->right->parent = y;
                    }
                    transplant(node_er, y);
                    y->left = node_er->left;
                    y->left->parent = y;
                    y->color = node_er->color;
                }
                _size--;
                _node_alloc.destroy(node_er);
                _node_alloc.deallocate(node_er, 1);
                if (original_color == BLACK)
                    DeleteFix(x);
                relink_tree();
            }

            /* UTILS */            

            pointer find(const value_type & value) const
            {
                pointer temp = _root;

                while (temp != _nil)
                {
                    if (_compare(temp->data, value))
                        temp = temp->right;
                    else if (_compare(value, temp->data))
                        temp = temp->left;
                    else
                        return (temp);
                }
                return (_nil);
            }
            
        protected:

            void DeleteFix(pointer x)
            {
                pointer w;

                while (x->parent != _nil && x->color == BLACK)
                {
                    if (x->parent->left == x)
                    {
                        w = x->parent->right;
                        if (w->color == RED)
                        {
                            w->color = BLACK;
                            x->parent->color = RED;
                            leftrotation(x->parent);
                            w = x->parent->right;
                        }
                        if (w->left->color == BLACK && w->right->color == BLACK)
                        {
                            w->color = RED;
                            x = x->parent;
                        }
                        else 
                        {
                            if (w->right->color == BLACK)
                            {
                                w->left->color = BLACK;
                                w->color = RED;
                                rightrotation(w);
                                w = x->parent->right;   
                            }
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->right->color = BLACK;
                            leftrotation(x->parent);
                            x = _root;
                        }
                    }
                    else
                    {
                        w = x->parent->left;
                        if (w->color == RED)
                        {
                            w->color = BLACK;
                            x->parent->color = RED;
                            rightrotation(x->parent);
                            w = x->parent->left;
                        }
                        if (w->left->color == BLACK && w->right->color == BLACK)
                        {
                            w->color = RED;
                            x = x->parent;
                        }
                        else
                        {
                            if (w->left->color == BLACK)
                            {
                                w->right->color = BLACK;
                                w->color = RED;
                                leftrotation(w);
                                w = x->parent->left;
                            }
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->left->color = BLACK;
                            rightrotation(x->parent);
                            x = _root;
                        }
                    }
                }
                x->color = BLACK;
            }
            
            void transplant(pointer u, pointer v)
            {
                if (u->parent == _nil)
                    _root = v;
                else if (u == u->parent->left)
                    u->parent->left = v;
                else
                    u->parent->right = v;
                v->parent = u->parent;
                
            }

            void relink_tree()
            {
                _root->color = BLACK;
                _root->parent = _nil;
                _nil->left = _root;
                _nil->right = _root;
            }
            
            pointer newNode(const value_type &value)
            {
                pointer new_node;
                
                new_node = _node_alloc.allocate(1);
                _node_alloc.construct(new_node, value);
                new_node->parent = _nil;
                new_node->left = _nil;
                new_node->right = _nil;
                new_node->color = RED;
                return (new_node);
            }

            void leftrotation(pointer x)
            {
                pointer y = x->right;

                x->right = y->left;
                if (y->left != _nil)
                    y->left->parent = x;
                y->parent = x->parent;
                if (x->parent == _nil)
                    _root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->left = x;
                x->parent = y;
            }

            void rightrotation(pointer y)
            {
                pointer x = y->left;

                y->left = x->right;
                if (x->right != _nil)
                    x->right->parent = y;
                x->parent = y->parent;
                if (y->parent == _nil)
                    _root = x;
                else if (y == y->parent->right)
                    y->parent->right = x;
                else
                    y->parent->left = x;
                x->right = y;
                y->parent = x;
            }

            void fix_insertion(pointer node)
            {
                while (node != _root && node->parent->color == RED)
                {
                    if (node->parent == node->parent->parent->left) // left parent
                    {
                        if (node->parent->parent->right->color == RED) // uncle is red
                        {
                            node->parent->color = BLACK;
                            node->parent->parent->right->color = BLACK;
                            node->parent->parent->color = RED;
                            node = node->parent->parent;
                        }
                        else if (node == node->parent->left) // left left case
                        {
                                node->parent->color = BLACK;
                                node->parent->parent->color = RED;
                                rightrotation(node->parent->parent);
                        }
                        else // left right case
                        {
                            node = node->parent;
                            leftrotation(node);
                        }
                    }
                    else // right parent
                    {
                        if (node->parent->parent->left->color == RED) // uncle is red
                        {
                            node->parent->color = BLACK;
                            node->parent->parent->left->color = BLACK;
                            node->parent->parent->color = RED;
                            node = node->parent->parent;
                        }
                        else if (node == node->parent->left) // right left case
                        {
                            node = node->parent;
                            rightrotation(node);
                        }
                        else // right right case
                        {
                            node->parent->color = BLACK;
                            node->parent->parent->color = RED;
                            leftrotation(node->parent->parent);
                        }
                    }
                }
            }
        
            size_type height(pointer _root)
            {
                size_type left_height, right_height;

                if (_root == _nil)
                    return (0);
                left_height = (height(_root->left));
                right_height = (height(_root->right));
                if (left_height > right_height)
                    return (left_height + 1);
                else
                    return (right_height + 1);
            }

            void	copyrecursion(pointer node, pointer nil)
			{				
				if (node != nil)
				{
					insert(node->data);
					if (node->right != nil)
						insert(node->right->data);
					if (node->left != nil)
						insert(node->left->data);
					copyrecursion(node->right, nil);
					copyrecursion(node->left, nil);
				}
			}

            void copyHelp(pointer node, pointer nil)
            {
                if (node == nil)
                    return ;
                insert(node->data);
                copyHelp(node->right, nil);
                copyHelp(node->left, nil);
            }
   
        public:

            void swap(RbTree & x)
            {
                ft::swap_(_root, x._root);
                ft::swap_(_nil, x._nil);
                ft::swap_(_size, x._size);
                ft::swap_(_node_alloc, x._node_alloc);
                ft::swap_(_pair_alloc, x._pair_alloc);
                ft::swap_(_compare, x._compare);
            }

            void clear()
            {
                if (_root && _root != _nil)
                {
                    destructor(_root);
                    _size = 0;
                    _root = _nil;
                }
            }

            void destructor(pointer node)
            {
                if (node != _nil)
                {
                    destructor(node->left);
                    destructor(node->right);
                    _node_alloc.destroy(node);
                    _node_alloc.deallocate(node, 1);
                }
            }

            pointer min() const
            {
                pointer temp = _root;

                while (temp != _nil && temp->left != _nil)
                    temp = temp->left;
                return (temp);
            }

            void print(const std::string & prefix = "", const ft::Node<T> * node = NULL, bool isLeft = false) const {
                if (node == NULL)
                    node = _root;
                if (node != _nil) {
                    std::cout << BKCOL << prefix << NOCOL;
                    std::cout << BKCOL << (isLeft ? "├──" : "└──" ) << NOCOL;
                    if (node->color == RED)
                        std::cout << RDCOL << node->data.first << NOCOL << std::endl;
                    else {
                        if (node->data.first == -1)
                            std::cout << "nil" << NOCOL << std::endl;
                        else
                            std::cout << node->data.first << NOCOL << std::endl;
                    }
                    print(prefix + (isLeft ? "│   " : "    "), node->right, true);
                    print(prefix + (isLeft ? "│   " : "    "), node->left, false);
                }
            }
    };
}

#endif
