/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_random_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:02:37 by fignigno          #+#    #+#             */
/*   Updated: 2021/05/28 18:47:43 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_RANDOM_ITERATOR_HPP
#define FT_VECTOR_RANDOM_ITERATOR_HPP

#include <iterator>
#include <iostream>
namespace ft
{
	template <class T> class VectorRandomAccessIterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef T																				value_type;
		typedef T*																				pointer;
		typedef T&																				reference;
		typedef VectorRandomAccessIterator<T>													RaIterator;
		typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
		typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;

		VectorRandomAccessIterator() : _ptr(0) {}
		VectorRandomAccessIterator(const VectorRandomAccessIterator &obj) : _ptr(obj._ptr) {}
		VectorRandomAccessIterator(pointer ptr) : _ptr(ptr) {}
		virtual ~VectorRandomAccessIterator() {}

		RaIterator	&operator=(const VectorRandomAccessIterator &right) {
			if (this != &right)
				_ptr = right._ptr;
			return (*this);
		}

		reference		operator*(){
			return (*_ptr);
		}

		pointer	operator->() {
			return (_ptr);
		}

		RaIterator		operator++() {
			_ptr++;
			return (*this);
		}

		RaIterator		operator++(int) {
			RaIterator	tmp(*this);
			this->_ptr++;
			return (tmp);
		}

		RaIterator		operator--() {
				_ptr--;
				return (*this);
		}

		RaIterator		operator--(int) {
			RaIterator	tmp(*this);
			this->_ptr--;
			return (tmp);
		}

		RaIterator	operator+(difference_type n) {
			return (RaIterator(this->_ptr + n));
		}

		RaIterator	operator-(difference_type n) {
			return (RaIterator(this->_ptr - n));
		}

		RaIterator	&operator+=(difference_type n) {
			this->_ptr += n;
			return (*this);
		}

		RaIterator	&operator-=(difference_type n) {
			this->_ptr -= n;
			return (*this);
		}

		reference	operator[](difference_type index) {
			return (*(_ptr + index));
		}

		pointer	getPointer() const {
			return (this->_ptr);
		}

	private:
		pointer					_ptr;
	};

	template <class T>
	VectorRandomAccessIterator<T>	operator+
	(typename VectorRandomAccessIterator<T>::difference_type n,
		VectorRandomAccessIterator<T> &right) {
		return (right + n);	
	}
	
	template <class T>
	typename VectorRandomAccessIterator<T>::difference_type operator-
	(const VectorRandomAccessIterator<T> &left,
		const VectorRandomAccessIterator<T> &right) {
		return (left.getPointer() - right.getPointer());
	}

	template <class T>
	bool	operator==
	(const VectorRandomAccessIterator<T> &left,
	 const VectorRandomAccessIterator<T> &right) {
		return (left.getPointer() == right.getPointer());
	}
	
	template <class T>
	bool	operator!=
	(const VectorRandomAccessIterator<T> &left,
	 const VectorRandomAccessIterator<T> &right) {
		return (!(left == right));
	}

	template <class T>
	bool	operator>
	(const VectorRandomAccessIterator<T> &left,
	 const VectorRandomAccessIterator<T> &right) {
		return (left.getPointer() > right.getPointer());
	}
	
	template <class T>
	bool	operator<
	(const VectorRandomAccessIterator<T> &left,
	 const VectorRandomAccessIterator<T> &right) {
		return (left.getPointer() <right.getPointer());
	}
	
	template <class T>
	bool	operator>=
	(const VectorRandomAccessIterator<T> &left,
	 const VectorRandomAccessIterator<T> &right) {
		return (left > right || left == right);
	}
	template <class T>
	bool	operator<=
	(const VectorRandomAccessIterator<T> &left,
	 const VectorRandomAccessIterator<T> &right) {
		return (left < right || left == right);
	}
}


#endif
