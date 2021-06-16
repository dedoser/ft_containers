/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:31:25 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/09 22:08:22 by fignigno         ###   ########.fr       */
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
}


#endif
