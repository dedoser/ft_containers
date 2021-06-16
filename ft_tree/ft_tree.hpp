/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:23:43 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/16 19:31:42 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TREE_HPP
#define FT_TREE_HPP

#include <memory>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <limits>
#include <cstddef>
#include <functional>

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>
			class Alloc = std::allocator<pair<const Key, T> >
	class tree {
	public:
		typedef	Key										key_type;
		typedef	T										mapped_type;
		typedef	std::pair<const key_type, mapped_type>	value_type;
		typedef	Compare									key_compare;
		typedef	Alloc									allocator_type;
		typedef	allocator_type::reference				reference;
		typedef	allocator_type::const_reference			const_reference;
		typedef	allocator_type::pointer					pointer;
		typedef	allocator_type::const_pointer			const_pointer;
		
		class value_compare : public binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;
			value_compare(key_compare c);
			public:
			bool operator()(const value_type& x, const value_type& y) const {
				return (comp(x.first, y.first));
			}
		};
	private:
		struct Node
		{
			Node	*left;
			Node	*right;
			char	color;
			T		value;
		};
		
	public:
		tree
	};
}

#endif
