/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 01:26:08 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 01:30:58 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SET_HPP
#define FT_SET_HPP

#include <functional>
#include <memory>
#include "../ft_tree.hpp"
#include "../ft_utils.hpp"

namespace ft {
	template <class T,
			  class Compare = std::less<T>,
			  class Alloc = std::allocator<T> >
	class set {
		typedef	T					key_type;
		typedef	T					value_type;
		typedef	Compare				key_compare;
		typedef	Compare				value_compare;
		typedef	Alloc				allocator_type;
		typedef	typename allocator_type::reference				reference;
		typedef	typename allocator_type::const_reference		const_reference;
		typedef	typename allocator_type::pointer				pointer;
		typedef	typename allocator_type::const_pointer			const_pointer;
	}
}

#endif
