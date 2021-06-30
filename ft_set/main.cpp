/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 16:11:25 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/30 16:15:57 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_set.hpp"
#include <iostream>

int main() {
	ft::set<int>	m;
	for (int i = 0; i < 10; ++i) {
		m.insert(i);
		m.insert(i);
	}
	for (auto it = m.begin(); it != m.end(); ++it)
		std::cout << *it << ' ';
	std::cout << '\n';
}

