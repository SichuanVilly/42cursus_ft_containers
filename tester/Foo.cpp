/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Foo.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:14:46 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/16 18:36:20 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Foo.hpp"

Foo::Foo() : _n(), _s() {}

Foo::Foo(int n, std::string s) : _n(n), _s(s) {}

Foo::Foo(int n) : _n(n), _s() {}

Foo::Foo(const Foo & other) { *this = other; }

Foo::~Foo() {}

Foo & Foo::operator=(const Foo & other)
{
    if (this == & other)
        return *this;
    _n = other._n;
    _s = other._s;
    return *this;
}

const int & Foo::get_n() const { return _n; }

const std::string & Foo::get_s() const { return _s; }

void Foo::edit_n(int new_n) { _n = new_n; }

void Foo::edit_s(std::string new_s) { _s = new_s; }
