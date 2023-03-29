/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:29:46 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/21 19:55:36 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void vector_test()
{
    std::cout << std::endl;
    std::cout << "********************" << std::endl;
    std::cout << "****** VECTOR ******" << std::endl;
    std::cout << "********************" << std::endl;
    std::cout << std::endl;
    
    NAMESPACE::vector<Foo> a;
    NAMESPACE::vector<Foo> b(10);
    int size = 1000;

    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
            a.push_back(Foo(i, std::string("even")));
        else
            a.push_back(Foo(i, std::string("odd")));
    }

    NAMESPACE::vector<Foo> c(a);

    std::cout << "------ a ------ " << std::endl;
    print_foo(a[0]);
    std::cout << "------ c ------ " << std::endl;
    print_foo(c[0]);

    std::cout << "------ a.at[100] ------" << std::endl;
    print_foo(a.at(100));

    std::cout << "------ a.front() ------" << std::endl;
    print_foo(a.front());

    std::cout << "------ b.back() ------" << std::endl;
    print_foo(a.back());
    
    std::cout << "------ a.data() ------" << std::endl;
    std::cout << a.data()->get_n() << std::endl;

    std::cout << "###### ITERATORS ######" << std::endl;
    std::cout << "------ begin ------" << std::endl;
    for (NAMESPACE::vector<Foo>::iterator it = a.begin(); it != a.begin() + 10; it++)
        print_foo(*it);
    std::cout << "------ cbegin ------" << std::endl;
    for (NAMESPACE::vector<Foo>::const_iterator cit = a.begin(); cit != a.begin() + 10; cit++)
        print_foo(*cit);
    std::cout << "------ rbegin ------" << std::endl;
    for (NAMESPACE::vector<Foo>::reverse_iterator rit = a.rbegin(); rit != a.rbegin() + 10; rit++)
        print_foo(*rit);
    std::cout << "------ crbegin ------" << std::endl;
    for (NAMESPACE::vector<Foo>::const_reverse_iterator crit = a.rbegin(); crit != a.rbegin() + 10; crit++)
        print_foo(*crit);
    std::cout << "------ end ------" << std::endl;
    for (NAMESPACE::vector<Foo>::iterator it = a.end() - 1; it != a.end() - 10; it--)
        print_foo(*it);
    std::cout << "------ cend ------" << std::endl;
    for (NAMESPACE::vector<Foo>::const_iterator cit = a.end() - 1; cit != a.end() - 10; cit--)
        print_foo(*cit);
    std::cout << "------ rend ------" << std::endl;
    for (NAMESPACE::vector<Foo>::reverse_iterator rit = a.rend() - 1; rit != a.rend() - 10; rit--)
        print_foo(*rit);
    std::cout << "------ crend ------" << std::endl;
    for (NAMESPACE::vector<Foo>::const_reverse_iterator crit = a.rend() - 1; crit != a.rend() - 10; crit--)
        print_foo(*crit);

    b.clear();
    if (a.empty() == false)
        std::cout << "not empty" << std::endl;
    else
        std::cout << "empty" << std::endl;
    if (b.empty() == false)
        std::cout << "not empty" << std::endl;
    else
        std::cout << "empty" << std::endl;
    if (c.empty() == false)
        std::cout << "not empty" << std::endl;
    else
        std::cout << "empty" << std::endl;

    std::cout << "------ size ------" << std::endl;
    std::cout << a.size() << std::endl;
    std::cout << b.size() << std::endl;
    std::cout << c.size() << std::endl;

    std::cout << "------ capacity ------" << std::endl;
    std::cout << b.capacity() << std::endl;
    b.reserve(15);
    std::cout << b.capacity() << std::endl;
    std::cout << std::endl;

    a.clear();
    b.push_back(Foo(0, std::string("new")));
    b.push_back(Foo(1, std::string("new")));
    b.push_back(Foo(2, std::string("new")));
    b.push_back(Foo(3, std::string("new")));
    b.push_back(Foo(4, std::string("new")));
    a.insert(a.begin(), *b.begin());
    a.insert(a.begin(), 5, *b.begin());
    a.insert(a.begin() + 5, b.begin(), b.end());

    a.pop_back();
    a.pop_back();

    for (NAMESPACE::vector<Foo>::iterator it = a.begin(); it != a.end(); it++)
        print_foo(*it);
    std::cout << std::endl;

    a.erase(a.begin() + 2);
    a.erase(a.begin(), a.end());

    if (a.empty())
        std::cout << "a is empty" << std::endl;
    std::cout << std::endl;

    c.resize(10);

    for (NAMESPACE::vector<Foo>::iterator it = c.begin(); it != c.end(); it++)
        print_foo(*it);
    std::cout << std::endl;
    
    c.swap(b);

    for (NAMESPACE::vector<Foo>::iterator it = c.begin(); it != c.end(); it++)
        print_foo(*it);
    std::cout << std::endl;
}
