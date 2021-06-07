/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ReverseIterator.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:24:25 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/03 22:29:40 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ReverseIterator_HPP
#define FT_ReverseIterator_HPP

namespace ft
{
	template <class Iterator>
	class ReverseIterator
	{
	public:
		typedef Iterator								iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		
		ReverseIterator() : _iter(0) {}
		explicit ReverseIterator(iterator_type it) : _iter(it) {}
		template<class Iter>
			ReverseIterator(const ReverseIterator<Iter> &rev_it) : _iter(rev_it._iter) {}
		virtual	~ReverseIterator() {}

		iterator_type	base() const {
			return (_iter);
		}

		reference		operator*() {
			return (*_iter);
		}

		ReverseIterator	operator+(difference_type n) const {
			return (ReverseIterator<iterator_type>(this->base() - n));
		}

		ReverseIterator	operator++() {
			_iter--;
			return (*this);
		}

		ReverseIterator	operator++(int) {
			ReverseIterator<iterator_type> tmp(*this);
			_iter--;
			return (tmp);
		}

		ReverseIterator	&operator+=(difference_type n) {
			_iter -= n;
			return (*this);
		}

		ReverseIterator	operator-(difference_type n) const {
			return (ReverseIterator<iterator_type>(this->base() + n));
		}

		ReverseIterator	operator--() {
			_iter++;
			return (*this);
		}

		ReverseIterator	operator--(int) {
			ReverseIterator<iterator_type> tmp(*this);
			_iter++;
			return (tmp);
		}

		ReverseIterator	&operator-=(difference_type n) {
			_iter += n;
			return (*this);
		}

		pointer				operator->() const {
			return &(operator*());
		}

		reference			operator[](difference_type n) {
			return (*(_iter - n));
		}
	private:
		iterator_type	_iter;
	};

	template <class Iterator>
		ReverseIterator<Iterator> operator+(
			typename ReverseIterator<Iterator>::difference_type n,
			const ReverseIterator<Iterator> &rev_it) {
			return (ReverseIterator<Iterator>(rev_it - n));
		}

	template <class Iterator>
		typename ReverseIterator<Iterator>::difference_type operator-(
			const ReverseIterator<Iterator> &lhs,
			const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() - rhs.base());
		}

	template <class Iterator>
		bool	operator== (const ReverseIterator<Iterator> &lhs,
							const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() == rhs.base());
		}

	template <class Iterator>
		bool	operator!= (const ReverseIterator<Iterator> &lhs,
							const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() != rhs.base());
		}

	template <class Iterator>
		bool	operator<	(const ReverseIterator<Iterator> &lhs,
							 const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() > rhs.base());
		}
	template <class Iterator>
		bool	operator>	(const ReverseIterator<Iterator> &lhs,
							 const ReverseIterator<Iterator> &rhs) {
			return (lhs.base() < rhs.base());
		}
	template <class Iterator>
		bool	operator>=	(const ReverseIterator<Iterator> &lhs,
							 const ReverseIterator<Iterator> &rhs) {
			return (lhs > rhs || lhs == rhs);
		}
	template <class Iterator>
		bool	operator<=	(const ReverseIterator<Iterator> &lhs,
							 const ReverseIterator<Iterator> &rhs) {
			return (lhs < rhs || lhs == rhs);
		}
}

#endif
