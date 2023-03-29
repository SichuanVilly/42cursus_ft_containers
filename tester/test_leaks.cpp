/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_leaks.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:19:48 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 19:25:49 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void leaks()
{
    system("leaks test_leaks");
}

int main()
{
    vector_test();
    stack_test();
    map_test();
    set_test();

    leaks();
    return 0;
}
