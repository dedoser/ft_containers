/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:23:43 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/25 18:25:20 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_HPP
#define FT_TREE_HPP

#include "ft_utils.hpp"

namespace ft {
	typedef enum { BLACK, RED} nodeColor;

	template <class value_type>
	struct Node {
		value_type	value;
		Node		*left;
		Node		*right;
		Node		*parent;
		Node		*revParent;
		nodeColor	color;
	};

	template <class value_type>
	bool	isNIL(Node<value_type> *node) {
		return (node->left == node || node->right == node);
	}

	template <class value_type>
	void	rotateLeft(Node<value_type> *x, Node<value_type> **root,
					   Node<value_type> *NIL) {
		Node<value_type> *y = x->right;

		x->right = y->left;
		if (!isNIL(y->left))
			y->left->parent = x;
		if (!isNIL(y))
			y->parent = x->parent;
		if (x->parent) {
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		} else {
			*root = y;
		}
		y->left = x;
		if (!isNIL(x))
			x->parent = y;
	}

	template <class value_type>
	void rotateRight(Node<value_type> *x, Node<value_type> **root,
					 Node<value_type> *NIL) {
		Node<value_type> *y = x->left;

		x->left = y->right;
		if (!isNIL(y->right))
			y->right->parent = x;
		if (!isNIL(y))
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
		if (!isNIL(x))
			x->parent = y;
	}

	template <class value_type>
	void insertFixup(Node<value_type> *x, Node<value_type> **root,
					 Node<value_type> *NIL) {
		while (x != *root && x->parent->color == RED) {
			/* we have a violation */
			if (x->parent == x->parent->parent->left) {
				Node<value_type> *y = x->parent->parent->right;
				if (y->color == RED) {
					/* uncle is RED */
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				} else {
					if (x == x->parent->right) {
						/* make x a left child */
						x = x->parent;
						rotateLeft(x, root, NIL);
					}

					/* recolor and rotate */
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					rotateRight(x->parent->parent, root, NIL);
				}
			} else {

				/* mirror image of above code */
				Node<value_type> *y = x->parent->parent->left;
				if (y->color == RED) {

					/* uncle is RED */
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				} else {

					/* uncle is BLACK */
					if (x == x->parent->left) {
						x = x->parent;
						rotateRight(x, root, NIL);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					rotateLeft(x->parent->parent, root, NIL);
				}
			}
		}
		(*root)->color = BLACK;
	}

	template<class value_type>
	void deleteFixup(Node<value_type> *x, Node<value_type> **root,
					 Node<value_type> *NIL) {
		while (x != *root && x->color == BLACK) {
			if (x == x->parent->left) {
				Node<value_type> *w = x->parent->right;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rotateLeft (x->parent, root, NIL);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						rotateRight (w, root, NIL);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					rotateLeft (x->parent, root, NIL);
					x = *root;
				}
			} else {
				Node<value_type> *w = x->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rotateRight (x->parent, root, NIL);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						rotateLeft (w, root, NIL);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rotateRight (x->parent, root, NIL);
					x = *root;
				}
			}
		}
		x->color = BLACK;
	}
}

#endif
