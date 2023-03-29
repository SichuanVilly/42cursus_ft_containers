/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_time_std.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:37:54 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 20:00:14 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

unsigned long int	c_time(unsigned long int time_start)
{
    struct timeval		time;
    unsigned long int	ms;

    gettimeofday(&time, NULL);
    ms = (time.tv_sec * 1000) + (time.tv_usec / 1000) - time_start;
    return (ms);
}

static void vector_time()
{
    NAMESPACE::vector<int> v;
    int size = 200000;

    for (int i = 0; i < size; i++)
        v.push_back(i);
    v.clear();
}

static void stack_time()
{
    NAMESPACE::stack<int> s;
    int size = 200000;

    for (int i = 0; i < size; i++)
        s.push(i);
}

static void map_time()
{
    NAMESPACE::map<int, std::string> m;
    int size = 200000;

    for (int i = 0; i < size; i++)
        m.insert(NAMESPACE::make_pair(i, std::string("string")));
    m.clear();
}

static void set_time()
{
    NAMESPACE::set<int> s;
    int size = 200000;

    for (int i = 0; i < size; i++)
        s.insert(i);
    s.clear();
}

int main()
{
    unsigned long int t_start = c_time(0);
    vector_test();
    vector_time();
    stack_test();
    stack_time();
    map_test();
    map_time();
    set_test();
    set_time();

    std::cout << "time_std: " << c_time(t_start) << " ms " << std::endl;
    return 0;
}
