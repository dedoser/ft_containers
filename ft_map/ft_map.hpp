/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:43:27 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 15:57:04 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <functional>
#include <memory>
#include <utility>
#include "../ft_pair.hpp"
#include "ft_map_iterator.hpp"
#include "../ft_ReverseIterator.hpp"
#include "../ft_tree.hpp"

namespace ft {
	template <  class Key,                                     // map::key_type
				class T,                                       // map::mapped_type
				class Compare = std::less<Key>,                     // map::key_compare
				class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
	public:
		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	ft::pair<const key_type, mapped_type>			value_type;
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
			revNIL = create_NIL();
			init_NIL();
			_root = NIL;
			init_border_nodes();
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
			_size(0), _comp(comp), _allocator(alloc) {
			NIL = create_NIL();
			revNIL = create_NIL();
			_root = NIL;
			this->insert(first, last);
			init_border_nodes();
		}

		map(const map &x) :
		_size(x._size), _allocator(x._allocator), _comp(x._comp) {
			NIL = create_NIL();
			revNIL = create_NIL();
			init_NIL();
			_root = copy_tree(x._root, NIL);
			this->init_border_nodes();
		}

		~map() {
			init_NIL();
			delete_tree(_root);
			_node_allocator.deallocate(NIL, 1);
			_node_allocator.deallocate(revNIL, 1);
		}

		map	&operator=(const map &right) {
			if (this == &right)
				return (*this);
			this->~map();
			this->NIL = create_NIL();
			this->revNIL = create_NIL();
			init_NIL();
			if (right._size == 0)
				_root = NIL;
			else
				_root = copy_tree(right._root, NIL);
			init_border_nodes();
			_size = right._size;
			_allocator = right._allocator;
			return (*this);
		}

		iterator	begin() {
			// std::cout << _beg_node << '\n';
			return (iterator(_beg_node));
		}

		const_iterator	begin() const {
			return (const_iterator(_beg_node));
		}

		iterator		end() {
			// std::cout << _end_node << '\n';
			return (iterator(NIL));
		}

		const_iterator	end() const {
			return (const_iterator(NIL));
		}

		reverse_iterator	rbegin() {
			if (_end_node == NIL)
				return (reverse_iterator(_end_node));
			return (reverse_iterator(_end_node));
		}

		const_reverse_iterator	rbegin() const {
			if (_end_node == NIL)
				return (const_reverse_iterator(_end_node));
			return (const_reverse_iterator(_end_node));
		}

		reverse_iterator	rend() {
			if (_beg_node == NIL)
				return (reverse_iterator(NIL));
			return (reverse_iterator(--this->begin()));
		}

