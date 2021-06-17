/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:23:43 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/17 21:50:16 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_HPP
#define FT_TREE_HPP

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

	void	rotate_left(Node *n) {
		Node	*pivot = n->right;

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

	void	rotate_right(Node *n) {
		Node	*pivot = n->left;

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

	void	insert_case1(Node *n) {
		if (n->parent == NULL)
			n->color = BLACK;
		else
			insert_case2(n);
	}

	void	insert_case2(Node *n) {
		if (n->parent->color == BLACK)
			return; /* Tree is still valid */
		else
			insert_case3(n);
	}

	void	insert_case3(Node *n) {
		Node *u = uncle(n), *g;

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

	void	insert_case4(Node *n) {
		Node *g = grandparent(n);

		if ((n == n->parent->right) && (n->parent == g->left)) {
			rotate_left(n->parent);
			n = n->left;
		} else if ((n == n->parent->left) && (n->parent == g->right)) {
			rotate_right(n->parent);
			n = n->right;
		}
		insert_case5(n);
	}

	void	insert_case5(Node *n) {
		Node *g = grandparent(n);

		n->parent->color = BLACK;
		g->color = RED;
		if ((n == n->parent->left) && (n->parent == g->left)) {
			rotate_right(g);
		} else {
			rotate_left(g);
		}
	}

	void 	replace_node(Node* n, Node* child) {
		child->parent = n->parent;
		if (n == n->parent->left) {
			n->parent->left = child;
		} else {
			n->parent->right = child;
		}
	}

	void	delete_one_child(Node *n) {
		Node *child = n->right == NULL ? n->left : n->right;

		replace_node(n, child);
		if (n->color == BLACK) {
			if (child->color == RED)
				child->color = BLACK;
			else
				delete_case1(child);
		}
		delete_node(n);
	}

	void	delete_case1(Node *n) {
		if (n->parent != NULL)
			delete_case2(n);
	}

	void delete_case2(Node *n) {
		Node *s = sibling(n);

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

	void delete_case3(Node *n) {
		Node *s = sibling(n);

		if ((n->parent->color == BLACK) &&
			(s->color == BLACK) &&
			(s->left->color == BLACK) &&
			(s->right->color == BLACK)) {
			s->color = RED;
			delete_case1(n->parent);
		} else
			delete_case4(n);
	}

	void delete_case4(Node *n) {
		Node *s = sibling(n);

		if ((n->parent->color == RED) &&
			(s->color == BLACK) &&
			(s->left->color == BLACK) &&
			(s->right->color == BLACK)) {
			s->color = RED;
			n->parent->color = BLACK;
		} else
			delete_case5(n);
	}

	void delete_case5(Node *n) {
		Node *s = sibling(n);

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

	void delete_case6(Node *n) {
		Node *s = sibling(n);

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
}

#endif
