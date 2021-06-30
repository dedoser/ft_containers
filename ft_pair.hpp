/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pair.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 00:38:42 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 16:14:38 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

namespace ft {
	template <class T1, class T2>
	struct pair {
		typedef	T1	first_type;
		typedef	T2	second_type;
		
		first_type	first;
		second_type	second;

		pair() : first(), second() {}

		template <class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		pair	*operator=(const pair &pr) {
			if (this == &pr)
				return (*this);
			first = pr.first;
			second = pr.second;
		}
		
	};

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y) {
		return (pair<T1, T2>(x, y));
	}
}

#endif
