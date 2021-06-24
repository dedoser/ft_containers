/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 22:28:27 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/23 23:10:56 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_CLASS_HPP
#define TEST_CLASS_HPP

class test_class
{
private:
	int	*m;
	int i;
public:
	test_class(int i);
	test_class(const test_class &obj);
	~test_class();
};

test_class::test_class(int i) : i(i)
{
	this->m = new int[3]();
}

test_class::test_class(const test_class &obj) {
	this->m = new int[3];
	i = obj.i;
}

test_class::~test_class()
{
	delete [] this->m;
}


#endif
