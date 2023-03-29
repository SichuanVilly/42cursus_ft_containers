/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:19:19 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 19:11:20 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void map_test()
{
    std::cout << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << "****** MAP ********" << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << std::endl;

    NAMESPACE::map<int, Foo> a;
    int size = 100;
    
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
            a[i] = Foo(i, std::string("even"));
        else
            a[i] = Foo(i, std::string("odd"));
    }

    NAMESPACE::map<int, Foo> b(a.begin(), a.end());

    std::cout << "-------------- int print --------------- " << std::endl;
    for (int i = 0; i < size; i++)
    {
        print_foo(b[i]);
        print_foo(b.at(i));
    }
    
    std::cout << "-------------- iterator print --------------- " << std::endl;
    for (NAMESPACE::map<int, Foo>::iterator it = b.begin(); it != b.end(); it++)
        print_foo(it->second);
    
    std::cout << "-------------- const_iterator print --------------- " << std::endl;
    for (NAMESPACE::map<int, Foo>::const_iterator cit = b.begin(); cit != b.end(); cit++)
        print_foo(cit->second);
        
    std::cout << "-------------- reverse_iterator print --------------- " << std::endl;
    for (NAMESPACE::map<int, Foo>::reverse_iterator rit = b.rbegin(); rit != b.rend(); rit++)
        print_foo(rit->second);
    
    std::cout << "-------------- const_reverse_iterator print --------------- " << std::endl;
    for (NAMESPACE::map<int, Foo>::const_reverse_iterator crit = b.rbegin(); crit != b.rend(); crit++)
        print_foo(crit->second);
    
    std::cout << b.size() << std::endl;
    if (b.empty())
        std::cout << "it is empty " << std::endl;
    else
        std::cout << " not empty " << std::endl;
    
    b.clear();
    
    std::cout << b.size() << std::endl;
    if (b.empty())
        std::cout << "it is empty " << std::endl;
    else
        std::cout << " not empty " << std::endl;
    
    NAMESPACE::pair<int, Foo> value = NAMESPACE::make_pair(0, Foo(0, std::string("im new")));
    bool is_insert = b.insert(value).second;
    std::cout << " is value inserted " << is_insert << std::endl;

    value = NAMESPACE::make_pair(1, Foo(1, std::string("im new")));
    is_insert = b.insert(value).second;
    std::cout << " is value inserted " << is_insert << std::endl;
    
    value = NAMESPACE::make_pair(2, Foo(2, std::string("im new")));
    is_insert = b.insert(value).second;
    std::cout << " is value inserted " << is_insert << std::endl;
    
    value = NAMESPACE::make_pair(3, Foo(3, std::string("im new")));
    is_insert = b.insert(value).second;
    std::cout << " is value inserted " << is_insert << std::endl;
    
    value = NAMESPACE::make_pair(3, Foo(3, std::string("im new")));
    is_insert = b.insert(value).second;
    std::cout << " is value inserted " << is_insert << std::endl;
    
    value = NAMESPACE::make_pair(15, Foo(15, std::string("im other insert")));
    b.insert(++(++b.begin()),value);
    
    b.insert(a.begin(), ++(++(++(++(++a.begin())))));

    for (NAMESPACE::map<int, Foo>::iterator it = b.begin(); it != b.end(); it++)
        print_foo(it->second);
    
    b.erase(b.begin());
    b.erase(++(++(++b.begin())));
    b.erase(b.begin(), --b.end());
    b.erase(b.begin()->first);
    
    std::cout << a.count(53) << std::endl;
    std::cout << a.count(15) << std::endl;
    std::cout << a.count(1) << std::endl;
    std::cout << a.count(42) << std::endl;
    std::cout << a.count(24) << std::endl;
    print_foo(a.find(53)->second);
    print_foo(a.find(15)->second);
    print_foo(a.find(1)->second);
    print_foo(a.find(42)->second);
    print_foo(a.find(24)->second);
    
    print_foo(a.equal_range(23).first->second);
    print_foo(a.equal_range(23).second->second);
    print_foo(a.lower_bound(23)->second);
    print_foo(a.upper_bound(23)->second);
}
