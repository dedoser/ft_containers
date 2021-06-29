/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_map.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:22:18 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 00:51:50 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_map.hpp"
#include <iostream>
#include <unistd.h>
#include <string>
#include <utility>

#define	ns	ft

template <class key, class value>
void	print_map(const ns::map<key, value> &m) {
	typename	ns::map<key, value>::const_iterator	it;
	for (it = m.begin(); it != m.end(); ++it) {
		std::cout << it->first << ' ' << it->second << '\n';
	}
	std::cout << m.size() << ' ' << m.empty() << '\n';
}

void	check_constructors_and_assignOp() {
	ns::map<int, std::string>	m;
	print_map(m);
	m[0] = "fdgfgdfgdf;gdfgdfgdfg";
	m[1] = "qweqweqeqwe";
	m[2] = "123456";
	m[3] = "ujghjyjtyjtyj";
	m[4] = "erwerwrwerwerew";
	ns::map<int, std::string>	range(m.begin(), m.end());
	print_map(range);
	ns::map<int, std::string>	q(range);
	print_map(q);
	ns::map<int, std::string>	cop;
	cop = m;
	print_map(cop);
}

void	check_iterators() {
	ns::map<int, std::string>	m;
	m[1] = "qwewqeqwe";
	m[2] = "sdffdsfdfdf";
	m[0] = "dfgjdfgdfjgldfjglkfjgierjirt";
	m[-1] = "vvcbvcbcvbcvb";
	m[200] = "fvcvbvcbcvbcb";
	ns::map<int, std::string>::iterator			it = m.begin();
	ns::map<int, std::string>::reverse_iterator	rit = m.rbegin();
	for (; it != m.end(); ++it) {
		std::cout << it->first << ' ' << it->second << '\n';
		std::cout << rit->first << ' ' << rit->second << '\n';
		rit++;
	}
	std::cout << (--m.end())->first << ' ' << (--m.end())->second << '\n';
	std::cout << (++----m.rend())->first << ' ' << (--m.rend())->second << '\n';
}

void	check_capacity() {
	ns::map<int, std::string>	m;
	std::cout << m.size() << ' ' << m.empty() << '\n';
	m[0] = "qeqwewqe";
	std::cout << m.size() << ' ' << m.empty() << '\n';
	ns::map<int, std::string>	cop(m);
	std::cout << cop.size() << ' ' << cop.empty() << '\n';
	cop[5] = "dfsfbfbfb";
	m = cop;
	std::cout << m.size() << ' ' << m.empty() << '\n';
}

void	check_insert() {
	ns::map<int, std::string>	m;
	m[0] = "qewqeqwe";
	m[-1] = "rfvvdf123123";
	m[2] = "efwewfewf";
	m[4] = "rrgrrg";
	m[3] = "ffvfvfvfv";
	for (int i = 0; i < 10; ++i) {
		ns::pair<ns::map<int, std::string>::iterator, bool>	p(m.insert(ns::make_pair(i, "werwrwer")));
		std::cout << p.first->first << ' ' << p.first->second << ' ' << p.second << '\n';
		print_map(m);
	}
	for (int i = 0; i < 15; ++i) {
		ns::map<int, std::string>::iterator	it = m.insert(m.begin(), ns::make_pair(10 + i, "werwrwer"));
		std::cout << it->first << ' ' << it->second << '\n';
	}
	print_map(m);
	ns::map<int, std::string>	cop;
	cop.insert(m.begin(), m.end());
	print_map(cop);
}

void	check_erase() {
	ns::map<int, std::string>	m;
	m[0] = "ererwerwer";
	m[1] = "wertrt";
	m[3] = "rrgrggrg";
	m.erase(m.begin());
	m.erase(m.begin());
	print_map(m);
	m.erase(m.begin());
	print_map(m);
	m[0] = "ererwerwer";
	m[1] = "wertrt";
	m[3] = "rrgrggrg";
	std::cout << m.erase(0) << '\n';
	std::cout << m.erase(1) << '\n';
	std::cout << m.erase(3) << '\n';
	print_map(m);
	m[0] = "ererwerwer";
	m[1] = "wertrt";
	m[3] = "rrgrggrg";
	m.erase(m.begin(), m.end());
	print_map(m);
}

void	check_swap() {
	ns::map<int, int>	m;
	ns::map<int, int>	q;
	for (int i = 0; i < 30; ++i) {
		m[i] = -i;
		q[i * 3] = i;
	}
	print_map(m);
	print_map(q);
	m.swap(q);
	print_map(m);
	print_map(q);
}

void	check_clear() {
	ns::map<int, std::string>	m;
	m[0] = "qweqeqweqe";
	m[1] = "dfdfdsfsdfdsf";
	m[2] = "dvfvfvffbgbgb";
	m.clear();
	print_map(m);
	m[1] = "fvvvfvfv";
	print_map(m);
}

void	check_find() {
	ns::map<int, int>	m;
	m.find(0);
	for (int i = 0; i < 20; ++i)
		m[i * 2 + (i % 2) * 3] = i;
	for (int i = 0; i < 20; ++i) {
		ns::map<int, int>::iterator	it = m.find(i * 2);
		if (it != m.end())
			std::cout << it->first << ' ' << it->second << '\n';
	}
}

void	check_count() {
	ns::map<int, int>	m;
	std::cout << m.count(0);
	for (int i = 0; i < 20; ++i)
		m[i * 2 + (i % 2) * 3] = i;
	for (int i = 0; i < 20; ++i)
		std::cout << m.count(i * 2) << '\n';
}

void	check_lower_bound() {
	ns::map<int, int>	m;
	for (int i = 0; i < 20; ++i)
		m[i * 2 + (i % 2) * 3] = i;
	for (int i = 0; i < 20; ++i) {
		ns::map<int, int>::iterator	it = m.lower_bound(i * 2);
		if (it != m.end())
			std::cout << i * 2 << ' ' << it->first << ' ' << it->second << '\n';
	}
}

void	check_upper_bound() {
	ns::map<int, int>	m;
	for (int i = 0; i < 20; ++i)
		m[i * 2 + (i % 2) * 3] = i;
	for (int i = 0; i < 20; ++i) {
		ns::map<int, int>::iterator	it = m.upper_bound(i * 2);
		if (it != m.end())
			std::cout << i * 2 << ' ' << it->first << ' ' << it->second << '\n';
	}
}

void	check_equal_range() {
	ns::map<int, int>	m;
	for (int i = 0; i < 20; ++i)
		m[i * 2 + (i % 2) * 3] = i;
	for (int i = 0; i < 20; ++i) {
		ns::pair<ns::map<int, int>::iterator, ns::map<int, int>::iterator>	p(m.equal_range(i * 2));
		std::cout << p.first->first << ' ' << p.first->second << "---" << p.second->first << ' ' << p.second->second << '\n';
	}
}

int main() {
	check_constructors_and_assignOp();
	check_iterators();
	check_capacity();
	check_insert();
	check_erase();
	check_swap();
	check_clear();
	check_find();
	check_count();
	check_lower_bound();
	check_upper_bound();
	check_equal_range();
	sleep(2);
}
