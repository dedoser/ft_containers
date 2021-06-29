/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 18:23:43 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 01:23:20 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_HPP
#define FT_LIST_HPP

#include "ft_list_bidirectional_iterator.hpp"
#include <memory>
#include "../ft_ReverseIterator.hpp"
#include "../ft_utils.hpp"
#include <exception>
#include <stdexcept>
#include <cstring>
#include <limits>
#include <cstddef>
#include <algorithm>

namespace ft {
	template <class T, class Alloc = std::allocator<T> > class list {
	private:
		struct Elem
		{
			T			value;
			Elem		*next;
			Elem		*prev;
			Elem() : value(T()), next(NULL), prev(NULL) {}
		};

	public:
		typedef	T												value_type;
		typedef	Alloc											allocator_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef	typename allocator_type::pointer				pointer;
		typedef	typename allocator_type::const_pointer			const_pointer;
		typedef	ListBidirectionalIterator<T, Elem>				iterator;
		typedef	ListBidirectionalIterator<const T, const Elem>	const_iterator;
		typedef	ReverseIterator<iterator>						reverse_iterator;
		typedef	ReverseIterator<const_iterator>					const_reverse_iterator;
		typedef	ptrdiff_t										difference_type;
		typedef	size_t											size_type;
		
		explicit list (const allocator_type& alloc = allocator_type()) :
			_node(NULL), _size(0), _allocator(alloc) {
			_node = alloc_elem();
		}

		explicit list (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) :
				_node(NULL), _size(0), _allocator(alloc) {
			_node = alloc_elem();
			_size = n;
			for (size_type i = 0; i < n; ++i) {
				put_elem_before(_node, val);
			}
		}

		template <class InputIterator>
			list (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(), typename enable_if
				< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0) :
				_node(NULL), _size(0), _allocator(alloc) {
			size_type	dist = (size_type)std::distance(first, last);
			_node = alloc_elem();
			_size = dist;
			for (size_type i = 0; i < dist; ++i) {
				put_elem_before(_node, *(first++));
			}
		}

		list (const list &obj) :
		_node(NULL), _size(obj._size), _allocator(obj._allocator){
			Elem	*tmp_elem = obj._node->next;
			_node = alloc_elem();
			for (size_type i = 0; i < obj._size; ++i) {
				put_elem_before(_node, tmp_elem->value);
				tmp_elem = tmp_elem->next;
			}
		}

		~list() {
			Elem	*tmp_elem = _node->prev;

			for (size_type i = 0; i < _size; ++i) {
				Elem	*prev;
				prev = tmp_elem->prev;
				destroy_elem(tmp_elem);
				tmp_elem = prev;
			}
			_elem_allocator.destroy(_node);
			deallocate_elem(_node);
		}

		list&	operator=(const list &x) {
			if (this == &x)
				return (*this);
			this->~list();
			Elem	*tmp_elem = x._node;
			_node = alloc_elem();
			for (size_type i = 0; i < x._size; ++i) {
				put_elem_before(_node, tmp_elem->value);
				tmp_elem = tmp_elem->next;
			}
			_size = x._size;
			_allocator = x._allocator;
			return (*this);
		}
		iterator	begin() {
			return (iterator(_node->next));
		}
		
		const_iterator	begin() const {
			return (const_iterator(_node->next));
		}

		iterator	end() {
			return (iterator(_node));
		}

		const_iterator	end() const {
			return (const_iterator(_node));
		}

		reverse_iterator	rbegin() {
			if (_size == 0)
				return (reverse_iterator(this->end()));
			return (reverse_iterator(--this->end()));
		}

		const_reverse_iterator	rbegin() const {
			if (_size == 0)
				return (const_reverse_iterator(this->end()));
			return (const_reverse_iterator(--this->end()));
		}

		reverse_iterator	rend() {
			if (_size == 0)
				return (reverse_iterator(this->begin()));
			return (reverse_iterator(--this->begin()));
		}

		const_reverse_iterator	rend() const {
			if (_size == 0)
				return (const_reverse_iterator(this->begin()));
			return (const_reverse_iterator(--this->begin()));
		}

		bool	empty() const {
			return (_size == 0);
		}

		size_type	size() const {
			return (_size);
		}

		size_type	max_size() const {
			return (_allocator.max_size());
		}

		reference	front() {
			return (_node->next->value);
		}

		const_reference	front() const {
			return (_node->next->value);
		}

		reference	back() {
			return (_node->prev->value);
		}

		const_reference	back() const {
			return (_node->prev->value);
		}
		
		template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
			list	tmp_list(first, last);
			this->swap(tmp_list);
		}

		void assign (size_type n, const value_type& val) {
			list	tmp_list(n, val);
			this->swap(tmp_list);
		}

		void	push_front(const value_type &val) {
			put_elem_before(_node->next, val);
			_size++;
		}

		void	pop_front() {
			destroy_elem(_node->next);
			_size--;
		}

		void	push_back(const value_type &val) {
			put_elem_before(_node, val);
			_size++;
		}

		void	pop_back() {
			destroy_elem(_node->prev);
			_size--;
		}

