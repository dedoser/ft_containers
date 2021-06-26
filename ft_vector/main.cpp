/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:25:58 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/26 16:52:02 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Test.hpp"
#include <unistd.h>

int main() {
	ft::vector<int> m;
	Test<int> t;
	t.TestAll();
	sleep(5);
}
