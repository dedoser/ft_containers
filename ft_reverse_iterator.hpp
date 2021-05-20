/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:24:25 by fignigno          #+#    #+#             */
/*   Updated: 2021/05/20 12:53:35 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator								iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		
		reverse_iterator() : _iter(0) {}
		explicit reverse_iterator(iterator_type it) : _iter(it) {}
		template<class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it) : _iter(rev_it._iter) {}
		virtual	~reverse_iterator() {}

		iterator_type	base() const {
			return (_iter);
		}

		reference		operator*() const {
			return (*_iter);
		}

		reverse_iterator	operator+(difference_type n) const {
			return (reverse_iterator<iterator_type>(this->base() - n));
		}

		reverse_iterator	operator++() {
			_ptr--;
			return (*this);
		}

		reverse_iterator	operator++(int) {
			reverse_iterator<iterator_type> tmp(*this);
			_ptr--;
			return (tmp);
		}

		reverse_iterator	&operator+=(difference_type n) {
			_ptr -= n;
			return (*this);
		}

		reverse_iterator	operator-(difference_type n) const {
			return (reverse_iterator<iterator_type>(this->base() + n));
		}

		reverse_iterator	operator--() {
			_ptr++;
			return (*this);
		}

		reverse_iterator	operator--(int) {
			reverse_iterator<iterator_type> tmp(*this);
			_ptr++;
			return (tmp);
		}

		reverse_iterator	&operator-=(difference_type n) {
			_ptr += n;
			return (*this);
		}

		pointer				operator->() const {
			return &(operator*());
		}

		reference			operator[](difference_type n) {
			return (*(_ptr - n));
		}
	private:
		iterator_type	_iter;
	};

	template <class Iterator>
		reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator> &rev_it) {
			return (reverse_iterator<Iterator>(rev_it - n));
		}

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator> &lhs,
			const reverse_iterator<Iterator> &rhs) {
			return (lhs.base() - rhs.base());
		}

	template <class Iterator>
		bool	operator== (const reverse_iterator<Iterator> &lhs,
							const reverse_iterator<Iterator> &rhs) {
			return (lhs.base() == rhs.base());
		}

	template <class Iterator>
		bool	operator!= (const reverse_iterator<Iterator> &lhs,
							const reverse_iterator<Iterator> &rhs) {
			return (lhs.base() != rhs.base());
		}

	template <class Iterator>
		bool	operator<	(const reverse_iterator<Iterator> &lhs,
							 const reverse_iterator<Iterator> &rhs) {
			return (lhs.base() > rhs.base());
		}
	template <class Iterator>
		bool	operator>	(const reverse_iterator<Iterator> &lhs,
							 const reverse_iterator<Iterator> &rhs) {
			return (lhs.base() < rhs.base());
		}
	template <class Iterator>
		bool	operator>=	(const reverse_iterator<Iterator> &lhs,
							 const reverse_iterator<Iterator> &rhs) {
			return (lhs > rhs || lhs == rhs);
		}
	template <class Iterator>
		bool	operator<=	(const reverse_iterator<Iterator> &lhs,
							 const reverse_iterator<Iterator> &rhs) {
			return (lhs < rhs || lhs == rhs);
		}
}

#endif
