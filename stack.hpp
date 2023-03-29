/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:57:38 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 18:50:46 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include "vector.hpp"

namespace ft
{
    // ********************
    // ****** STACK *******
    // ********************

    template <typename T, class Container = vector<T> >
    class stack
    {
        public:
            typedef Container                               container_type;
            typedef typename Container::value_type          value_type;
            typedef typename Container::size_type           size_type;
            typedef typename Container::reference           reference;
            typedef typename Container::const_reference     const_reference;

        protected:
            container_type c;

        public:
            explicit stack(const Container& cont = container_type()) : c(cont) {}
            stack(const stack& other) {*this = other;}
            virtual ~stack() {}

            stack & operator=(const stack & other)
            {
                if (this == &other)
                    return (*this);
                c = other.c;
                return (*this);
            }

            /* ELEMENT ACCESS */

            reference top() {return (c.back());}

            const_reference top() const {return (c.back());}

            /* CAPACITY */

            bool empty() const {return (c.empty());}

            size_type size() const {return (c.size());}

            /* MODIFIERS */

            void push(const value_type & value) {c.push_back(value);}

            void pop() {c.pop_back();}

            /* OPERATORS */
            
            template <typename U, typename V>
            friend bool operator==(const stack<U, V> & lhs, const stack<U, V> & rhs);
            template <typename U, typename V>
            friend bool operator<(const stack<U, V> & lhs, const stack<U, V> & rhs);

    };

    template< typename T, typename Container >
    bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (lhs.c == rhs.c);}
    template< typename T, typename Container >
    bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return !(lhs == rhs);}
    template< typename T, typename Container >
    bool operator<(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (lhs.c < rhs.c);}
    template< typename T, typename Container >
    bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (lhs < rhs || lhs == rhs);}
    template< typename T, typename Container >
    bool operator>(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (rhs < lhs);}
    template< typename T, typename Container >
    bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {return (rhs < lhs || lhs == rhs);}
    
}

#endif