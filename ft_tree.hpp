/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:23:43 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/19 13:55:55 by fignigno         ###   ########.fr       */
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
	void	rotateLeft(Node<value_type> *x, Node<value_type> **root) {
		Node<value_type> *y = x->right;

		x->right = y->left;
		if (y->left != NULL) y->left->parent = x;
		if (y != NULL) y->parent = x->parent;
		if (x->parent) {
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		} else {
			*root = y;
		}
		y->left = x;
		if (x != NULL) x->parent = y;
	}

	template <class value_type>
	void rotateRight(Node<value_type> *x, Node<value_type> **root) {
		Node<value_type> *y = x->left;

		x->left = y->right;
		if (y->right != NULL)
			y->right->parent = x;
		if (y != NULL)
			y->parent = x->parent;
		if (x->parent) {
			if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
		} else {
			*root = y;
		}
		y->right = x;
		if (x != NULL)
			x->parent = y;
	}

	template <class value_type>
	void insertFixup(Node<value_type> *x, Node<value_type> **root) {

   /*************************************
    *  maintain Red-Black tree balance  *
    *  after inserting node x           *
    *************************************/

    /* check Red-Black properties */
	while (x != *root && x->parent->color == RED) {
		/* we have a violation */
		if (x->parent == x->parent->parent->left) {
			Node<value_type> *y = x->parent->parent->right;
			if (y != NULL && y->color == RED) {
				/* uncle is RED */
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			} else {

				/* uncle is BLACK */
				if (x == x->parent->right) {
					/* make x a left child */
					x = x->parent;
					rotateLeft(x, root);
				}

				/* recolor and rotate */
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rotateRight(x->parent->parent, root);
			}
		} else {

			/* mirror image of above code */
			Node<value_type> *y = x->parent->parent->left;
			if (y != NULL && y->color == RED) {

				/* uncle is RED */
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			} else {

				/* uncle is BLACK */
				if (x == x->parent->left) {
					x = x->parent;
					rotateRight(x, root);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rotateLeft(x->parent->parent, root);
			}
		}
	}
	(*root)->color = BLACK;
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
		// if (n->parent != NULL) {
			if (n == n->parent->left) {
				n->parent->left = child;
			} else {
				n->parent->right = child;
			// }
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
