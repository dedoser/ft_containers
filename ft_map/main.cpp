/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:43:33 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/17 19:41:49 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <string>
#include <iostream>
int main() {
	std::map<int, std::string> m;
	std::map<int, std::string>::reverse_iterator it = m.rbegin();
	// m.insert(it, std::pair<int, std::string>(1, "asd"));
	std::cout << (it == m.rend()) << '\n';
}
