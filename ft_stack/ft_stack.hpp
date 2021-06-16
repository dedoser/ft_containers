/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:11:17 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/16 15:11:10 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include "../ft_list/ft_list.hpp"

namespace ft {
	template <class T, class Container = list<T> > class stack {
	public:
		typedef	T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;

	protected:
		container_type	c;

	public:
		explicit stack(const container_type &cntr = container_type()) : c(cntr) {}
		stack(const stack &x) : c(x.c) {}
		
		stack	&operator=(const stack &other) {
			if (this == &other)
				return (*this);
			this->~stack();
			c = other.c;
			return (*this);
		}

		~stack() {}

		bool	empty() const {
			return (c.empty());
		}

		size_type	size() const {
			return (c.size());
		}

		value_type			&top() {
			return (c.back());
		}

		const value_type	&top() const {
			return (c.back());
		}

		void	push(const value_type &val) {
			c.push_back(val);
		}

		void	pop() {
			c.pop_back();
		}
	};
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c == rhs.c);
	}
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c != rhs.c);
	}
	
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c < rhs.c);
	}
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c >= rhs.c);
	}
}

#endif
