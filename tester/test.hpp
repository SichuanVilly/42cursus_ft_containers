/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:22:49 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 19:34:00 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# include <vector>
# include "../vector.hpp"
# include <map>
# include "../map.hpp"
# include <stack>
# include "../stack.hpp"
# include <set>
# include "../set.hpp"

# include <list>

# include "Foo.hpp"
# include <sys/time.h>

# ifndef NAMESPACE
#  define NAMESPACE ft
# endif

void print_foo(const Foo & foo);

void vector_test();
void stack_test();
void map_test();
void set_test();

#endif