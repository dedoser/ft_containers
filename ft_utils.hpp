/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:31:25 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 01:25:21 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_HPP
#define FT_UTILS_HPP

namespace ft
{
	template < bool B, class T = void >
	struct enable_if {};

	template < class T >
	struct enable_if <true, T> {
		typedef T type;
	};

	template<class T>
	void swap(T &a, T &b) {
		T	tmp = a;

		a = b;
		b = tmp;
	}

	template <class InputIterator>
	bool	lexicographical_compare(InputIterator first1, InputIterator last1,
								   InputIterator first2, InputIterator last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator>
	bool equal ( InputIterator first1, InputIterator last1, InputIterator first2 )
	{
	while (first1!=last1) {
		if (!(*first1 == *first2))
			return (false);
		++first1;
		++first2;
	}
	return true;
}
}


#endif
