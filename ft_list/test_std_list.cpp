/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_std_list.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:09:52 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 01:11:09 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.hpp"
#include <iostream>
#include "test_class.hpp"
#include <list>
#include <unistd.h>
#include <cmath>

#define	ns 		std

typedef	ns::list<int>::iterator	iterator;
typedef	ns::list<int>::const_iterator	const_iterator;
typedef	ns::list<int>::reverse_iterator	reverse_iterator;

template <class T>
void	print_list(const ns::list<T> &l) {
	typename ns::list<T>::const_iterator	it = l.begin();
	for (; it != l.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << '\n';
	std::cout << l.size() << '\n';
}

void	check_constructor_and_assignOperator() {
	std::cout << "constructor and assign operator test\n";
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
	std::cout << "iterators test\n";
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
	std::cout << "capacity test\n";
	ns::list<int>	q;
	std::cout << q.size() << ' ' << q.empty() << '\n';
	ns::list<int>	e(10, 0);
	std::cout << e.size() << ' ' << e.empty() << '\n';
}

void	check_el_access() {
	std::cout << "element access test\n";
	int	mass[] = {5, 4, 6, 7, 8};
	ns::list<int>	l(mass, mass + 5);
	std::cout << l.front() << ' ' << l.back() << '\n';
	l.front() = -1;
	l.back() = 10;
	std::cout << l.front() << ' ' << l.back() << '\n';
}

void	check_assign() {
	std::cout << "assign test\n";
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
	std::cout << "pushs test\n";
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
	std::cout << "pops test\n";
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

void	check_insert() {
	std::cout << "insert test\n";
	ns::list<int>	l(10, 0);
	std::cout << *l.insert(++l.begin(), -1) << '\n';
	print_list(l);
	l.insert(++++l.begin(), 20, 10);
	print_list(l);
	int	m[] = {1, 2, 3, 4, 5};
	l.insert(--l.end(), m, m + 5);
	print_list(l);
}

void	check_erase() {
	std::cout << "erase test\n";
	ns::list<int>	m(10, 0);
	for (int i = 0; i < 10; ++i)
		m.push_back(i + 1);
	size_t	size = m.size();
	std::cout << m.size() << ' ';
	for (size_t i = 0; i < size; ++i) {
		iterator	it = m.begin();
		std::cout << *m.erase(it) << ' ';
	}
	for (int i = 0; i < 10; ++i)
		m.push_front(i + 1);
	std::cout << *m.erase(m.begin(), ++++m.begin());
	print_list(m);
	for (int i = 0; i < 10; ++i)
		m.push_front(i + 1);
}

void	check_swap() {
	std::cout << "swap test\n";
	ns::list<int>	n;
	ns::list<int>	k;
	for (int i = 0; i < 15; ++i) {
		n.push_back(i + 1);
		k.push_front(i);
	}
	n.swap(k);
	print_list(n);
	print_list(k);
}

void	check_resize() {
	std::cout << "resize test\n";
	ns::list<int>	k;
	for (int i = 0; i < 10; ++i)
		k.push_back(i + 1);
	k.resize(20);
	print_list(k);
	std::cout << k.size() << '\n';
	k.resize(0);
	std::cout << k.size() << '\n';
	print_list(k);
}

void	check_splice() {
	std::cout << "splice test\n";
	ns::list<int>	n(10, 0);
	ns::list<int>	k(5, -1);
	ns::list<int>	k1(1, 10);
	ns::list<int>	k2(6, 6);
	for (int i = 0; i < 5; ++i) {
		n.push_back(i + 1);
		k.push_front(i + 1);
	}
	n.splice(n.end(), k);
	print_list(n);
	print_list(k);
	k.splice(k.begin(), k1);
	print_list(k);
	print_list(k1);
	n.splice(++n.begin(), k, k.begin());
	print_list(n);
	print_list(k);
	n.splice(n.begin(), k, k.begin(), k.end());
	print_list(n);
	print_list(k);
}

void	check_remove() {
	ns::list<int>	l(10, -1);
	l.insert(++++l.begin(), 10);
	for (int i = 0; i < 5; ++i) {
		l.push_front(9);
		l.push_back(9);
	}
	print_list(l);
	l.remove(10);
	print_list(l);
	l.remove(9);
	print_list(l);
}

bool single_digit (const int& value) {
	return (value < 10);
}

struct is_odd {
	bool operator() (const int& value) {
		return (value %2 ) == 1;
	}
};

void	check_remove_if() {
	ns::list<int>	l(10, 0);
	for (int i = 0; i < 20; ++i) {
		l.push_back(i + 1);
		l.push_front(20 - i);
	}
	l.remove_if(is_odd());
	print_list(l);
	l.remove_if(single_digit);
	print_list(l);
}

bool same_integral_part (double first, double second) {
	return (int(first)==int(second));
}

struct is_near {
	bool operator() (double first, double second) {
		return (fabs(first-second) < 5.0);
	}
};

void	check_unique() {
	ns::list<int>	l;
	for (int i = 0; i < 20; ++i) {
		l.push_back(i + 1);
		if ((i + 1) % 2)
			l.push_back(i + 1);
	}
	l.unique();
	print_list(l);
	double mydoubles[] = {12.15, 2.72, 73.0, 12.77, 3.14,
						12.77, 73.35, 72.25, 15.3, 72.25 };
	ns::list<double> mylist (mydoubles, mydoubles + 10);
	mylist.sort();
	mylist.unique();
	print_list(mylist);
	mylist.unique(same_integral_part);
	print_list(mylist);
	mylist.unique(is_near());
	print_list(mylist);
}

bool mycomparison (double first, double second) {
	return ( int(first)<int(second) );
}

void	check_merge() {
	ns::list<int>	m(10, 0);
	ns::list<int>	k;
	ns::list<int>	l;
	for (int i = 0; i < 10; ++i) {
		m.push_back(i + 1);
		m.push_front(10 - i);
		k.push_front(i * 2 + (i % 2) * 3);
		l.push_back(i - 1);
	}
	m.merge(k);
	print_list(m);
	print_list(k);
	m.sort();
	m.merge(l);
	print_list(m);

	ns::list<double> first, second;

	first.push_back (3.1);
	first.push_back (2.2);
	first.push_back (2.9);
	second.push_back (3.7);
	second.push_back (7.1);
	second.push_back (1.4);
	first.sort();
	second.sort();
	first.merge(second);
	second.push_back (2.1);
	first.merge(second, mycomparison);
	print_list(first);
	print_list(second);
	first.merge(second);
	print_list(first);
}

bool compare_nocase (const std::string& first, const std::string& second)
{
	unsigned int i = 0;
	while ((i < first.length()) && (i < second.length()))
	{
		if (tolower(first[i]) < tolower(second[i]))
			return (true);
		else if (tolower(first[i]) > tolower(second[i]))
			return (false);
		++i;
	}
	return (first.length() < second.length());
}

void	check_sort() {
	ns::list<int>	m(10, 0);
	for (int i = 0; i < 30; ++i) {
		m.push_front(30 - i);
		m.push_back(30 - i);
	}
	m.sort();
	print_list(m);
	ns::list<std::string>	mylist;
	mylist.push_back ("one");
	mylist.push_back ("two");
	mylist.push_back ("Three");
	mylist.sort();
	print_list(mylist);
	mylist.sort(compare_nocase);
	print_list(mylist);
}

void	check_reverse() {
	ns::list<int>	m(10, 1);

	for (int i = 0; i < 40; ++i) {
		m.push_back(i);
		m.push_front(20 - i);
		m.insert(++m.begin(), 3, i);
	}
	m.reverse();
	print_list(m);
}

void	check_relOperators() {
	ns::list<int>	m;
	ns::list<int>	k;
	
	std::cout << (m == k) << '\n';
	for (int i = 0; i < 2; ++i) {
		m.push_back(i);
		k.push_back(i);
	}
	std::cout << (m == k) << '\n';
	m.back() = 10;
	std::cout << (m == k) << '\n';
	m.push_back(8);
	std::cout << (m != k) << '\n';
	std::cout << (m < k) << '\n';
	std::cout << (m > k) << '\n';
	k.back() = 10;
	std::cout << (m < k) << '\n';
	std::cout << (m > k) << '\n';
	std::cout << (m <= k) << '\n';
	std::cout << (m >= k) << '\n';
}

int main() {
	check_constructor_and_assignOperator();
	check_iterators();
	check_capacity();
	check_el_access();
	check_assign();
	check_push();
	check_pop();
	check_insert();
	check_erase();
	check_swap();
	check_resize();
	check_splice();
	check_remove();
	check_remove_if();
	check_unique();
	check_merge();
	check_sort();
	check_reverse();
	check_relOperators();
	sleep(2);
}