		iterator insert (iterator position, const value_type& val) {
			put_elem_before(position.get_pointer(), val);
			_size++;
			return (--position);
		}

		void insert (iterator position, size_type n, const value_type& val) {
			for (size_type i = 0; i < n; ++i) {
				put_elem_before(position.get_pointer(), val);
			}
			_size += n;
		}

		template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename enable_if
				< !std::numeric_limits<InputIterator>::is_specialized >::type* = 0) {
			size_type	dist = std::distance(first, last);
			
			for (size_type i = 0; i < dist; ++i) {
				put_elem_before(position.get_pointer(), *first);
				first++;
			}
			_size += dist;
		}

		iterator	erase(iterator position) {
			iterator	res = iterator(position.get_pointer()->next);

			destroy_elem(position.get_pointer());
			_size--;
			return (res);
		}

		iterator erase (iterator first, iterator last) {
			size_type	dist = std::distance(first, last);
			if (dist > _size)
				return (first);

			for (size_type i = 0; i < dist; ++i) {
				erase(first++);
			}
			return (last);
		}

		void	swap(list	&x) {
			ft::swap(_node, x._node);
			ft::swap(_size, x._size);
			ft::swap(_allocator, x._allocator);
			ft::swap(_elem_allocator, x._elem_allocator);
		}

		void	resize(size_type n, value_type val = value_type()) {
			if (_size > n) {
				for (;_size > n; _size--) {
					destroy_elem(_node->prev);
				}
				return ;
			}
			if (_size < n) {
				for (; _size < n; _size++)
					put_elem_before(_node, val);
			}
		}

		void	clear() {
			this->erase(this->begin(), this->end());
		}

		void	splice(iterator position, list &x) {
			Elem	*getterStart = position.get_pointer()->prev;
			Elem	*getterEnd = position.get_pointer();
			Elem	*transferedStart = x.begin().get_pointer();
			Elem	*transferedEnd = x.end().get_pointer()->prev;
			Elem	*transferedLastElem = x.end().get_pointer();

			getterStart->next = transferedStart;
			transferedStart->prev = getterStart;
			getterEnd->prev = transferedEnd;
			transferedEnd->next = getterEnd;
			transferedLastElem->next = transferedLastElem;
			transferedLastElem->prev = transferedLastElem;
			_size += x._size;
			x._size = 0;
		}

		void splice (iterator position, list& x, iterator i) {
			Elem	*getterStart = position.get_pointer()->prev;
			Elem	*getterEnd = position.get_pointer();
			Elem	*transferedElem = i.get_pointer();

			transferedElem->prev->next = transferedElem->next;
			transferedElem->next->prev = transferedElem->prev;
			getterStart->next = transferedElem;
			transferedElem->prev = getterStart;
			getterEnd->prev = transferedElem;
			transferedElem->next = getterEnd;
			_size++;
			x._size--;
		}

		void splice (iterator position, list& x, iterator first, iterator last) {
			size_type	dist = std::distance(first, last);
			if (dist == 0)
				return ;
			Elem	*getterStart = position.get_pointer()->prev;
			Elem	*getterEnd = position.get_pointer();
			Elem	*transferedStart = first.get_pointer();
			Elem	*transferedEnd = last.get_pointer()->prev;
			Elem	*transferedLastElem = last.get_pointer();

			transferedLastElem->prev = transferedStart->prev;
			transferedStart->prev->next = transferedLastElem;
			getterStart->next = transferedStart;
			transferedStart->prev = getterStart;
			getterEnd->prev = transferedEnd;
			transferedEnd->next = getterEnd;
			_size += dist;
			x._size -= dist;
		}

		void remove (const value_type& val) {
			Elem		*cur_node = _node->next;
			Elem		*next_node;
			size_type	count = 0;

			for (size_type i = 0; i < _size; ++i) {
				next_node = cur_node->next;
				if (cur_node->value == val) {
					destroy_elem(cur_node);
					count++;
				}
				cur_node = next_node;
			}
			_size -= count;
		}

		template <class Predicate>
		void remove_if (Predicate pred) {
			iterator	cur_node = this->begin();
			iterator	next_node;

			while (cur_node != this->end()) {
				next_node = cur_node;
				next_node++;
				if (pred(*cur_node)) {
					destroy_elem(cur_node.get_pointer());
					_size--;
				}
				cur_node = next_node;
			}
		}

		void	unique() {
			iterator	cur_node = ++this->begin();
			iterator	next_node;
			iterator	prev_node = this->begin();

			while (cur_node != this->end()) {
				next_node = cur_node;
				next_node++;
				if (*cur_node == *prev_node) {
					destroy_elem(cur_node.get_pointer());
					_size--;
				}
				else
					prev_node = cur_node;
				cur_node = next_node;
			}
		}

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred) {
			iterator	cur_node = ++this->begin();
			iterator	next_node;
			iterator	prev_node = this->begin();

			while (cur_node != this->end()) {
				next_node = cur_node;
				next_node++;
				if (binary_pred(*cur_node, *prev_node)) {
					destroy_elem(cur_node.get_pointer());
					_size--;
				}
				else
					prev_node = cur_node;
				cur_node = next_node;
			}
		}

		void	merge(list &x) {
			if (&x == this || x.size() == 0)
				return ;
			iterator	cur_node = this->begin();
			iterator	x_cur_node = x.begin();

			while (cur_node != this->end()) {
				iterator	x_end_node = x_cur_node;
				while (x_end_node != x.end()
					&& *x_end_node < *cur_node) {
					++x_end_node;
				}
				if (x_end_node == x_cur_node)
					cur_node++;
				else {
					splice(cur_node, x, x_cur_node, x_end_node);
					x_cur_node = x_end_node;
				}
			}
			if (x._size != 0)
				splice(cur_node, x);
		}

		template <class Compare>
		void merge (list& x, Compare comp) {
			if (&x == this || x.size() == 0)
				return ;
			iterator	cur_node = this->begin();
			iterator	x_cur_node = x.begin();

			while (cur_node != this->end()) {
				iterator	x_end_node = x_cur_node;
				while (x_end_node != x.end()
					&& comp(*x_end_node, *cur_node)) {
					++x_end_node;
				}
				if (x_end_node == x_cur_node)
					cur_node++;
				else {
					splice(cur_node, x, x_cur_node, x_end_node);
					x_cur_node = x_end_node;
				}
			}
			if (x._size != 0)
				splice(cur_node, x);
		}

		void	sort() {
			iterator	endList = --this->end();
			for (iterator cur = this->begin(); cur != endList; ++cur) {
				iterator	next = cur;
				++next;
				for (; next != this->end(); ++next) {
					if (*next < *cur)
						ft::swap(*next, *cur);
				}
			}
		}
		
		template <class Compare>
		void sort (Compare comp) {
			iterator	endList = --this->end();
			for (iterator cur = this->begin(); cur != endList; ++cur) {
				iterator	next = cur;
				++next;
				for (; next != this->end(); ++next) {
					if (comp(*next, *cur))
						ft::swap(*next, *cur);
				}
			}
		}

		void	reverse() {
			Elem	*start = _node->next;
			Elem	*end = _node->prev;

			for (size_type i = 0; i < _size / 2; ++i) {
				Elem	*startNext = start->next;
				Elem	*endPrev = end->prev;
				swap_node(start, end);
				start = startNext;
				end = endPrev;
				
			}
		}
		
		allocator_type	get_allocator() const {
			return (_allocator);
		}
	
	private:
		Elem					*_node;
		size_type				_size;
		allocator_type			_allocator;
		std::allocator<Elem>	_elem_allocator;

		Elem	*alloc_elem() {
			Elem	*elem;

			elem = _elem_allocator.allocate(1);
			_elem_allocator.construct(elem, Elem());
			elem->next = elem;
			elem->prev = elem;
			return (elem);
		}

		Elem	*construct_elem(const value_type &val) {
			Elem	*elem = alloc_elem();

			_allocator.destroy(&elem->value);
			_allocator.construct(&elem->value, val);
			return (elem);
		}

		void	deallocate_elem(Elem *elem) {
			elem->prev->next = elem->next;
			elem->next->prev = elem->prev;
			_elem_allocator.deallocate(elem, 1);
		}

		void	destroy_elem(Elem *elem) {
			_allocator.destroy(&elem->value);
			deallocate_elem(elem);
		}

		void	put_elem_before(Elem *end_elem, const value_type &val) {
			Elem	*new_elem = construct_elem(val);

			new_elem->next = end_elem;
			new_elem->prev = end_elem->prev;
			end_elem->prev->next = new_elem;
			end_elem->prev = new_elem;
		}

		bool	elems_are_neighbours(Elem *A, Elem *B) {
			return ((A->next == B && B->prev == A) ||
					(A->prev == B && A->next == B));
		}

		void	swap_node(Elem *lhs, Elem *rhs) {
			Elem	*outterElems[4];

			outterElems[0] = lhs->prev;
			outterElems[1] = rhs->prev;
			outterElems[2] = lhs->next;
			outterElems[3] = rhs->next;
			if (elems_are_neighbours(lhs, rhs)) {
				lhs->next = outterElems[3];
				lhs->prev = outterElems[2];
				rhs->next = outterElems[1];
				rhs->prev = outterElems[0];
			}
			else {
				lhs->next = outterElems[3];
				rhs->next = outterElems[2];
				lhs->prev = outterElems[1];
				rhs->prev = outterElems[0];
			}
			lhs->prev->next = lhs;
			lhs->next->prev = lhs;
			rhs->prev->next = rhs;
			rhs->next->prev = rhs;
		}
	};
	template <class T, class Alloc>
	bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::list<T, Alloc>::const_iterator	lit = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator	rit = rhs.begin();
		while (lit != lhs.end()) {
			if (*lit != *rit)
				return (false);
			++lit;
			++rit;
		}
		return (true);
	}
	
	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
											 rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (lhs < rhs || lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}
	template <class T, class Alloc>
	bool operator> (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif
