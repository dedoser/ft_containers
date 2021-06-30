/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_bidirectional_iterator.hpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:46:57 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 15:48:15 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SET_BIDIRECTIONAL_ITERATOR_HPP
#define FT_SET_BIDIRECTIONAL_ITERATOR_HPP

namespace ft {
	template <class T, class Node>
		class SetBidirectIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		typedef T																				value_type;
		typedef T*																				pointer;
		typedef T&																				reference;
		typedef SetBidirectIterator<T, Node>													BiIterator;
		typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		SetBidirectIterator() : _ptr(0) {}
		SetBidirectIterator(const BiIterator &obj) : _ptr(obj._ptr) {}
		SetBidirectIterator(Node *ptr) : _ptr(ptr) {}
		virtual ~SetBidirectIterator() {}
		
		BiIterator	&operator=(const BiIterator &right) {
			if (this == &right)
				return (*this);
			_ptr = right._ptr;
			return (*this);
		}

		reference	operator*() {
			return (_ptr->value);
		}

		pointer		operator->() const {
			return (&_ptr->value);
		}

		BiIterator	operator++() {
			if (_ptr->left == _ptr && _ptr->right == _ptr &&
				_ptr->revParent != NULL) {
				_ptr = _ptr->revParent;
				return (_ptr);
			}
			if (isNULL(_ptr))
				return (NULL);
			if (!isNULL(_ptr->right)) {
				_ptr = _ptr->right;
				while (!isNULL(_ptr->left))
					_ptr = _ptr->left;
			}
			else {
				Node	*prev = _ptr;
				while (!isNULL(_ptr->parent)) {
					prev = _ptr;
					_ptr = _ptr->parent;
					if (_ptr->left == prev)
						break ;
				}
				if (isNULL(_ptr->parent) && isNULL(_ptr->right) && isNULL(_ptr->left))
					_ptr = _ptr->right;
				else if (isNULL(_ptr->parent) && _ptr->right == prev)
					while (!isNULL(_ptr))
						_ptr = _ptr->right;
			}
			return (_ptr);
		}

		BiIterator	operator++(int) {
			BiIterator	tmp(*this);
			this->operator++();
			return (tmp);
		}

		BiIterator	operator--() {
			if (isNULL(_ptr)) {
				_ptr = _ptr->parent;
				return (_ptr);
			}
			if (isNIL(_ptr->left) && _ptr->left->revParent != NULL) {
				_ptr = _ptr->left;
				return (_ptr->left);
			}
			if (!isNULL(_ptr->left)) {
				_ptr = _ptr->left;
				while (!isNULL(_ptr->right))
					_ptr = _ptr->right;
			}
			else {
				Node	*prev = _ptr;
				while (!isNULL(_ptr->parent)) {
					prev = _ptr;
					_ptr = _ptr->parent;
					if (_ptr->right == prev)
						break ;
				}
				if (isNULL(_ptr->parent) && isNULL(_ptr->right) && isNULL(_ptr->left))
					_ptr = _ptr->right;
				else if (isNULL(_ptr->parent) && _ptr->left == prev)
					while (!isNULL(_ptr))
						_ptr = _ptr->left;
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
		bool	isNULL(Node *n) {
			return ((n == NULL) || (n == n->right && n == n->left));
		}
	};

	template <class T, class Node>
	bool	operator==(const SetBidirectIterator<T, Node> &lhs,
					   const SetBidirectIterator<T, Node> &rhs) {
		return (lhs.get_pointer() == rhs.get_pointer() ||
				(isNIL(lhs.get_pointer()) && isNIL(rhs.get_pointer())));
	}

	template <class T, class Node>
	bool	operator!=(const SetBidirectIterator<T, Node> &lhs,
					   const SetBidirectIterator<T, Node> &rhs) {
		// std::cout << lhs.get_pointer() << ' ' << rhs.get_pointer() << '\n';
		return (lhs.get_pointer() != rhs.get_pointer());
	}
}

#endif
