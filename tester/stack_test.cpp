/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:57:43 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 19:14:05 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void stack_test()
{
    std::cout << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << "****** STACK ******" << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << std::endl;

    NAMESPACE::stack<Foo> a;
    NAMESPACE::stack<Foo> b;
    NAMESPACE::stack<Foo, std::list<Foo> > li;
    
    
    int size = 1000;
    
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
        {
            a.push(Foo(size, std::string("even")));
            li.push(Foo(i, std::string("even")));
        }
        else
        {
            a.push(Foo(i, std::string("odd")));
            li.push(Foo(i, std::string("odd")));   
        }
    }
    NAMESPACE::stack<Foo> c(a);
    
    if (a.empty())
        std::cout << "empty" << std::endl;
    else
        std::cout << "not empty" << std::endl;
    if (b.empty())
        std::cout << "empty" << std::endl;
    else
        std::cout << "not empty" << std::endl;
    if (c.empty())
        std::cout << "empty" << std::endl;
    else
        std::cout << "not empty" << std::endl;
    if (li.empty())
        std::cout << "empty" << std::endl;
    else
        std::cout << "not empty" << std::endl;
    std::cout << std::endl;

    std::cout << "size: " << std::endl;
    std::cout << a.size() << std::endl;
    std::cout << b.size() << std::endl;
    std::cout << c.size() << std::endl;
    std::cout << li.size() << std::endl;
    std::cout << std::endl;

    std::cout << "top: " << std::endl;
    print_foo(a.top());
    print_foo(c.top());
    print_foo(li.top());
    std::cout << std::endl;
    
    for (unsigned long i = 0; i < a.size() ; i++)
    {
        a.pop();
        print_foo(a.top());
    }
    for (unsigned long i = 0; i < b.size(); i++)
    {
            b.pop();
            print_foo(b.top());
    }
    for (unsigned long i = 0; i < c.size(); i++)
    {
            c.pop();
            print_foo(c.top());
    }
    for (unsigned long i = 0; i < li.size(); i++)
    {
            li.pop();
            print_foo(li.top());
    }
}
