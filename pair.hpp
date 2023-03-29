/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:00:34 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/14 15:31:58 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_H
# define PAIR_H
# include <functional>

namespace ft
{
    // *********************
    // ******* PAIR ********
    // *********************
    
    template <typename T1, typename T2>
    struct pair
    {
        typedef T1     first_type;
        typedef T2     second_type;

        T1 first;
        T2 second;

        pair() : first(first_type()), second(second_type()) {}
        pair(const T1 & x, const T2 & y) : first(x), second(y) {}
        template<typename U1, typename U2>
        pair(const pair<U1, U2> & p) : first(p.first), second(p.second) {}

        pair& operator=(const pair & other)
        {
            if (this == & other)
                return (*this);
            first = other.first;
            second = other.second;
            return (*this);
        }
    };

    template< class T1, class T2 >
    pair<T1, T2> make_pair(T1 t, T2 u) {return (pair<T1, T2>(t, u));}

    template< class T1, class T2, class U1, class U2 >
    bool operator==(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs)
    {return (lhs.first == rhs.first && lhs.second == rhs.second);}

    template< class T1, class T2, class U1, class U2 >
    bool operator!=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs)
    {return !(lhs.first == rhs.first && lhs.second == rhs.second);}

    template< class T1, class T2, class U1, class U2 >
    bool operator<(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs)
    {
        if (lhs.first < rhs.first)
            return (true);
        else if (lhs.first > rhs.first)
            return (false);
        else if (lhs.second < rhs.second)
            return (true);
        return (false);
    }

    template< class T1, class T2, class U1, class U2 >
    bool operator<=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs )
    {
        if (lhs == rhs || lhs < rhs)
            return (true);
        return (false);
    }

    template< class T1, class T2, class U1, class U2 >
    bool operator>(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs)
    {
          if (lhs.first > rhs.first)
            return (true);
        else if (lhs.first < rhs.first)
            return (false);
        else if (lhs.second > rhs.second)
            return (true);
        return (false);
    }

    template< class T1, class T2, class U1, class U2 >
    bool operator>=(const pair<T1, T2>& lhs, const pair<U1, U2>& rhs)
    {
        if (lhs == rhs || lhs > rhs)
            return (true);
        return (false);
    }

}

#endif