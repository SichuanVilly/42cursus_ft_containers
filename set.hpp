/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:50:57 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 19:09:21 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include "pair.hpp"
# include "RbTree.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"

namespace ft
{

    // *******************
    // ******* SET *******
    // *******************
    
    template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Key> >
    class set
    {
        public:
            typedef Key                                                     key_type;
            typedef Key                                                     value_type;
        
            typedef typename Allocator::size_type                           size_type;
            typedef typename Allocator::difference_type                     difference_type;
            typedef Compare                                                 key_compare;
            typedef Compare                                                 value_compare;
            typedef Allocator                                               allocator_type;
                    
            typedef typename Allocator::reference                           reference;
            typedef typename Allocator::const_reference                     const_reference;
            typedef typename Allocator::pointer                             pointer;
            typedef typename Allocator::const_pointer                       const_pointer;
            
            typedef ft::RbTree<value_type, value_compare, allocator_type>	tree_type;
            typedef typename tree_type::const_iterator                      iterator;
            typedef typename tree_type::const_iterator                      const_iterator;
            typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;

        protected:
            tree_type _tree;
            key_compare _compare;
            allocator_type _alloc;
        
        public:
            explicit set(const key_compare & comp = key_compare(), const Allocator & alloc = allocator_type()) : _tree(), _compare(comp), _alloc(alloc) {}
            
            template <typename InputIt>
            set(InputIt first, InputIt last, const key_compare & comp = key_compare(), const Allocator & alloc = allocator_type()) :
            _tree(), _compare(comp), _alloc(alloc)
            {
                for (InputIt it = first; it != last; it++)
                    _tree.insert(*it);
            }

            set(const set & other) {*this = other;}

            virtual ~set() {}

            set & operator=(const set & other)
            {
                if (this == & other)
                    return *this;
                _tree = other._tree;
                _compare = other._compare;
                _alloc = other._alloc;
                return *this;
            }

            allocator_type get_allocator() const { return _alloc; }
            
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

            void swap(set & x)
            {
                _tree.swap(x._tree);
                ft::swap_(_compare, x._compare);
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
                ft::Node<value_type> * node = _tree.find(key);

                if (node == _tree.getNil())
                    return end();
                return (iterator(node, _tree.getNil()));
                
            }

            const_iterator find( const Key& key ) const
            {
                ft::Node<value_type> * node = _tree.find(key);
                
                if (node == _tree.getNil())
                    return (end());
                return (const_iterator(node, _tree.getNil()));
            }

            iterator lower_bound (const key_type& k)
            {
                for (iterator it = begin(); it != end(); it++)
                {
                    if (_compare(*it, k) == false)
                        return (it);
                }
                return end();
            }
            
            const_iterator lower_bound (const key_type& k) const
            {
                for (const_iterator cit = begin(); cit != end(); cit++)
                {
                    if (_compare(*cit, k) == false)
                        return (cit);
                }
                return end();
            }

            iterator upper_bound (const key_type& k)
            {
                for (iterator it = begin(); it != end(); it++)
                {
                    if (_compare(k, *it) == true)
                        return (it);
                }
                return end();
            }
            
            const_iterator upper_bound (const key_type& k) const 
            {
                for (const_iterator cit = begin(); cit != end(); cit++)
                {
                    if (_compare(k, *cit) == true)
                        return (cit);
                }
                return end();
            }

            ft::pair<iterator, iterator> equal_range(const key_type &key) { return ft::make_pair(lower_bound(key), upper_bound(key)); }
            ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const{ return ft::make_pair(lower_bound(key), upper_bound(key)); }

            /* OBSERVERS */

            key_compare key_comp() const {return _compare;}

            key_compare value_comp() const {return _compare;}
    };

    template <typename Key, typename Compare, typename Alloc>
    bool operator==(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        return ft::is_equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename Key, typename Compare, typename Alloc>
    bool operator!=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs)
    { return !(lhs==rhs); }

    template <typename Key, typename Compare, typename Alloc>
    bool operator<(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());} 
    
    template <typename Key, typename Compare, typename Alloc>
    bool operator<=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs)
    { return lhs == rhs || lhs < rhs; }

    template <typename Key, typename Compare, typename Alloc>
    bool operator>(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs)
    {return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());}
    
    template <typename Key, typename Compare, typename Alloc>
    bool operator>=(const ft::set<Key, Compare, Alloc> & lhs, const ft::set<Key, Compare, Alloc> & rhs)
    {return lhs == rhs || lhs > rhs;}

    template <typename Key, typename Compare, typename Alloc>
    void swap(set<Key, Compare, Alloc> & x, set<Key, Compare, Alloc> & y) {x.swap(y);}
}

#endif