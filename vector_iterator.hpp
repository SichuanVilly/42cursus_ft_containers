/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:46:46 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/09 19:34:02 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORVECTOR_H
# define ITERATORVECTOR_H
//# include "vector.hpp"
# include "iterator_traits.hpp"

namespace ft
{
    
    // *******************
    // **** ITERATOR *****
    // *******************

    template <typename T>
    class vector_iterator
    {
        public:
            typedef typename ft::iterator_traits<T>::value_type			value_type;
            typedef typename ft::iterator_traits<T>::difference_type	difference_type;
            typedef typename ft::iterator_traits<T>::pointer			pointer;
            typedef typename ft::iterator_traits<T>::reference			reference;
            typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;

        private:
            pointer _data;

        public:
            
            vector_iterator() : _data(0) {}
            explicit vector_iterator(T data) : _data(data) {}
            template <typename U>
            vector_iterator(const vector_iterator<U> & other) {*this = other;}

            ~vector_iterator() {}

            pointer base() const {return (_data);}

            template <typename U>
            vector_iterator & operator=(const vector_iterator<U> & other)
            {
                _data = other.base();
                return (*this);
            }

            reference operator*() const {return (*_data);}
            reference operator[](difference_type n) const {return (*(_data + n));}
            pointer operator->() const {return (_data);}
            vector_iterator & operator++() {_data++; return (*this);}
            vector_iterator operator++(int) {vector_iterator temp(*this); _data++; return (temp);}
            vector_iterator & operator--() {_data--; return (*this);}
            vector_iterator operator--(int) {vector_iterator temp(*this); _data--; return (temp);}
            vector_iterator & operator+=(difference_type n) {_data += n; return (*this);}
            vector_iterator & operator-=(difference_type n) {_data -= n; return (*this);}
            vector_iterator operator+(difference_type n) const {return (vector_iterator(_data + n));}
            vector_iterator operator-(difference_type n) const {return (vector_iterator(_data - n));}
    };

    // Non Member Functions

    template <typename T, typename U>
    bool operator==(const vector_iterator<T> & lhs, const vector_iterator<U> & rhs) {return (lhs.base() == rhs.base());}
    template <typename T, typename U>
    bool operator!=(const vector_iterator<T> & lhs, const vector_iterator<U> & rhs) {return (lhs.base() != rhs.base());}
    template <typename T, typename U>
    bool operator>(const vector_iterator<T> & lhs, const vector_iterator<U> & rhs) {return (lhs.base() > rhs.base());}
    template <typename T, typename U>
    bool operator>=(const vector_iterator<T> & lhs, const vector_iterator<U> & rhs) {return (lhs.base() >= rhs.base());}
    template <typename T, typename U>
    bool operator<(const vector_iterator<T> & lhs, const vector_iterator<U> & rhs) {return (lhs.base() < rhs.base());}
    template <typename T, typename U>
    bool operator<=(const vector_iterator<T> & lhs, const vector_iterator<U> & rhs) {return (lhs.base() <= rhs.base());}
    
    template <typename T>
    vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T> & rhs)
    {return (vector_iterator<T>(rhs.base() + n));}
    
    template <typename T>
    vector_iterator<T> operator-(typename vector_iterator<T>::difference_type n, const vector_iterator<T> & rhs)
    {return (vector_iterator<T>(rhs.base() - n));}
    
    template <typename T, typename U>
    typename vector_iterator<T>::difference_type operator-(const vector_iterator<T> & lhs,const vector_iterator<U> & rhs) 
    {return (lhs.base() - rhs.base());}

};

#endif
