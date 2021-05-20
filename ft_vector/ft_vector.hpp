/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:10:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/05/20 12:55:46 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include "ft_vector_random_iterator.hpp"
#include "../ft_reverse_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> > class vector
	{
	public:
		typedef	T											value_type;
		typedef	Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef	typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef	VectorRandomAccessIterator<T>				iterator;
		typedef	VectorRandomAccessIterator<const T>			const_iterator;
		typedef	reverse_iterator<iterator>					reverse_iterator;
		typedef	reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef	ptrdiff_t									difference_type;
		typedef	size_t										size_type;

		
	};
}


#endif
