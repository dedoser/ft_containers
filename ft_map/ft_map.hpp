/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:43:27 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/24 20:41:43 by fignigno         ###   ########.fr       */
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
#include <iostream>

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
		_root(NULL), _end_node(0), _beg_node(0), _size(0), _allocator(alloc), _comp(comp) {
			NIL = create_NIL();
			_end_node = create_NIL();
			_beg_node = create_NIL();
			_root = NIL;
			init_border_nodes();
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
			_size(0), _comp(comp), _allocator(alloc) {
			NIL = create_NIL();
			_root = NIL;
			_end_node = create_NIL();
			_beg_node = create_NIL();
			init_border_nodes();
			this->insert(first, last);
		}

		map(const map &x) :
		_size(x._size), _allocator(x._allocator), _comp(x._comp) {
			NIL = create_NIL();
			_end_node = create_NIL();
			_beg_node = create_NIL();
			_root = copy_tree(x._root, this->NIL);
			this->init_border_nodes();
		}

		~map() {
			delete_tree(_root);
			_node_allocator.deallocate(NIL, 1);
			_node_allocator.deallocate(_end_node, 1);
			_node_allocator.deallocate(_beg_node, 1);
		}

		map	&operator=(const map &right) {
			if (this == &right)
				return (*this);
			this->~map();
			this->NIL = create_NIL();
			this->_end_node = create_NIL();
			this->_beg_node = create_NIL();
			_root = copy_tree(right._root, NIL);
			init_border_nodes();
			_size = right._size;
			_allocator = right._allocator;
			return (*this);
		}

		iterator	begin() {
			return (iterator(_beg_node->parent));
		}

		const_iterator	begin() const {
			return (const_iterator(_beg_node->parent));
		}

		iterator		end() {
			return (iterator(_end_node));
		}

		const_iterator	end() const {
			return (const_iterator(_end_node));
		}

		reverse_iterator	rbegin() {
			if (_root == NIL)
				return (reverse_iterator(_root));
			return (reverse_iterator(_end_node->parent));
		}

		const_reverse_iterator	rbegin() const {
			if (_root == NIL)
				return (const_reverse_iterator(_root));
			return (const_reverse_iterator(_end_node->parent));
		}

		reverse_iterator	rend() {
			if (_root == NIL)
				return (reverse_iterator(NIL));
			return (reverse_iterator(_beg_node));
		}

		const_reverse_iterator	rend() const {
			if (_root == NIL)
				return (const_reverse_iterator(NIL));
			return (const_reverse_iterator(_beg_node));
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
			node	*parent, *x;

			std::pair<node *, node *>	is_in_map = find_node(val.first);
			if (is_in_map.first != NIL)
				return (std::make_pair<iterator, bool>(is_in_map.first, false));
			x = create_node(val);
			if (is_in_map.second == NIL)
				parent = 0;
			else
				parent = is_in_map.second;
			x->parent = parent;
			if (parent)
				init_leaf(parent, x);
			else
				_root = x;
			balance_tree(x);
			_size++;
			return (std::pair<iterator, bool>(x, true));
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
			node	*del_elem = delete_one_child(position.get_pointer(), &_root);
			// _root = find_root(del_elem);
			if (del_elem && del_elem != NIL)
				delete_node(del_elem);
			_size--;
			init_border_nodes();
		}

		size_type	erase(const key_type &k) {
			std::pair<node *, node *>	res = find_node(k);
			if (res.first == NIL)
				return (0);
			erase(res.first);
			return (1);
		}

		void	erase(iterator first, iterator last) {
			while (first != last) {
				iterator	tmp = first;
				tmp++;
				erase(first);
				first = tmp;
			}
		}
		
		void	swap(map &x) {
			ft::swap(_root, x._root);
			ft::swap(_end_node, x._end_node);
			ft::swap(_beg_node, x._beg_node);
			ft::swap(_size, x._size);
			ft::swap(_allocator, x._allocator);
			ft::swap(_comp, x._comp);
			ft::swap(NIL, x.NIL);
		}

		void	clear() {
			this->erase(this->begin(), this->end());
		}

		key_compare		key_comp() const {
			return (_comp);
		}

		value_compare	value_comp() const {
			return (value_compare(_comp));
		}

		iterator	find(const key_type &k) {
			std::pair<node *, node *>	res = find_node(k);
			if (res.first == NIL)
				return (this->end());
			return (res.first);
		}

		const_iterator	find(const key_type &k) const {
			std::pair<node *, node *>	res = find_node(k);
			if (res.first == NIL)
				return (this->end());
			return (res.first);
		}

		size_type		count(const key_type &k) const {
			if (this->find(k) == this->end())
				return (0);
			return (1);
		}

		iterator	lower_bound (const key_type& k) {
			node	*tmp = _root;

			while (tmp != NIL) {
				if (_comp(tmp->value.first, k))
					tmp = tmp->right;
				else
					return (tmp);
			}
			return (this->end());
		}

		const_iterator	lower_bound (const key_type& k) const {
			node	*tmp = _root;

			while (tmp != NIL) {
				if (_comp(tmp->value.first, k))
					tmp = tmp->right;
				else
					return (tmp);
			}
			return (this->end());
		}
		
		iterator	upper_bound(const key_type &k) {
			node	*tmp = _root;

			while (tmp != NIL) {
				if (_comp(k, tmp->value.first))
					tmp = tmp->left;
				else
					return (tmp);
			}
			return (this->end());
		}

		const_iterator	upper_bound(const key_type &k) const {
			node	*tmp = _root;

			while (tmp != NIL) {
				if (_comp(k, tmp->value.first))
					tmp = tmp->left;
				else
					return (tmp);
			}
			return (this->end());
		}

		std::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const {
			return (std::make_pair<const_iterator, const_iterator>
					(this->lower_bound(k), this->upper_bound(k)));
		}

		std::pair<iterator,iterator>	equal_range (const key_type& k) {
			return (std::make_pair<iterator, iterator>
					(this->lower_bound(k), this->upper_bound(k)));
		}

		allocator_type	get_allocator() const {
			return (_allocator);
		}

	private:
		node					*_root;
		node					*_end_node;
		node					*_beg_node;
		size_type				_size;
		allocator_type			_allocator;
		std::allocator<node>	_node_allocator;
		key_compare				_comp;
		node					*NIL;

		node	*create_NIL() {
			node	*res;

			res = _node_allocator.allocate(1);
			res->left = res;
			res->right = res;
			res->parent = NULL;
			res->color = BLACK;
			return (res);
		}
		node	*create_node(const value_type &val) {
			node	*elem;

			elem = _node_allocator.allocate(1);
			_allocator.construct(&elem->value, val);
			elem->left = NIL;
			elem->right = NIL;
			elem->parent = NULL;
			elem->color = RED;
			return (elem);
		}

		void	delete_node(node *n) {
			_allocator.destroy(&n->value);
			_node_allocator.deallocate(n, 1);
		}

		void	delete_tree(node *root) {
			if (root == NIL)
				return ;
			node	*right = root->right;
			delete_tree(root->left);
			_allocator.destroy(&root->value);
			_node_allocator.deallocate(root, 1);
			delete_tree(right);
		}

		void	init_border_nodes() {
			node	*beg = _root, *end = _root;
			while (beg->left != NIL)
				beg = beg->left;
			while (end->right != NIL)
				end = end->right;
			_beg_node->parent = beg;
			beg->left = _beg_node;
			_end_node->parent = end;
			end->right = _end_node;
		}

		void	balance_tree(node *n) {
			insertFixup(n, &_root, NIL);
			init_border_nodes();
		}

		void	init_leaf(node *n, node *new_elem) {
			if (value_comp()(n->value, new_elem->value))
				n->right = new_elem;
			else
				n->left = new_elem;
		}

		std::pair<node *, node *>	find_node(const key_type &key) const {
			node	*tmp = _root;
			node	*prev = NIL;

			while (tmp != NIL) {
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

		node	*copy_tree(node *root, node *NIL) {
			if (root->left == root && root->right == root)
				return (NIL);
			node	*res = copy_node(root);
			res->left = copy_tree(root->left, NIL);
			if (res->left != NIL)
				res->left->parent = res;
			res->right = copy_tree(root->right, NIL);
			if (res->right != NIL)
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

		node	*delete_one_child(node *z, node **root) {
			node *x, *y;

			if (!z || z == NIL)
				return (z);
			if (z->left == NIL || z->right == NIL) {
				y = z;
			} else {
				y = z->right;
				while (y->left != NIL)
					y = y->left;
			}
			if (y->left != NIL)
				x = y->left;
			else
				x = y->right;
			x->parent = y->parent;
			if (y->parent)
				if (y == y->parent->left)
					y->parent->left = x;
				else
					y->parent->right = x;
			else
				*root = x;
			if (y != z)
				swap_pair(y, z);
			if (y->color == BLACK)
				deleteFixup(x, root, NIL);
			return (y);
		}
	};
}

#endif
