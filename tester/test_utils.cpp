/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:59:08 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/21 18:59:21 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void print_foo(const Foo & foo)
{
    std::cout << "int n: " << foo.get_n() << std::endl;
    std::cout << "string s: " << foo.get_s() << std::endl;
}