/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:43:33 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/19 00:43:36 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <string>
#include <iostream>
#include "ft_map.hpp"

int main() {
	// std::map<int, std::string> m;
	// std::map<int, std::string>::reverse_iterator it = m.rbegin();
	// // m.insert(it, std::pair<int, std::string>(1, "asd"));
	// std::cout << (it == m.rend()) << '\n';
	ft::map<int, std::string>	tmp;
	tmp[1] = "a";
	tmp[2] = "s";
	tmp[3] = "q";
	tmp[3] = "w";
	tmp[4] = "er";
	// tmp[3] = "q";
	// std::cout << (++tmp.begin())->first << ' ' << (++tmp.begin())->second << '\n';
	for (auto it = tmp.begin(); it != tmp.end(); it++) {
		std::cout << it->first << " " << it->second << '\n';
	}
	// tmp.erase(tmp.begin());
	// tmp.erase(++tmp.begin());
	// for (auto it = tmp.begin(); it != tmp.end(); it++) {
	// 	std::cout << it->first << " " << it->second << '\n';
	// }
	// std::cout << tmp[1] << ' ' << tmp[2] << '\n';
	return (0);
}

