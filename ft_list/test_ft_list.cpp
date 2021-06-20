/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_list.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:09:52 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/20 17:36:47 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.hpp"
#include <iostream>

#define	ns 		ft

typedef	ns::list<int>::iterator	iterator;
typedef	ns::list<int>::const_iterator	const_iterator;
typedef	ns::list<int>::reverse_iterator	reverse_iterator;

void	print_list(const ns::list<int> &l) {
	const_iterator	it = l.begin();
	for (; it != l.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << '\n';
}

void	check_constructor_and_assign() {
	ns::list<int>	l;
	std::cout << l.size() << ' ' << l.empty() << '\n';
	print_list(l);
	ns::list<int>	q(10, 0);
	std::cout << q.size() << ' ' << q.empty() << '\n';
	print_list(q);
	int	mass[] = {1, 2, 3, 4, 5};
	ns::list<int>	r(mass, mass + 5);
	std::cout << r.size() << ' ' << r.empty() << '\n';
	print_list(r);
	ns::list<int>	cop(r);
	std::cout << cop.size() << ' ' << cop.empty() << '\n';
	print_list(cop);
	cop = q;
	print_list(cop);
}

void	check_iterators() {
	int	mass[] = {5, 4, 6, 7, 8};
	ns::list<int>	l(mass, mass + 5);
	iterator	it = l.begin();
	std::cout << *it << '\n';
	reverse_iterator	ri = l.rbegin();
	std::cout << *ri << '\n';
}

int main() {
	check_constructor_and_assign();
	check_iterators();
}