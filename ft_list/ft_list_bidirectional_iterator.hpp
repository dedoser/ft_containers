/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_bidirectional_iterator.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:44:02 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/17 17:57:18 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_BIDIRECTIONAL_ITERATOR_HPP
#define FT_LIST_BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>

namespace ft {
	template <class T, class Node>
		class ListBidirectionalIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		typedef T																				value_type;
		typedef T*																				pointer;
		typedef T&																				reference;
		typedef ListBidirectionalIterator<T, Node>													BiIterator;
		typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		
		ListBidirectionalIterator() : _ptr(0) {}
		ListBidirectionalIterator(const BiIterator &obj) : _ptr(obj._ptr) {}
		ListBidirectionalIterator(Node *ptr) : _ptr(ptr) {}
		virtual ~ListBidirectionalIterator() {}

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

		BiIterator	operator++(int) {
			BiIterator	tmp(*this);
			this->_ptr = this->_ptr->next;
			return (tmp);
		}

		BiIterator	operator++() {
			this->_ptr = this->_ptr->next;
			return (*this);
		}

		BiIterator	operator--() {
			this->_ptr = this->_ptr->prev;
			return (*this);
		}

		BiIterator	operator--(int) {
			BiIterator	tmp(*this);
			this->_ptr = this->_ptr->prev;
			return (tmp);
		}

		Node	*get_pointer() const {
			return (_ptr);
		}
	private:
		Node				*_ptr;
	};

	template<class T, class Node>
	bool	operator==(const ListBidirectionalIterator<T, Node> &lhs,
					   const ListBidirectionalIterator<T, Node> &rhs) {
		return (lhs.get_pointer() == rhs.get_pointer());
	}

	template<class T, class Node>
	bool	operator!=(const ListBidirectionalIterator<T, Node> &lhs,
					   const ListBidirectionalIterator<T, Node> &rhs) {
		return (lhs.get_pointer() != rhs.get_pointer());
   }
}

#endif
