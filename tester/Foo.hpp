/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:01:47 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/21 15:55:31 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOO_HPP
# define FOO_HPP
# include <iostream>

class Foo
{
    private:
        int _n;
        std::string _s;

    public:
        Foo();
        Foo(int n, std::string s);
        Foo(int n);
        Foo(const Foo & other);
        ~Foo();

        Foo & operator=(const Foo & other);

        const int & get_n() const;
        const std::string & get_s() const;
        void edit_n(int new_n);
        void edit_s(std::string new_s);
};


#endif
