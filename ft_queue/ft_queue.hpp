/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:07:49 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/16 15:18:55 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_QUEUE_HPP
#define FT_QUEUE_HPP

#include "../ft_list/ft_list.hpp"

namespace ft {
	template <class T, class Container = list<T> > class queue {
	public:
		typedef	T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;
	protected:
		container_type	c;
	public:
		explicit queue (const container_type &ctnr = container_type()) : c(ctnr) {}

		queue (const queue &x) : c(x.c) {}

		queue	&operator=(const queue &right) {
			if (this == &right)
				return (*this);
			c = right.c;
			return (*this);
		}

		~queue() {}

		bool	empty() const {
			return (c.empty());
		}

		size_type	size() const {
			return (c.size());
		}

		value_type	&front() {
			return (c.front());
		}

		const value_type	&front() const {
			return (c.front());
		}

		value_type	&back() {
			return (c.back());
		}

		const value_type	&back() const {
			return (c.back());
		}

		void	push(const value_type &val) {
			c.push_back(val);
		}

		void	pop() {
			c.pop_front();
		}
	};
	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.c != rhs.c);
	}
	template <class T, class Container>
	bool operator< (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.c < rhs.c);
	}
	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.c <= rhs.c);
	}
	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.c > rhs.c);
	}
	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.c >= rhs.c);
	}
}

#endif
