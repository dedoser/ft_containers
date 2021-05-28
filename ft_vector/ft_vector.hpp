/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:10:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/05/28 18:58:34 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <limits>
#include <iostream>
#include "ft_vector_random_iterator.hpp"
#include "../ft_ReverseIterator.hpp"
#include "../ft_utils.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef	T											value_type;
		typedef	Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef	typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef	VectorRandomAccessIterator<T>				iterator;
		typedef	VectorRandomAccessIterator<const T>			const_iterator;
		typedef	ReverseIterator<iterator>					reverse_iterator;
		typedef	ReverseIterator<const_iterator>				const_reverse_iterator;
		typedef	ptrdiff_t									difference_type;
		typedef	size_t										size_type;

		explicit vector (const allocator_type &alloc = allocator_type()) :
			_ptr(0), _size(0), _alloc_size(0), allocator_type(alloc) {}
		explicit vector (size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type())
		: _ptr(NULL), _size(n), _alloc_size(n), _allocator(alloc) {
			try {
				_ptr = _allocator.allocate(n);
			}
			catch(std::exception &e) {
				this->~vector();
				throw std::length_error("Wrong size");
			}
			for (size_type i = 0; i < _size; ++i) {
				_allocator.construct(_ptr + i, val);
			}
		}
		template<class InputIterator>
			vector	(InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type(),
					typename enable_if
			 < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0)
		: _ptr(NULL), _size(0), _alloc_size(0), _allocator(alloc) {
			difference_type	dist = std::distance(first, last);
			_size = dist;
			_alloc_size = _size;
			try {
				_ptr = _allocator.allocate(_size);
			}
			catch(std::exception &e) {
				this->~vector();
				throw std::length_error("Wrong size");
			}
			for (size_type i = 0; i < _size; ++i) {
				_allocator.construct(_ptr + i, *(first + i));
			}
		}
		vector(const vector &obj) 
		: _ptr(NULL), _size(obj._size), _alloc_size(obj._alloc_size), _allocator(obj._alloc_size) {
			try {
				_ptr = _allocator.allocate(_alloc_size);
			}
			catch(std::exception &e) {
				this->~vector();
				throw std::length_error("Wrong size");
			}
			for (size_type i = 0; i < _size; ++i) {
				_allocator.construct(_ptr + i, *(obj._ptr + i));
			}
		}
		~vector() {
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_ptr + i);
			if (_alloc_size != 0)
				_allocator.deallocate(_ptr, _alloc_size);
			_ptr = NULL;
		}
		vector	&operator=(const vector &right) {
			if (this == &right)
				return (*this);
			this->~vector();
			try {
				_ptr = _allocator.allocate(right._alloc_size);
			}
			catch(std::exception &e) {
				this->~vector();
				throw std::length_error("Wrong size");
			}
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(_ptr + i, *(right._ptr + i));
			return (*this);
		}
		/*-----------------ITERATORS-----------------*/
		iterator		begin() {
			return (iterator(_ptr));
		}
		const_iterator	begin() const {
			return (const_iterator(_ptr));
		}
		iterator		end() {
			return (iterator(_ptr + _size));
		}
		const_iterator	end() const {
			return (const_iterator(_ptr + _size));
		}
		reverse_iterator		rbegin() {
			if (_size == 0)
				return (reverse_iterator(_ptr));
			return (reverse_iterator(_ptr + _size - 1));
		}
		const_reverse_iterator	rbegin() const {
			if (_size == 0)
				return (const_reverse_iterator(_ptr));
			return (const_reverse_iterator(_ptr + _size - 1));
		}
		reverse_iterator		rend() {
			if (_size == 0)
				return (reverse_iterator(_ptr));
			return (reverse_iterator(_ptr - 1));
		}
		const_reverse_iterator	rend() const {
			if (_size == 0)
				return (const_reverse_iterator(_ptr));
			return (const_reverse_iterator(_ptr - 1));
		}
		/*----------------CAPACITY-------------*/
		size_type	size() const {
			return (_size);
		}
		size_type	max_size() const {
			return (_allocator.max_size());
		}
		void		resize(size_type n, value_type val = value_type()) {
			if (n < _size) {
				for (size_type i = n; i < _size; ++i)
					_allocator.destroy(_ptr + i);
				_size = n;
				return ;
			}
			if (n <= _alloc_size) {
				for (size_type i = n; i < _alloc_size; ++i)
					_allocator.construct(_ptr + i, val);
				_size = _alloc_size;
				return ;
			}
			if (n > _alloc_size) {
				pointer	tmp;
				try {
					tmp = _allocator.allocate(n);
				}
				catch(std::exception &e) {
					this->~vector();
					throw std::length_error("Wrong size");
				}
				std::memmove(tmp, _ptr, _size * sizeof(val));
				for (size_type i = _size; i < n; ++i)
					_allocator.construct(tmp + i, val);
				_size = n;
				_alloc_size = n;
				_ptr = tmp;
			}
		}
		size_type	capacity() const {
			return (_alloc_size);
		}
		bool		empty() const {
			return (_size == 0);
		}
		void		reserve(size_type n) {
			if (n > _alloc_size) {
				pointer	tmp;
				try {
					tmp = _allocator.allocate(n);
				}
				catch(std::exception &e) {
					this->~vector();
					throw std::length_error("Wrong size");
				}
				std::memmove(tmp, _ptr, sizeof(value_type) * _size);
				_allocator.deallocate(_ptr, _alloc_size);
				_alloc_size = n;
				_ptr = tmp;
			}
		}
		/*--------------ELEMENT_ACCESS---------------*/
		reference		operator[] (size_type n) {
			return *(_ptr + n);
		}
		const_reference	operator[] (size_type n) const {
			return *(_ptr + n);
		}
		reference			at (size_type n) {
			if (n >= _size)
				throw std::out_of_range("Out of range");
			return *(_ptr + n);
		}
		const_reference		at (size_type n) const {
			if (n >= _size)
				throw std::out_of_range("Out of range");
			return *(_ptr + n);
		}
		reference			front() {
			return (*_ptr);
		}
		const_reference		front() const {
			return (*_ptr);
		}
		reference			back() {
			return (*(_ptr + _size - 1));
		}
		const_reference		back() const {
			return (*(_ptr + _size - 1));
		}
		/*-------------MODIFIERS----------*/
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last) {
			size_type dist = std::distance(first, last);
			if (dist > _alloc_size) {
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(_ptr + i);
				_allocator.deallocate(_ptr, _alloc_size);
				try {
					_ptr = _allocator.allocate(dist);
				}
				catch(std::exception &e) {
					this->~vector();
					throw std::length_error("Wrong size");
				}
			}
			else {
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(_ptr + i);
				if (_size < dist)
					_size = dist;
			}
			for (size_type i = 0; i < dist; ++i)
				_allocator.construct(_ptr + i, first + i);
		}
	void	push_back(const value_type &val) {
		if (_size == _alloc_size) {
			_alloc_size *= 2;
			this->reserve(_alloc_size);
		}
		_allocator.construct(_ptr + _size++, val);
	}
	void	pop_back() {
		if (_size == 0)
			return ;
		_allocator.destroy(_ptr + _size - 1);
		_size--;
	}
	iterator	insert(iterator position, const value_type &val) {
		difference_type	dist = std::distance(this->begin(), position);
		if (dist > _size)
			return this->begin();
		if (_size == _alloc_size)
			this->reserve(_size * 2);
		iterator	res = this->begin();
		position = res + dist;
		unsigned	i = 0;
		while (res != position) {
			i++;
			res++;
		}
		std::memmove(_ptr + i + 1, _ptr + i, (size_t)(_size - i) * sizeof(value_type));
		_allocator.construct(_ptr + i, val);
		_size++;
		return (res);
	}
	// void		insert(iterator position, size_type n, const value_type &val) {
	// 	if (_size == _alloc_size)
	// 		this->resize(_size * 2);

	// 	iterator	res = this->begin();
	// 	unsigned	i = 0;
	// 	while (res++ < position)
	// 		i++;
	// 	std::memmove(_ptr + i, _ptr + i + 1, (size_t)(_size - i));
	// 	_allocator.construct(_ptr + i - 1, val);
	// 	return (res - 1);
	// }
	private:
		pointer				_ptr;
		size_type			_size;
		size_type			_alloc_size;
		allocator_type		_allocator;
	};
}


#endif
