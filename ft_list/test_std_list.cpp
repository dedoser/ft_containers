/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_std_list.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:09:52 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/24 01:46:47 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.hpp"
#include <iostream>
#include "test_class.hpp"
#include <list>

#define	ns 		std

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

void	check_constructor_and_assignOperator() {
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
	ns::list<test_class>	ms;
	for (int i = 0; i < 3; ++i)
		ms.push_back(test_class(i));
}

void	check_iterators() {
	int	mass[] = {5, 4, 6, 7, 8};
	ns::list<int>	l(mass, mass + 5);
	iterator	it = l.begin();
	std::cout << *it << '\n';
	reverse_iterator	ri = l.rbegin();
	std::cout << *ri << '\n';
	std::cout << *(--l.end()) << '\n';
	std::cout << *(--l.rend()) << '\n';
}

void	check_capacity() {
	ns::list<int>	q;
	std::cout << q.size() << ' ' << q.empty() << '\n';
	ns::list<int>	e(10, 0);
	std::cout << e.size() << ' ' << e.empty() << '\n';
}

void	check_el_access() {
	int	mass[] = {5, 4, 6, 7, 8};
	ns::list<int>	l(mass, mass + 5);
	std::cout << l.front() << ' ' << l.back() << '\n';
	l.front() = -1;
	l.back() = 10;
	std::cout << l.front() << ' ' << l.back() << '\n';
}

void	check_assign() {
	ns::list<int>	ms(3, 0);
	int	array[] = {1, 2, 3, 4, 5};
	ms.assign(array, array + 5);
	print_list(ms);
	std::cout << ms.size() << ' ' << ms.front() << ' ' <<
				 ms.back() << '\n';
	ns::list<int>	ms1(5, 1);
	ms1.assign(10, -1);
	print_list(ms1);
	std::cout << ms1.size() << ' ' << ms1.front() << ' ' <<
				 ms1.back() << '\n';
	ms1.assign(1, -1);
	print_list(ms1);
	std::cout << ms1.size() << ' ' << ms1.front() << ' ' <<
				 ms1.back() << '\n';
	
}

void	check_push() {
	ns::list<int>	l;
	for (int i = 0; i < 10; ++i)
		l.push_front(i + 1);
	print_list(l);
	for (int i = 0 ; i < 10; ++i)
		l.push_back(i + 1);
	print_list(l);
	ns::list<int>	m(10, 0);
	m.push_back(1);
	m.push_front(1);
	print_list(m);
}

void	check_pop() {
	ns::list<int>	l;
	for (int i = 0; i < 10; i++) {
		l.push_back(i);
		l.push_front(10 - i);
	}
	for (int i = 0; i < 5; ++i) {
		l.pop_back();
		l.pop_front();
	}
	print_list(l);
}

int main() {
	check_constructor_and_assignOperator();
	check_iterators();
	check_capacity();
	check_el_access();
	check_assign();
	check_push();
	check_pop();
}
