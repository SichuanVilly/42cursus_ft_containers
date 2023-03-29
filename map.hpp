/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:47:45 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 19:09:48 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include "RbTree.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"

namespace ft 
{
    // *******************
    // ******* MAP *******
    // *******************

    template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
            typedef Key                                             key_type;
            typedef T                                               mapped_type;
            typedef typename ft::pair<const Key, T>                 value_type;

            typedef typename Allocator::size_type                   size_type;
            typedef typename Allocator::difference_type             difference_type;
            typedef Compare                                         key_compare;
            typedef Allocator                                       allocator_type;

            typedef typename Allocator::reference                   reference;
            typedef typename Allocator::const_reference             const_reference;
            typedef typename Allocator::pointer                     pointer;
            typedef typename Allocator::const_pointer               const_pointer;

            class value_compare
            {
                protected:
                    key_compare	_comp;

                public:
                    typedef bool		result_type;
                    typedef value_type	first_argument_type;
                    typedef value_type	second_argument_type;

                    value_compare() : _comp() {}

                    bool	operator()(const value_type &lhs, const value_type &rhs) const { return (_comp(lhs.first, rhs.first)); }

            };

            typedef ft::RbTree<value_type, value_compare, allocator_type>	tree_type;
            typedef typename tree_type::iterator                            iterator;
            typedef typename tree_type::const_iterator                      const_iterator;
            typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;
        
        protected:
            tree_type _tree;
            key_compare _compare;
            value_compare  _value_compare;
            allocator_type _alloc;
        
        public:
            explicit map(const key_compare & comp = key_compare(), const Allocator & alloc = allocator_type()) : _tree(), _compare(comp), _value_compare(value_compare()), _alloc(alloc) {}
            
            template < typename InputIt >
            map(InputIt first, InputIt last, const key_compare & comp = key_compare(), const Allocator & alloc = allocator_type()) :
            _tree(), _compare(comp), _value_compare(value_compare()), _alloc(alloc)
            {
                for (InputIt it = first; it != last; it++)
                    _tree.insert(*it);
            }
            
            map(const map & other) {*this = other;}

            virtual ~map() {}

            /* EQUAL OPERATOR */

            map & operator=(const map & other)
            {
                if (this == & other)
                    return (*this);
                _tree = other._tree;
                _compare = other._compare;
                _value_compare = other._value_compare;
                _alloc = other._alloc;
                return (*this);
            }
            
            allocator_type get_allocator() const { return (_alloc);}

            /* ELEMENT ACCESS */

            mapped_type &operator[](const key_type &key)
            {
                iterator it = find(key);

                if (it != end())
                    return (it->second);
                return (insert(ft::make_pair(key, mapped_type())).first->second);
            }

            mapped_type & at(const key_type & key)
            {
                iterator it = find(key);
                
                if (it == end())
                    throw (std::out_of_range("Error. Out of range"));
                return (it->second);
            }

            const mapped_type at(const key_type & key) const
            {
                const_iterator cit = find(key);

                if (cit == end())
                    throw (std::out_of_range("Error. Out of range"));
                return (cit->second);
            }

            /* ITERATORS */

            iterator begin() { return (_tree.begin()); }
            iterator end() { return (_tree.end()); }
            const_iterator begin() const { return (_tree.begin()); }
            const_iterator end() const { return (_tree.end()); }
            
            reverse_iterator rbegin() { return (_tree.rbegin()); }
            reverse_iterator rend() { return (_tree.rend()); }
            const_reverse_iterator rbegin() const { return (_tree.rbegin()); }
            const_reverse_iterator rend() const { return (_tree.rend()); }


            /* CAPACITY */
            
            bool empty() const
            {
                if (_tree.getSize() == 0)
                    return true;
                return false;
            }

            size_type size() const {return (_tree.getSize());}
            
            size_type max_size() const {return (_tree.getMaxSize());}

            /* MODIFIERS */

            void clear() { _tree.clear(); }

            ft::pair<iterator, bool> insert(const value_type & value) {return (_tree.insert(value));}
            
            iterator insert(iterator pos, const value_type& value) {(void)pos; return (_tree.insert(value).first);}
            
            template< typename InputIt >
            void insert( InputIt first, InputIt last )
            {
                for (InputIt it = first; it != last; it++)
                    _tree.insert(*it);
            }

            void erase( iterator pos ) { _tree.erase(*pos); }

            void erase( iterator first, iterator last )
            {
              for (iterator it = first; it != last;)
					_tree.erase(*(it++));
            }

            size_type erase( const key_type & key )
            {
                iterator it = find(key);
                
                if (it != end())
                {
                    _tree.erase(*it);
                    return 1;
                }
                return 0;
            }

            void swap(map & x)
            {
                _tree.swap(x._tree);
                ft::swap_(_compare, x._compare);
                ft::swap_(_value_compare, x._value_compare);
                ft::swap_(_alloc, x._alloc);
            }

            /* LOOKUP */

            size_type count( const Key& key ) const
            {
                const_iterator cit = find(key);

                if (cit != end())
                    return 1;
                return 0;
            }

            iterator find( const key_type & key )
            {
                ft::Node<value_type> * node = _tree.find(ft::make_pair(key, mapped_type()));

                if (node == _tree.getNil())
                    return end();
                return (iterator(node, _tree.getNil()));
                
            }

            const_iterator find( const Key& key ) const
            {
                ft::Node<value_type> * node = _tree.find(ft::make_pair(key, mapped_type()));
                
                if (node == _tree.getNil())
                    return (end());
                return (const_iterator(node, _tree.getNil()));
            }

            iterator lower_bound (const key_type& k)
            {
                for (iterator it = begin(); it != end(); it++)
                {
                    if (_value_compare(*it, ft::make_pair(k, mapped_type())) == false)
                        return (it);
                }
                return end();
            }
            
            const_iterator lower_bound (const key_type& k) const
            {
                for (const_iterator cit = begin(); cit != end(); cit++)
                {
                    if (_value_compare(*cit, ft::make_pair(k, mapped_type())) == false)
                        return (cit);
                }
                return end();
            }

            iterator upper_bound (const key_type& k)
            {
                for (iterator it = begin(); it != end(); it++)
                {
                    if (_value_compare(ft::make_pair(k, mapped_type()), *it) == true)
                        return (it);
                }
                return end();
            }
            
            const_iterator upper_bound (const key_type& k) const 
            {
                for (const_iterator cit = begin(); cit != end(); cit++)
                {
                    if (_value_compare(ft::make_pair(k, mapped_type()), *cit) == true)
                        return (cit);
                }
                return end();
            }

            ft::pair<iterator, iterator> equal_range(const key_type &key) { return ft::make_pair(lower_bound(key), upper_bound(key)); }
            ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const{ return ft::make_pair(lower_bound(key), upper_bound(key)); }


            /* OBSERVERS */

            key_compare key_comp() const {return _compare;}

            value_compare value_comp() const {return _value_compare;}
    };

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        return ft::is_equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs)
    { return !(lhs==rhs); }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());} 
    
    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs)
    { return lhs == rhs || lhs < rhs; }

    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs)
    {return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());}
    
    template <typename Key, typename T, typename Compare, typename Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> & lhs, const ft::map<Key, T, Compare, Alloc> & rhs)
    {return lhs == rhs || lhs > rhs;}

    template <typename Key, typename T, typename Compare, typename Alloc>
    void swap(map<Key, T, Compare, Alloc> & x, map<Key, T, Compare, Alloc> & y) {x.swap(y);}
}

#endif