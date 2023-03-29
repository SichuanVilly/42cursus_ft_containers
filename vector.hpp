/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvillena <pvillena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:28:24 by pvillena          #+#    #+#             */
/*   Updated: 2023/03/27 19:08:32 by pvillena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "utils.hpp"
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"
# include <iostream>

namespace ft
{
    // *******************
    // ***** VECTOR ******
    // *******************

    template <typename T, typename Allocator = std::allocator<T> >
    class vector
    {
            
        public:
            typedef T										value_type;
            typedef Allocator								allocator_type;

            typedef typename Allocator::size_type			size_type;
            typedef typename Allocator::difference_type		difference_type;

            typedef typename Allocator::reference			reference;
            typedef typename Allocator::const_reference		const_reference;
            typedef typename Allocator::pointer				pointer;
            typedef typename Allocator::const_pointer		const_pointer;

            typedef ft::vector_iterator<pointer>			iterator;
            typedef ft::vector_iterator<const_pointer>		const_iterator;
            typedef ft::reverse_iterator<iterator>			reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

        protected:
            pointer			_start;
            size_type		_size;
            size_type		_capacity;
            allocator_type	_alloc;

        public:
            /* CONSTRUCTORS */
            
            explicit vector(const allocator_type &Alloc = allocator_type()) : _start(0), _size(0), _capacity(0), _alloc(Alloc) {}
            explicit vector(size_type n, value_type const &value = value_type(), const allocator_type &Alloc = allocator_type()) :
            _size(n), _capacity(n), _alloc(Alloc)
            {
                if (n > _alloc.max_size())
                    throw (std::length_error("Error. Can not allocate"));
                if (n > 0)
                    _start = _alloc.allocate(_capacity);
                for (size_type i = 0; i < _capacity; i++)
                    _alloc.construct(&_start[i], value);
            }
            template<typename InputIt>
            vector(InputIt first, InputIt last, const allocator_type &Alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) :
            _start(0), _size(0), _capacity(0), _alloc(Alloc)
            {
                size_type i = 0;

                for (InputIt temp = first; temp != last; temp++)
                    i++;
                if (i > _alloc.max_size())
                    throw (std::length_error("Error. Can not allocate"));
                _capacity = i;
                if (i > 0)
                    _start = _alloc.allocate(_capacity);
                i = 0;
                for (i = 0; i < _capacity; i++)
                    _alloc.construct(&_start[i], *first++);
                _size = i;
            }
            
            /* COPY CONSTRUCTOR */

            vector (const vector & x) : _start(0), _size(0), _capacity(x._capacity), _alloc(x._alloc) {*this = x;}

            /* DESTRUCTOR */

            virtual ~vector()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(&_start[i]);
                _alloc.deallocate(_start, _capacity);
            }
            
            /* EQUAL OPERATOR */

            vector & operator=(const vector & other)
            {
                pointer temp;

                if (this == &other)
                    return (*this);
                temp = _alloc.allocate(other._size);
                for (size_type i = 0; i < other._size; i++)
                    _alloc.construct(&temp[i], other._start[i]);
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(&_start[i]);
                _alloc.deallocate(_start, _capacity);
                _capacity = other._size;
                _start = temp;
                _size = other._size;
                return (*this);
            }

            /* ASSIGN */

            template <typename InputIt>
            void assign (InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
            {
                size_type i = 0;

                for (size_type len = 0; len < _size; len++)
                    _alloc.destroy(&_start[len]);
                _alloc.deallocate(_start, _capacity);

                for (InputIt temp = first; temp != last; temp++)
                    i++;
                if (i > _alloc.max_size())
                    throw (std::length_error("Error. Can not allocate"));
                _capacity = i;
                if (i > 0)
                    _start = _alloc.allocate(_capacity);
                i = 0;
                for (i = 0; i < _capacity; i++)
                    _alloc.construct(&_start[i], *first++);
                _size = i;
            }


            void assign(size_type count, const T & value)
            {
                if (_capacity > count)
                {
                    for (size_type i = 0; i < _size; i++)
                        _alloc.destroy(&_start[i]);
                    for (size_type i = 0; i < count; i++)
                        _alloc.construct(&_start[i], value);
                    _size = count;
                }
                else
                {
                    for (size_type len = 0; len < _size; len++)
                        _alloc.destroy(&_start[len]);
                    _alloc.deallocate(_start, _capacity);
                    
                    _capacity = _size = count;
                    if (count > _alloc.max_size())
                        throw (std::length_error("Error. Can not allocate"));
                    if (count > 0)
                        _start = _alloc.allocate(_capacity);
                    for (size_type i = 0; i < _size; i++)
                        _alloc.construct(&_start[i], value);
                }
            }

            /* GET ALLOCATOR */

            allocator_type get_allocator() const {return (_alloc);}

            /* ELEMENT ACCESS */

            reference at(size_type pos) 
            {
                if (pos >= _size)
                    throw (std::out_of_range("Error. Out of range"));
                return *(_start + pos);
            }

            const_reference at(size_type pos) const
            {
                if (pos >= _size)
                    throw (std::out_of_range("Error. Out of range"));
                return *(_start + pos);
            }

            reference operator[](size_type n) {return (_start[n]);}

            reference front() {return *_start;}

            const_reference front() const {return *_start;}

            reference back() {return *(_start + _size - 1);}

            const_reference back() const {return *(_start + _size - 1);}

            T* data() {return (_start);}

            const T* data() const {return (_start);}

            /* ITERATORS */

            iterator				begin() {return (iterator(_start));}

            iterator				end() {return (iterator(_start + _size));}

            const_iterator			begin() const {return (const_iterator(_start));}
            
            const_iterator			end() const {return (const_iterator(_start + _size));}

            reverse_iterator		rbegin(void) {return (reverse_iterator(end()));}
            
            reverse_iterator		rend(void) {return (reverse_iterator(begin()));}

            const_reverse_iterator	rbegin(void) const {return (const_reverse_iterator(end()));}

            const_reverse_iterator	rend(void) const {return (const_reverse_iterator(begin()));}
            
            
            /* CAPACITY */

            bool empty() const 
            {
                if (_size == 0)
                    return true;
                return false;
            }

            size_type size() const
            {
                return (_size);
            };

            size_type max_size() const
            {
                return (_alloc.max_size());
            };

            void reserve(size_type new_cap)
            {
                pointer temp;

                if (new_cap < _capacity)
                    return ;
                if (new_cap > _alloc.max_size())
                    throw (std::length_error("Error. Can not allocate"));
                if (new_cap > 0)
                    temp = _alloc.allocate(new_cap);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(&temp[i], _start[i]);
                for (size_type i = 0; i < _size; i++)
                {
                    _alloc.destroy(&_start[i]);
                }
                // if (_capacity > 0)
                    _alloc.deallocate(_start, _capacity);
                _capacity = new_cap;
                _start = temp;
            }
            
            size_type capacity() const
            {
                return (_capacity);
            };

            /* MODIFIERS */

            void clear()
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(&_start[i]);
                _size = 0;
            }

            iterator insert(const_iterator pos, const T & value)
            {
                size_type i = pos - begin();

                if (_capacity < _size + 1)
                {
                    if (_capacity < 1)
                        reserve(10);
                    else
                        reserve(_capacity * 2);
                }
                for (iterator it = end(); it != begin() + i;)
                {
                    _alloc.construct(&(*it), *(--it));
                    _alloc.destroy(&(*it));
                }
                _alloc.construct(&_start[i], value);
                _size++;
                return (begin() + i);
            }

            iterator insert(const_iterator pos, size_type count, const T& value)
            {
                size_type i = pos - begin();

                while (_capacity < count + _size)
                {
                    if (_capacity == 0)
                        reserve(10);
                    else
                        reserve(_capacity * 2);
                }
                for (iterator it = end() + count - 1; it != begin() + i + count - 1; it--)
                {
                    _alloc.construct(&(*it), *(it - count));
                    _alloc.destroy(&(*(it - count)));
                }
                for (size_type j = 0; j < count; j++)
                    _alloc.construct(&*(begin() + i + j), value);
                _size += count;
                return (begin() + i);
            }

            template <typename InputIt>
            iterator insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type * = 0)
            {
                size_type count = 0;
                size_type i;

                for (InputIt it = first; it != last; it++)
                    count++;
                i = pos - begin();
                while (_capacity < count + _size)
                {
                    if (_capacity == 0)
                        reserve(10);
                    else
                        reserve(_capacity * 2);
                }
                for (iterator it = end() + count - 1; it != begin() + i + count - 1; it--)
                {
                    _alloc.construct(&(*it), *(it - count));
                    _alloc.destroy(&(*(it - count)));
                }
                for (size_type j = 0; j < count; j++)
                    _alloc.construct(&*(begin() + i + j), *first++);
                _size += count;
                return (begin() + i);
            }

            iterator erase(iterator pos)
            {
                size_type i = pos - begin();

                for (iterator it = begin() + i; it != end(); it++)
                {
                    _alloc.destroy(&*it);
                    if (it + 1 != end())
                        _alloc.construct(&*it, *(it + 1));
                }
                _size--;
                return (begin() + i);
            }

            iterator erase(iterator first, iterator last)
            {
                size_type i = first - begin();
                size_type diff = last - first;

                for (iterator it = begin() + i; it != end(); it++)
                {
                    _alloc.destroy(&*it);
                    if (it + diff != end())
                        _alloc.construct(&*it, *(it + diff));
                }
                _size -= diff;
                return (begin() + i);
            }

            void push_back(const T & value)
            {
                if (_size == _capacity)
                {
                    if (_capacity < 1)
                    {
                        reserve(10);
                    }
                    else
                        reserve(_capacity * 2);
                }
                _alloc.construct(&_start[_size++], value);
            }

            void pop_back()
            {
                if (_size > 0)
                    resize(_size - 1);
            }

            void resize(size_type count, T value = T())
            {
                if (_size > count)
                {
                    while (_size < count)
                        _alloc.destroy(&_start[--_size]);
                }
                else
                {
                    while (_capacity < count)
                    {
                        if (_capacity == 0)
                            reserve(10);
                        else
                            reserve(_capacity * 2);
                    }
                    while (_size < count)
                        _alloc.construct(&_start[_size++], value);
                }
                _size = count;
            }

            void swap(vector & other)
            {
                ft::swap_(_start, other._start);
                ft::swap_(_capacity, other._capacity);
                ft::swap_(_size, other._size);
            }

    };

    template<typename T, typename Alloc >
    bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        if (lhs.size() == rhs.size())
            return (ft::is_equal(lhs.begin(), lhs.end(), rhs.begin()));
        return (false);
    }
    
    template<typename T, typename Alloc >
    bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        if (lhs == rhs)
            return (false);
        else
            return (true);
    }

    template<typename T, typename Alloc >
    bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

    template<typename T, typename Alloc >
    bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));}

    template<typename T, typename Alloc >
    bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        if (lhs.size() == rhs.size() && ft::is_equal(lhs.begin(), lhs.end(), rhs.begin()))
            return (true);
        else if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
            return (true);
        return (false);
    }

    template<typename T, typename Alloc >
    bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        if (lhs.size() == rhs.size() && ft::is_equal(lhs.begin(), lhs.end(), rhs.begin()))
            return (true);
        else if (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()))
            return (true);
        return (false);
    }
    
}

#endif
