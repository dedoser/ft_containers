/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_std_map.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:46:40 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/24 20:22:46 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_map.hpp"
#include <iostream>
#include <unistd.h>
#include <string>
#include <utility>
#include <map>

#define	ns	std

template <class key, class value>
void	print_map(const ns::map<key, value> &m) {
	typename	ns::map<key, value>::const_iterator	it;
	for (it = m.begin(); it != m.end(); ++it) {
		std::cout << it->first << ' ' << it->second << '\n';
	}
	std::cout << m.size() << ' ' << m.empty() << '\n';
}

void	check_constructors() {
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
	}
	std::cout << (--m.end())->first << ' ' << (--m.end())->second << '\n';
	std::cout << (--m.rend())->first << ' ' << (--m.rend())->second << '\n';
}

int main() {
	check_constructors();
	check_iterators();
	sleep(2);
}
