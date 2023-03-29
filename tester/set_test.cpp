/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:16:52 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 19:10:59 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void set_test()
{
    std::cout << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << "****** SET ********" << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << std::endl;
    
    NAMESPACE::set<int> a;
    int size = 100;
    
    for (int i = 0; i < size; i++)
            a.insert(i);

    NAMESPACE::set<int> b(a.begin(), a.end());
    
    std::cout << "-------------- iterator print --------------- " << std::endl;
    for (NAMESPACE::set<int>::iterator it = b.begin(); it != b.end(); it++)
        std::cout << *it << std::endl;
    
    std::cout << "-------------- const_iterator print --------------- " << std::endl;
    for (NAMESPACE::set<int>::const_iterator cit = b.begin(); cit != b.end(); cit++)
        std::cout << *cit << std::endl;
        
    std::cout << "-------------- reverse_iterator print --------------- " << std::endl;
    for (NAMESPACE::set<int>::reverse_iterator rit = b.rbegin(); rit != b.rend(); rit++)
        std::cout << *rit << std::endl;
    
    std::cout << "-------------- const_reverse_iterator print --------------- " << std::endl;
    for (NAMESPACE::set<int>::const_reverse_iterator crit = b.rbegin(); crit != b.rend(); crit++)
        std::cout << *crit << std::endl;
    
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
    
    bool is_insert = b.insert(0).second;
    std::cout << " is value inserted " << is_insert << std::endl;

    is_insert = b.insert(1).second;
    std::cout << " is value inserted " << is_insert << std::endl;
    
    is_insert = b.insert(2).second;
    std::cout << " is value inserted " << is_insert << std::endl;

    is_insert = b.insert(3).second;
    std::cout << " is value inserted " << is_insert << std::endl;
    
    is_insert = b.insert(3).second;
    std::cout << " is value inserted " << is_insert << std::endl;
    
    b.insert(++(++b.begin()), 4);
    
    b.insert(a.begin(), ++(++(++(++(++a.begin())))));

    for (NAMESPACE::set<int>::iterator it = b.begin(); it != b.end(); it++)
        std::cout << *it << std::endl;
    
    b.erase(b.begin());
    b.erase(++(++(++b.begin())));
    b.erase(b.begin(), --b.end());
    b.erase(b.begin());
    
    std::cout << a.count(53) << std::endl;
    std::cout << a.count(15) << std::endl;
    std::cout << a.count(1) << std::endl;
    std::cout << a.count(42) << std::endl;
    std::cout << a.count(24) << std::endl;
    std::cout << *a.find(53) << std::endl;
    std::cout << *a.find(15) << std::endl;
    std::cout << *a.find(1) << std::endl;
    std::cout << *a.find(42) << std::endl;
    std::cout << *a.find(24) << std::endl;

    
    std::cout << *a.equal_range(23).first;
    std::cout << *a.equal_range(23).second;
    std::cout << *a.lower_bound(23) << std::endl;
    std::cout << *a.upper_bound(23) << std::endl;
}
