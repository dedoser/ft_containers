/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:43:27 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/17 21:47:57 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <functional>
#include <memory>
#include <utility>
#include "ft_map_iterator.hpp"
#include "../ft_ReverseIterator.hpp"
// #include "../ft_tree.hpp"

namespace ft {
	template <  class Key,                                     // map::key_type
				class T,                                       // map::mapped_type
				class Compare = std::less<Key>,                     // map::key_compare
				class Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
	private:
		typedef enum { BLACK, RED } nodeColor;

		struct Node {
			value_type	value;
			Node		*left;
			Node		*right;
			Node		*parent;
			nodeColor	color;
		};
	public:
		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	std::pair<const key_type, mapped_type>			value_type;
		typedef	Compare											key_compare;
		typedef	Alloc											allocator_type;
		typedef	allocator_type::reference						reference;
		typedef	allocator_type::const_reference					const_reference;
		typedef	allocator_type::pointer							pointer;
		typedef	allocator_type::const_pointer					const_pointer;
		typedef	MapBidirectIterator<value_type, Node>			iterator;
		typedef	MapBidirectIterator<const value_type, Node>		const_iterator;
		typedef	ReverseIterator<iterator>						reverse_iterator;
		typedef	ReverseIterator<const_iterator>					const_reverse_iterator;
		typedef	ptrdiff_t										difference_type;
		typedef	size_t											size_type;
		class value_compare : public binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;
			value_compare(key_compare c);
			public:
			bool operator()(const value_type& x, const value_type& y) const {
				return (comp(x.first, y.first));
			}
		};

		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
		_root(0), _end_node(0), _beg_node(0), _size(0), _allocator(alloc), _comp(comp) {}

		iterator	begin() {
			return (iterator(_beg_node));
		}

		const_iterator	begin() const {
			return (const_iterator(_beg_node));
		}

		iterator		end() {
			return (iterator(_end_node));
		}

		const_iterator	end() const {
			return (const_iterator(_end_node));
		}

		reverse_iterator	rbegin() {
			if (_end_node == NULL)
				return (reverse_iterator(_end_node));
			return (reverse_iterator(--this->end()));
		}

		const_reverse_iterator	rbegin() const {
			if (_end_node == NULL)
				return (const_reverse_iterator(_end_node));
			return (const_reverse_iterator(--this->end()));
		}

		reverse_iterator	rend() {
			if (_beg_node == NULL)
				return (reverse_iterator(this->begin()));
			return (reverse_iterator(--this->begin()));
		}

		const_reverse_iterator	rend() const {
			if (_beg_node == NULL)
				return (const_reverse_iterator(this->begin()));
			return (const_reverse_iterator(--this->begin()));
		}

		bool	empty const {
			return (_size == 0);
		}

		size_type	size() const {
			return (_size);
		}

		size_type	max_size() const {
			return (_node_allocator.max_size());
		}

		pair<iterator, bool>	insert(const value_type &val) {
			
		}
	private:
		Node					*root;
		Node					*_end_node;
		Node					*_beg_node;
		size_type				_size;
		allocator_type			_allocator;
		std::allocator<Node>	_node_allocator;
		key_compare				_comp;

		Node	*create_node(const value_type &val) {
			Node	*elem;

			elem = _node_allocator.allocate(1);
			_allocator.construct(&elem->value, val);
			elem->left = NULL;
			elem->right = NULL;
			elem->parent = NULL;
			return (elem);
		}

		void	delete_node(Node *n) {
			_allocator.destroy(&elem->value);
			_node_allocator.deallocate(n);
		}

		
	};
}

#endif
