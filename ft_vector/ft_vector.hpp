/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:10:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 00:55:57 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <limits>
#include <cstddef>
#include "ft_vector_random_iterator.hpp"
#include "../ft_ReverseIterator.hpp"
#include "../ft_utils.hpp"
#include <iostream>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector {
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
			_ptr(0), _size(0), _alloc_size(0), _allocator(alloc) {
				// std::cout << "a\n";
				}
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
		: _ptr(NULL), _size(obj._size), _alloc_size(obj._alloc_size), _allocator(obj._allocator) {
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
			_size = right._size;
			_alloc_size = right._alloc_size;
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
			if (n <= _size) {
				for (size_type i = n; i < _size; ++i)
					_allocator.destroy(_ptr + i);
				
				_size = n;
				return ;
			}
			else if (n <= _alloc_size) {
				for (size_type i = _size; i < n; ++i)
					_allocator.construct(_ptr + i, val);
				_size = n;
				return ;
			}
			else if (n > _alloc_size) {
				pointer	tmp;
				try {
					tmp = _allocator.allocate(n);
				}
				catch(std::exception &e) {
					this->~vector();
					throw std::length_error("Wrong size");
				}
				std::memmove(tmp, _ptr, _size * sizeof(value_type));
				for (size_type i = _size; i < n; ++i)
					_allocator.construct(tmp + i, val);
				if (_ptr != NULL)
					_allocator.deallocate(_ptr, _alloc_size);
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
				if (_ptr != NULL)
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
		void	assign(InputIterator first, InputIterator last,
					   typename enable_if
					   < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0) {
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
				_alloc_size = dist;
			}
			else {
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(_ptr + i);
			}
			for (size_type i = 0; i < dist; ++i)
				_allocator.construct(_ptr + i, *(first + i));
			_size = dist;
		}
		void	assign(size_type n, const value_type &val) {
			if (n > _alloc_size) {
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(_ptr + i);
				_allocator.deallocate(_ptr, _alloc_size);
				try {
					_ptr = _allocator.allocate(n);
				}
				catch(std::exception &e) {
					this->~vector();
					throw std::length_error("Wrong size");
				}
				_alloc_size = n;
			}
			else {
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(_ptr + i);
			}
			for (size_type i = 0; i < n; ++i)
				_allocator.construct(_ptr + i, val);
			_size = n;
		}
		void	push_back(const value_type &val) {
			if (_size >= _alloc_size) {
				this->reserve(_alloc_size * 2 + (_alloc_size == 0));
			}
			_allocator.construct(this->end().getPointer(), val);
			_size++;
		}
		void	pop_back() {
			if (_size == 0)
				return ;
			_allocator.destroy(_ptr + _size - 1);
			_size--;
		}
		iterator	insert(iterator position, const value_type &val) {
			difference_type	dist = std::distance(this->begin(), position);
			if ((size_type)dist > _size)
				return this->begin();
			this->insert(position, 1, val);
			return (this->begin() + dist);
		}
		void		insert(iterator position, size_type n, const value_type &val) {
			difference_type	dist = std::distance(this->begin(), position);
			if ((size_type)dist > _size)
				return ;
			if (_size + n >= _alloc_size)
				this->reserve(_size + n);

			iterator	res = this->begin();
			position = res + dist;
			unsigned	i = 0;
			while (res++ < position)
				i++;
			std::memmove(_ptr + i + n, _ptr + i, (size_t)(_size - i) * sizeof(value_type));
			for (size_type j = 0; j < n; ++j)
				_allocator.construct(_ptr + i + j, val);
			_size += n;
		}
		template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
						typename enable_if < !std::numeric_limits<InputIterator>::is_specialized >::type* = 0) {
				difference_type	dist = std::distance(this->begin(), position);
				size_type amountVal = std::distance(first, last);
				if ((size_type)dist > _size)
					return ;
				if (_size + amountVal >= _alloc_size)
					this->reserve(_size * 2 + amountVal);
				iterator	res = this->begin();
				position = res + dist;
				unsigned	i = 0;
				while (res++ < position)
					i++;
				std::memmove(_ptr + i + amountVal, _ptr + i, (size_t)(_size - i) * sizeof(value_type));
				for (size_type j = 0; j < amountVal; ++j)
					_allocator.construct(_ptr + i + j, *(first + j));
				_size += amountVal;
			}
		iterator	erase(iterator position) {
			size_type	dist = std::distance(this->begin(), position);
			if (dist > _size)
				return (position);
			_allocator.destroy(_ptr + dist);
			std::memmove(_ptr + dist, _ptr + dist + 1, (size_t)(_size - dist) * sizeof(value_type));
			_size--;
			return (_ptr + dist);
		}
		iterator	erase(iterator first, iterator last) {
			size_type	dist = std::distance(this->begin(), first);
			size_type	amount = std::distance(first, last);
			if (dist > _size || amount > _size)
				return (first);
			for (size_type i = 0; i < amount; ++i)
				_allocator.destroy(_ptr + dist + i);
			std::memmove(_ptr + dist, _ptr + dist + amount, (size_t)(_size - dist - amount + 1) * sizeof(value_type));
			_size -= amount;
			return (_ptr + dist);
		}
		void	swap(vector &x) {
			ft::swap(this->_ptr, x._ptr);
			ft::swap(this->_size, x._size);
			ft::swap(this->_alloc_size, x._alloc_size);
			ft::swap(this->_allocator, x._allocator);
		}
		void	clear() {
			if (_ptr == NULL)
				return ;
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_ptr + i);
			_size = 0;
		}
		allocator_type	get_allocator() const {
			return (_allocator);
		}
	private:
		pointer				_ptr;
		size_type			_size;
		size_type			_alloc_size;
		allocator_type		_allocator;
	};
	template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (lhs.size() == rhs.size()
					&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!(lhs == rhs));
		}
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
												 rhs.begin(), rhs.end()));
		}
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!ft::lexicographical_compare(rhs.begin(), rhs.end(),
												  lhs.begin(), lhs.end()));
		}
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (ft::lexicographical_compare(rhs.begin(), rhs.end(),
												  lhs.begin(), lhs.end()));
		}
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (!ft::lexicographical_compare(lhs.begin(), lhs.end(),
												 rhs.begin(), rhs.end()));
		}
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
			x.swap(y);
		}
}


#endif
