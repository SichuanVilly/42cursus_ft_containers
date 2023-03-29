/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:20:58 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/14 19:15:27 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

namespace ft
{
    /* ENABLE IF */
        
    template<bool, typename T = void>
    struct enable_if
    {};

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    /* IS INTEGRAL */

    template <typename T>
    struct is_integral {static bool const value = false;};
    template<>
    struct is_integral<bool> {static bool const value = true;};
    template<>
    struct is_integral<char> {static bool const value = true;};
    template<>
    struct is_integral<char16_t> {static bool const value = true;};
    template<>
    struct is_integral<char32_t> {static bool const value = true;};
    template<>
    struct is_integral<wchar_t> {static bool const value = true;};
    template<>
    struct is_integral<signed char> {static bool const value = true;};
    template<>
    struct is_integral<short int> {static bool const value = true;};
    template<>
    struct is_integral<int> {static bool const value = true;};
    template<>
    struct is_integral<long int> {static bool const value = true;};
    template<>
    struct is_integral<long long int> {static bool const value = true;};
    template<>
    struct is_integral<unsigned char> {static bool const value = true;};
    template<>
    struct is_integral<unsigned short int> {static bool const value = true;};
    template<>
    struct is_integral<unsigned int> {static bool const value = true;};
    template<>
    struct is_integral<unsigned long int> {static bool const value = true;};
    template<>
    struct is_integral<unsigned long long int> {static bool const value = true;};
    

    /* IS EQUAL */

    template<typename InputIt>
    bool is_equal(InputIt first_b, InputIt first_e, InputIt second_b)
    {
        for (InputIt it = first_b; it != first_e; it++)
        {
            if (*it != *second_b++)
                return (false);
        }
        return (true);
    }

    /* LEXICOGRAPHICAL_COMPARE */

    template<typename InputIt1, typename InputIt2 >
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (InputIt1 it1 = first1; it1 != last1; it1++)
        {
            if (first2 == last2)
                return (false);
            if (*it1 < *first2)
                return (true);
            else if (*it1 > *first2)
                return (false);
            first2++;
        }
        return (first2 != last2);
    }

    /* ADDRESS OF */   

    template<typename T>
    T * addressof(T& arg)
    {
        return (reinterpret_cast<T*>(
                   &const_cast<char&>(
                       reinterpret_cast<const volatile char&>(arg))));
    }
    
    /* SWAP */

    template<typename T>
    void swap_(T & x, T & y)
    {
        T temp;
        
        temp = x;
        x = y;
        y = temp;
    }

};

#endif