		const_reverse_iterator	rend() const {
			if (_beg_node == NIL)
				return (const_reverse_iterator(NIL));
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
				(*((this->insert(ft::make_pair(k, mapped_type()))).first)).second
			);
		}

		ft::pair<iterator, bool>	insert(const value_type &val) {
			node	*parent, *x;

			ft::pair<node *, node *>	is_in_map = find_node(val.first);
			if (!isNIL(is_in_map.first))
				return (ft::make_pair<iterator, bool>(is_in_map.first, false));
			x = create_node(val);
			if (isNIL(is_in_map.second))
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
			return (ft::pair<iterator, bool>(x, true));
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
			ft::pair<node *, node *>	res = find_node(k);
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
			ft::swap(revNIL, x.revNIL);
			swap_leafs(_root);
			swap_leafs(x._root);
			init_border_nodes();
			x.init_border_nodes();
			
		}

		void	clear() {
			this->erase(this->begin(), this->end());
		}

		key_compare		key_comp() const {
			return (_comp);
		}

		value_compare	value_comp() const {
			return (_comp);
		}

		iterator	find(const key_type &k) {
			ft::pair<node *, node *>	res = find_node(k);
			if (res.first == NIL)
				return (this->end());
			return (res.first);
		}

		const_iterator	find(const key_type &k) const {
			ft::pair<node *, node *>	res = find_node(k);
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
			iterator	it(_beg_node);

			while (it != this->end()) {
				if (_comp(it.get_pointer()->value.first, k))
					++it;
				else
					return (it);
			}
			return (this->end());
		}

		const_iterator	lower_bound (const key_type& k) const {
			const_iterator	it(_beg_node);

			while (it != this->end()) {
				if (_comp(it.get_pointer()->value.first, k))
					++it;
				else
					return (it);
			}
			return (this->end());
		}
		
		iterator	upper_bound(const key_type &k) {
			iterator	it(_beg_node);

			while (it != this->end()) {
				if (_comp(k, it.get_pointer()->value.first))
					return (it);
				else
					it++;
			}
			return (this->end());
		}

		const_iterator	upper_bound(const key_type &k) const {
			const_iterator	it(_beg_node);

			while (it != this->end()) {
				if (_comp(k, it.get_pointer()->value.first))
					return (it);
				else
					it++;
			}
			return (this->end());
		}

		ft::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const {
			if (this->lower_bound(k) == this->end() && this->upper_bound(k) == this->end())
				return (ft::make_pair<const_iterator, const_iterator>
					(this->begin(), this->begin()));
			return (ft::make_pair<const_iterator, const_iterator>
					(this->lower_bound(k), this->upper_bound(k)));
		}

		ft::pair<iterator,iterator>	equal_range (const key_type& k) {
			if (this->lower_bound(k) == this->end() && this->upper_bound(k) == this->end())
				return (ft::make_pair<iterator, iterator>
					(this->begin(), this->begin()));
			return (ft::make_pair<iterator, iterator>
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
		node					*revNIL;

		node	*create_NIL() {
			node	*res;

			res = _node_allocator.allocate(1);
			_allocator.construct(&res->value, value_type());
			res->left = res;
			res->right = res;
			res->parent = NULL;
			res->color = BLACK;
			res->revParent = NULL;
			return (res);
		}

		void	init_NIL() {
			NIL->left = NIL;
			NIL->right = NIL;
			revNIL->left = revNIL;
			revNIL->right = revNIL;
		}

		node	*create_node(const value_type &val) {
			node	*elem;

			elem = _node_allocator.allocate(1);
			_allocator.construct(&elem->value, val);
			elem->left = NIL;
			elem->right = NIL;
			elem->parent = NULL;
			elem->revParent = NULL;
			elem->color = RED;
			return (elem);
		}

		void	delete_node(node *n) {
			_allocator.destroy(&n->value);
			_node_allocator.deallocate(n, 1);
		}

		void	delete_tree(node *root) {
			if (isNIL(root))
				return ;
			node	*right = root->right;
			delete_tree(root->left);
			_allocator.destroy(&root->value);
			_node_allocator.deallocate(root, 1);
			delete_tree(right);
		}

		void	init_border_nodes() {
			init_NIL();
			_beg_node = _root;
			_end_node = _root;
			while (!isNIL(_beg_node->left))
				_beg_node = _beg_node->left;
			while (!isNIL(_end_node->right))
				_end_node = _end_node->right;
			NIL->parent = _end_node;
			revNIL->parent = _end_node;
			revNIL->revParent = _beg_node;
			_beg_node->left = revNIL;
			// std::cout << _beg_node->value.first << ' ' << _end_node->value.first << '\n';
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

		void	swap_leafs(node *root) {
			if (isNIL(root->left)) {
				root->left = NIL;
				return ;
			}
			swap_leafs(root->left);
			if (isNIL(root->right)) {
				root->right = NIL;
				return ;
			}
			swap_leafs(root->right);
		}

		ft::pair<node *, node *>	find_node(const key_type &key) const {
			node	*tmp = _root;
			node	*prev = NIL;

			while (!isNIL(tmp)) {
				prev = tmp;
				if (_comp(tmp->value.first, key))
					tmp = tmp->right;
				else if (_comp(key, tmp->value.first))
					tmp = tmp->left;
				else
					return (ft::make_pair(tmp, tmp));
			}
			return (ft::make_pair(tmp, prev));
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

			if (!z || isNIL(z))
				return (z);
			if (isNIL(z->left) || isNIL(z->right)) {
				y = z;
			} else {
				y = z->right;
				while (!isNIL(y->left))
					y = y->left;
			}
			if (!isNIL(y->left))
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
