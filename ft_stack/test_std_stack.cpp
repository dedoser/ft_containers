/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_std_stack.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:55:15 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/24 17:03:51 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.hpp"
#include <iostream>
#include <stack>
#include <unistd.h>

#define	ns 		std

int	main() {
	ns::stack<int>	m;
	std::cout << m.empty() << ' ' << m.size() << '\n';
	for (int i = 0; i < 10; ++i)
		m.push(i + 1);
	std::cout << m.empty() << ' ' << m.size() << '\n';
	for (int i = 0; i < 10; ++i) {
		std::cout << m.top() << '\n';
		m.pop();
	}
	std::cout << m.empty() << ' ' << m.size() << '\n';
	sleep(2);
}
