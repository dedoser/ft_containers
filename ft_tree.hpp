/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:23:43 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/19 00:17:21 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_HPP
#define FT_TREE_HPP

#include "ft_utils.hpp"

namespace ft {
	typedef enum { BLACK, RED } nodeColor;

	template <class value_type>
	struct Node {
		value_type	value;
		Node		*left;
		Node		*right;
		Node		*parent;
		nodeColor	color;
	};

	template <class value_type>
	Node<value_type>	*grandparent(Node<value_type> *node) {
		if ((node != NULL) && (node->parent != NULL))
			return (node->parent->parent);
		return (NULL);
	}

	template<class value_type>
	Node<value_type>	*uncle(Node<value_type> *node) {
		Node<value_type>	*g = grandparent(node);

		if (g == NULL)
			return (NULL);
		if (node->parent == g->left)
			return (g->right);
		return (g->left);
	}

	template <class value_type>
	void	rotate_left(Node<value_type> *n) {
		Node<value_type>	*pivot = n->right;

		pivot->parent = n->parent;
		if (n->parent != NULL) {
			if (n->parent->left == n)
				n->parent->left = pivot;
			else
				n->parent->right = pivot;
		}
		n->right = pivot->left;
		if (pivot->left != NULL)
			pivot->left->parent = n;
		n->parent = pivot;
		pivot->left = n;
	}

	template <class value_type>
	void	rotate_right(Node<value_type> *n) {
		Node<value_type>	*pivot = n->left;

		pivot->parent = n->parent;
		if (n->parent != NULL) {
			if (n->parent->left == n)
				n->parent->left = pivot;
			else
				n->parent->right = pivot;
		}
		n->left = pivot->right;
		if (pivot->right != NULL)
			pivot->right->parent = n;
		n->parent = pivot;
		pivot->right = n;
	}

	template <class value_type>
	void	insert_case1(Node<value_type> *n) {
		if (n->parent == NULL)
			n->color = BLACK;
		else
			insert_case2(n);
	}

	template <class value_type>
	void	insert_case2(Node<value_type> *n) {
		if (n->parent->color == BLACK)
			return; /* Tree is still valid */
		else
			insert_case3(n);
	}

	template <class value_type>
	void	insert_case3(Node<value_type> *n) {
		Node<value_type> *u = uncle(n), *g;

		if ((u != NULL) && (u->color == RED)) {
			n->parent->color = BLACK;
			u->color = BLACK;
			g = grandparent(n);
			g->color = RED;
			insert_case1(g);
		} else {
			insert_case4(n);
		}
	}

	template <class value_type>
	void	insert_case4(Node<value_type> *n) {
		Node<value_type> *g = grandparent(n);

		if ((n == n->parent->right) && (n->parent == g->left)) {
			rotate_left(n->parent);
			n = n->left;
		} else if ((n == n->parent->left) && (n->parent == g->right)) {
			rotate_right(n->parent);
			n = n->right;
		}
		insert_case5(n);
	}

	template <class value_type>
	void	insert_case5(Node<value_type> *n) {
		Node<value_type> *g = grandparent(n);

		n->parent->color = BLACK;
		g->color = RED;
		if ((n == n->parent->left) && (n->parent == g->left)) {
			rotate_right(g);
		} else {
			rotate_left(g);
		}
	}

	template <class value_type>
	Node<value_type>	*sibling(Node<value_type> *n) {
		if (n == n->parent->left)
			return n->parent->right;
		else
			return n->parent->left;
	}

	template <class value_type>
	void 	replace_node(Node<value_type> *n, Node<value_type> *child) {
		child->parent = n->parent;
		if (n->parent != NULL) {
			if (n == n->parent->left) {
				n->parent->left = child;
			} else {
				n->parent->right = child;
			}
		}
	}

	template <class value_type>
	Node<value_type>	*delete_one_child(Node<value_type> *n) {
		Node<value_type> *child = n->right == NULL ? n->left : n->right;

		if (child == NULL)
			return (n);
		replace_node(n, child);
		if (n->color == BLACK) {
			if (child->color == RED)
				child->color = BLACK;
			else
				delete_case1(child);
		}
		return (n);
	}

	template <class value_type>
	void	delete_case1(Node<value_type> *n) {
		if (n->parent != NULL)
			delete_case2(n);
	}

	template <class value_type>
	void delete_case2(Node<value_type> *n) {
		Node<value_type> *s = sibling(n);

		if (s->color == RED) {
			n->parent->color = RED;
			s->color = BLACK;
			if (n == n->parent->left)
				rotate_left(n->parent);
			else
				rotate_right(n->parent);
		} 
		delete_case3(n);
	}

	template <class value_type>
	void delete_case3(Node<value_type> *n) {
		Node<value_type> *s = sibling(n);

		if ((n->parent->color == BLACK) &&
			(s->color == BLACK) &&
			(s->left->color == BLACK) &&
			(s->right->color == BLACK)) {
			s->color = RED;
			delete_case1(n->parent);
		} else
			delete_case4(n);
	}

	template <class value_type>
	void delete_case4(Node<value_type> *n) {
		Node<value_type> *s = sibling(n);

		if ((n->parent->color == RED) &&
			(s->color == BLACK) &&
			(s->left->color == BLACK) &&
			(s->right->color == BLACK)) {
			s->color = RED;
			n->parent->color = BLACK;
		} else
			delete_case5(n);
	}

	template <class value_type>
	void delete_case5(Node<value_type> *n) {
		Node<value_type> *s = sibling(n);

		if (s->color == BLACK) {
			if ((n == n->parent->left) &&
				(s->right->color == BLACK) &&
				(s->left->color == RED)) {
				s->color = RED;
				s->left->color = BLACK;
				rotate_right(s);
			} else if ((n == n->parent->right) &&
					(s->left->color == BLACK) &&
					(s->right->color == RED)) {
				s->color = RED;
				s->right->color = BLACK;
				rotate_left(s);
			}
		}
		delete_case6(n);
	}

	template <class value_type>
	void delete_case6(Node<value_type> *n) {
		Node<value_type> *s = sibling(n);

		s->color = n->parent->color;
		n->parent->color = BLACK;

		if (n == n->parent->left) {
			s->right->color = BLACK;
			rotate_left(n->parent);
		} else {
			s->left->color = BLACK;
			rotate_right(n->parent);
		}
	}

	template<class value_type>
	Node<value_type>	*find_root(Node<value_type> *n) {
		while (n->parent != NULL)
			n = n->parent;
		return (n);
	}

	template <class value_type>
	Node<value_type>	*find_max_for_delete(Node<value_type> *n) {
		if (n->left == NULL || n->right == NULL)
			return (n);
		n = n->left;
		while (n->right)
			n = n->right;
		return (n);
	}
}

#endif
