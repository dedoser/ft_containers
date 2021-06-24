/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_queue.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 17:06:08 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/24 18:02:54 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_queue.hpp"
#include <iostream>
#include <unistd.h>

#define	ns	ft

int main() {
	ns::queue<int>	m;
	std::cout << m.size() << ' ' << m.empty() << '\n';
	for (int i = 0; i < 15; ++i)
		m.push(i + 1);
	std::cout << m.size() << ' ' << m.empty() << '\n';
	for (int i = 0; i < 15; ++i) {
		std::cout << m.back() << ' ' << m.front() << '\n';
		m.pop();
	}
	std::cout << m.size() << ' ' << m.empty() << '\n';
	sleep(2);
}
