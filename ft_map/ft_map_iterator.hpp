/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 17:14:18 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/17 18:36:11 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_ITERATOR_HPP
#define FT_MAP_ITERATOR_HPP

#include <iterator>

namespace ft {
	template <class T, class Node>
		class MapBidirectIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		typedef T																				value_type;
		typedef T*																				pointer;
		typedef T&																				reference;
		typedef MapBidirectIterator<T, Node>													BiIterator;
		typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		MapBidirectIterator() : _ptr(0) {}
		MapBidirectIterator(const BiIterator &obj) : _ptr(obj._ptr) {}
		MapBidirectIterator(Node *ptr) : _ptr(ptr) {}
		virtual ~MapBidirectIterator() {}
		
		BiIterator	&operator=(const BiIterator &right) {
			if (this == &right)
				return (*this);
			_ptr = right._ptr;
			return (*this);
		}

		reference	operator*() {
			return (_ptr->value);
		}

		pointer		operator->() {
			return (&_ptr->value);
		}

		BiIterator	operator++() {
			if (_ptr->right == NULL)
				if (_ptr->parent == NULL || _ptr->parent->value < _ptr->value)
					_ptr++
				else
					_ptr = _ptr->parent;
			else {
				_ptr = _ptr->right;
				while (_ptr->left != NULL)
					_ptr = _ptr->left;
			}
			return (_ptr);
		}

		BiIterator	operator++(int) {
			BiIterator	tmp(*this);
			this->operator++();
			return (tmp);
		}

		BiIterator	operator--() {
			if (_ptr->left == NULL)
				if (_ptr->parent == NULL || _ptr->parent->value > _ptr->value)
					_ptr--;
				else
					_ptr = _ptr->parent;
			else {
				_ptr = _ptr->left;
				while (_ptr->right != NULL)
					_ptr = _ptr->right;
			}
			return (_ptr);
		}

		BiIterator	operator--(int) {
			BiIterator	tmp(*this);
			this->operator--();
			return (tmp);
		}

		Node	*get_pointer() const {
			return (_ptr);
		}
	private:
		Node	*_ptr;
	};
}

#endif
