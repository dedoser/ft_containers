/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:43:27 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/19 00:14:03 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <functional>
#include <memory>
#include <utility>
#include "ft_map_iterator.hpp"
#include "../ft_ReverseIterator.hpp"
#include "../ft_tree.hpp"

namespace ft {
	template <  class Key,                                     // map::key_type
				class T,                                       // map::mapped_type
				class Compare = std::less<Key>,                     // map::key_compare
				class Alloc = std::allocator<std::pair<const Key,T> > >
	class map {
	public:
		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	std::pair<const key_type, mapped_type>			value_type;
		typedef	Node<value_type>								node;
		typedef	Compare											key_compare;
		typedef	Alloc											allocator_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef	typename allocator_type::pointer				pointer;
		typedef	typename allocator_type::const_pointer			const_pointer;
		typedef	MapBidirectIterator<value_type, node>			iterator;
		typedef	MapBidirectIterator<const value_type, node>		const_iterator;
		typedef	ReverseIterator<iterator>						reverse_iterator;
		typedef	ReverseIterator<const_iterator>					const_reverse_iterator;
		typedef	ptrdiff_t										difference_type;
		typedef	size_t											size_type;
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}
		public:
			typedef	bool		result_type;
			typedef	value_type	first_argument_type;
			typedef	value_type	second_argument_type;
			bool operator()(const value_type& x, const value_type& y) const {
				return (comp(x.first, y.first));
			}
		};
	public:

		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
		_root(NULL), _end_node(0), _beg_node(0), _size(0), _allocator(alloc), _comp(comp) {}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) {
			this->insert(first, last);
		}

		map(const map &x) :
		_size(x._size), _allocator(x._allocator), _comp(x._comp) {
			_root = copy_tree(x._root);
			this->init_border_nodes();
		}

		~map() {
			// print_tree(_root);
		}

		iterator	begin() {
			return (iterator(_beg_node));
		}

		const_iterator	begin() const {
			return (const_iterator(_beg_node));
		}

		iterator		end() {
			return (iterator(_end_node + 1));
		}

		const_iterator	end() const {
			return (const_iterator(_end_node + 1));
		}

		reverse_iterator	rbegin() {
			if (_end_node == NULL)
				return (reverse_iterator(_end_node));
			return (reverse_iterator(_end_node));
		}

		const_reverse_iterator	rbegin() const {
			if (_end_node == NULL)
				return (const_reverse_iterator(_end_node));
			return (const_reverse_iterator(_end_node));
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

		bool	empty() const {
			return (_size == 0);
		}

		size_type	size() const {
			return (_size);
		}

		size_type	max_size() const {
			return (_node_allocator.max_size());
		}

		mapped_type	&operator[](const key_type &k) {
			return (
				(*((this->insert(std::make_pair(k, mapped_type()))).first)).second
			);
		}
		std::pair<iterator, bool>	insert(const value_type &val) {
			if (_size == 0) {
				_root = create_node(val);
				_size++;
				balance_tree(_root);
				return (std::make_pair<iterator, bool>(iterator(_root), true));
			}
			std::pair<node *, node *>	is_in_map = find(val.first);
			if (is_in_map.first != NULL)
				return (std::make_pair<iterator, bool>(
						iterator(is_in_map.first), true));
			node	*new_node = create_node(val);
			node	*prev = is_in_map.second;
			new_node->parent = prev;
			init_leaf(prev, new_node);
			balance_tree(new_node);
			_root = find_root(prev);
			init_border_nodes();
			_size++;
			return (std::make_pair<iterator, bool>(iterator(new_node), true));
		}

		iterator insert (iterator position, const value_type& val) {
			(void) (position);
			return (this->insert(val).first);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			while (first != last) {
				this->insert(*first);
				first++;
			}
		}

		void	erase(iterator position) {
			replace_node_for_erase(position.get_pointer());
			node	*del_elem = delete_one_child(position.get_pointer());
			_root = find_root(del_elem);
			delete_node(del_elem);
			init_border_nodes();
		}

		value_compare	value_comp() const {
			return (value_compare(key_compare()));
		}
	private:
		node					*_root;
		node					*_end_node;
		node					*_beg_node;
		size_type				_size;
		allocator_type			_allocator;
		std::allocator<node>	_node_allocator;
		key_compare				_comp;

		node	*create_node(const value_type &val) {
			node	*elem;

			elem = _node_allocator.allocate(1);
			_allocator.construct(&elem->value, val);
			elem->left = NULL;
			elem->right = NULL;
			elem->parent = NULL;
			elem->color = RED;
			return (elem);
		}

		void	delete_node(node *n) {
			if (n->parent != NULL) {
				if (n->parent->left == n)
					n->parent->left = NULL;
				else
					n->parent->right = NULL;
			}
			_allocator.destroy(&n->value);
			_node_allocator.deallocate(n, 1);
		}

		void	init_border_nodes() {
			_beg_node = _root;
			_end_node = _root;
			while (_beg_node->left)
				_beg_node = _beg_node->left;
			while (_end_node->right)
				_end_node = _end_node->right;
		}

		void	balance_tree(node *n) {
			insert_case1(n);
			init_border_nodes();
		}

		void	init_leaf(node *n, node *new_elem) {
			if (value_comp()(n->value, new_elem->value))
				n->right = new_elem;
			else
				n->left = new_elem;
		}

		std::pair<node *, node *>	find(const key_type &key) {
			node	*tmp = _root;
			node	*prev;

			while (tmp) {
				prev = tmp;
				if (_comp(tmp->value.first, key))
					tmp = tmp->right;
				else if (_comp(key, tmp->value.first))
					tmp = tmp->left;
				else
					return (std::make_pair(tmp, tmp));
			}
			return (std::make_pair(tmp, prev));
		}

		node	*copy_node(node *n) {
			node	*new_elem = create_node(n->value);

			new_elem->color = n->color;
			return (new_elem);
		}

		node	*copy_tree(node *root) {
			if (root == NULL)
				return (NULL);
			node	*res;

			res = copy_node(root);
			res->left = copy_tree(root->left);
			if (res->left)
				res->left->parent = res;
			res->right = copy_tree(root->right);
			if (res->right)
				res->right->parent = res;
			return (res);
		}

		void	swap_pair(node *lhs, node *rhs) {
			value_type	tmpl(lhs->value);
			value_type	tmpr(rhs->value);

			_allocator.destroy(&lhs->value);
			_allocator.destroy(&rhs->value);
			_allocator.construct(&rhs->value, tmpl);
			_allocator.construct(&lhs->value, tmpr);
		}

		void	replace_node_for_erase(node *n) {
			node	*rep = find_max_for_delete(n);
			swap_pair(n, rep);
		}
	};
}

#endif
