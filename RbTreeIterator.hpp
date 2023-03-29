/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RbTreeIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:28:15 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/14 20:26:36 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include "iterator_traits.hpp" 

namespace ft
{
    // *************************
    // ***** TREE_ITERATOR *****
    // *************************

    template <typename Node, typename T>
    class RbTreeIterator
    {
        public:
            typedef T                                                       value_type;
            typedef value_type *                                            pointer;
            typedef value_type &                                            reference;
            typedef typename ft::iterator_traits<Node>::value_type			node_type;
            typedef typename ft::iterator_traits<Node>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Node>::pointer			    node_pointer;
            typedef typename ft::iterator_traits<Node>::reference			node_reference;
            typedef typename ft::iterator_traits<Node>::iterator_category	iterator_category;

        protected:
            node_pointer _node;
            node_pointer _nil;
        
        public:
            RbTreeIterator() : _node(), _nil() {}
            explicit RbTreeIterator(node_pointer node, node_pointer nil) : _node(node), _nil(nil) {}
            template <typename U, typename V>
            RbTreeIterator(const RbTreeIterator<U, V> & other) { *this = other; }
            
            ~RbTreeIterator() {}

            node_pointer getNode() const {return (_node);}
            node_pointer getNil() const {return (_nil);}

            template <typename U, typename V>
            RbTreeIterator & operator=(const RbTreeIterator<U, V> & other)
            {
                _node = other.getNode();
                _nil = other.getNil();
                return (*this);
            }
            
            reference operator*() const { return (_node->data); }
            pointer operator->() const { return (&_node->data); }

            RbTreeIterator & operator++()
            {
                if (_node->right != _nil)
                {
                    _node = _node->right;
                    while (_node->left !=  _nil)
                        _node = _node->left;
                }
                else
                {
                    while (_node->parent != _nil && _node == _node->parent->right)
                        _node = _node->parent;
                    _node = _node->parent;
                }
                return (*this);
            }

            RbTreeIterator operator++(int) { RbTreeIterator temp(*this); ++(*this); return (temp);}

            RbTreeIterator & operator--()
            {
                if (_node->left != _nil)
                {
                    _node = _node->left;
                    while (_node->right != _nil)
                      _node = _node->right;  
                }
                else
                {
                    while (_node->parent != _nil && _node == _node->parent->left)
                        _node = _node->parent;
                    _node = _node->parent;
                }
                return (*this);
            }

             RbTreeIterator operator--(int) { RbTreeIterator temp(*this); --(*this); return (temp);}
    };

    template <typename N1, typename T1, typename N2, typename T2>
	bool	operator!=(const RbTreeIterator<N1, T1> &lhs, const RbTreeIterator<N2, T2> &rhs) { return (lhs.getNode() != rhs.getNode()); }
    template <typename N1, typename T1, typename N2, typename T2>
	bool	operator==(const RbTreeIterator<N1, T1> &lhs, const RbTreeIterator<N2, T2> &rhs) { return (lhs.getNode() == rhs.getNode()); }
    template <typename N1, typename T1, typename N2, typename T2>
	bool	operator>(const RbTreeIterator<N1, T1> &lhs, const RbTreeIterator<N2, T2> &rhs) { return (lhs.getNode() > rhs.getNode()); }
    template <typename N1, typename T1, typename N2, typename T2>
	bool	operator>=(const RbTreeIterator<N1, T1> &lhs, const RbTreeIterator<N2, T2> &rhs) { return (lhs.getNode() >= rhs.getNode()); }
    template <typename N1, typename T1, typename N2, typename T2>
	bool	operator<(const RbTreeIterator<N1, T1> &lhs, const RbTreeIterator<N2, T2> &rhs) { return (lhs.getNode() < rhs.getNode()); }
    template <typename N1, typename T1, typename N2, typename T2>
	bool	operator<=(const RbTreeIterator<N1, T1> &lhs, const RbTreeIterator<N2, T2> &rhs) { return (lhs.getNode() <= rhs.getNode()); }
}

#endif
