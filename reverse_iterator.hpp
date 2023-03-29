/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:28:12 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/13 14:23:51 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H
# include "utils.hpp"

namespace ft
{
    // ***************************
	// **** REVERSE ITERATOR *****
	// ***************************

    template <typename T>
    class reverse_iterator
    {
        public:
            typedef  T                                                  iterator_type;
            typedef typename ft::iterator_traits<T>::value_type         value_type;
            typedef typename ft::iterator_traits<T>::difference_type    difference_type;
            typedef typename ft::iterator_traits<T>::pointer            pointer;
            typedef typename ft::iterator_traits<T>::reference          reference;
            typedef typename ft::iterator_traits<T>::iterator_category  iterator_category;

        private:
            iterator_type _iter;

        public:

            reverse_iterator() : _iter() {}
            explicit reverse_iterator(iterator_type x) : _iter(x) {}
            template <typename U>
            reverse_iterator(const reverse_iterator<U> & other) {*this = other;}

            ~reverse_iterator() {}

            iterator_type base() const {return (_iter);}

            template <typename U>
            reverse_iterator & operator=(const reverse_iterator<U> & other) 
            {
                _iter = other.base();
                return (*this);
            }
            
            reference operator*() const {iterator_type temp(_iter); return *(--temp);}
            reference operator[](difference_type n) const {return (*(_iter - n - 1));}
            pointer operator->() const {return (ft::addressof(operator*()));}
            reverse_iterator & operator++() {_iter--; return (*this);}
            reverse_iterator operator++(int) {reverse_iterator temp(*this); _iter--; return (temp);}
            reverse_iterator & operator--() {_iter++; return (*this);}
            reverse_iterator operator--(int) {reverse_iterator temp(*this); _iter++; return (temp);}
            reverse_iterator operator+=(difference_type n) {_iter -= n; return (*this);}
            reverse_iterator operator-=(difference_type n) {_iter += n; return (*this);}
            reverse_iterator operator+(difference_type n) const {return (reverse_iterator(_iter - n));}
            reverse_iterator operator-(difference_type n) const {return (reverse_iterator(_iter + n));}
    };
    // Non Member Functions

    template <typename T, typename U>
    bool operator==(reverse_iterator<T> lhs, reverse_iterator<U> rhs) {return (lhs.base() == rhs.base());}
    template <typename T, typename U>
    bool operator!=(reverse_iterator<T> lhs, reverse_iterator<U> rhs) {return (lhs.base() != rhs.base());}
    template <typename T, typename U>
    bool operator>(const reverse_iterator<T> & lhs, const reverse_iterator<U> & rhs) {return (lhs.base() < rhs.base());}
    template <typename T, typename U>
    bool operator>=(const reverse_iterator<T> & lhs, const reverse_iterator<U> & rhs) {return (lhs.base() <= rhs.base());}
    template <typename T, typename U>
    bool operator<(const reverse_iterator<T> & lhs, const reverse_iterator<U> & rhs) {return (lhs.base() > rhs.base());}
    template <typename T, typename U>
    bool operator<=(const reverse_iterator<T> & lhs, const reverse_iterator<U> & rhs) {return (lhs.base() >= rhs.base());}

    template <typename T>
	reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> & rhs)
	{return (reverse_iterator<T>(rhs.base() - n));}
    template <typename T, typename U>
    typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T> & lhs, const reverse_iterator<U> & rhs)
    {return (rhs.base() - lhs.base());}

};

#endif