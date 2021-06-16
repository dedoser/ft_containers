/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:43:33 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/16 19:16:01 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <string>
#include <iostream>
int main() {
	std::map<int, std::string> m;
	m[0] = "a";
	m[1] = "f";
	m[-1] = "q";
	std::map<int, std::string>::iterator it = m.begin();
	std::cout << (*it).first << '\n';
}
