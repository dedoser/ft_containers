/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 20:47:22 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/26 16:44:35 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include "ft_vector.hpp"
#include <vector>
#include <cassert>
#include <iostream>

template<class T = int>
class Test
{
private:
	void	AssertCompareContent(const ft::vector<T> &ft, const std::vector<T> &std)  const{
		assert(ft.size() == std.size());
		for (size_t i = 0; i < ft.size(); ++i)
			assert(ft[i] == std[i]);
	}
	void	AssertCompareContent(const std::vector<T> &lhs, const std::vector<T> &rhs)  const{
		assert(lhs.size() == rhs.size());
		for (size_t i = 0; i < lhs.size(); ++i)
			assert(lhs[i] == rhs[i]);
	}
	void	AssertCompareContent(const ft::vector<T> &lhs, const ft::vector<T> &rhs)  const{
		assert(lhs.size() == rhs.size());
		for (size_t i = 0; i < lhs.size(); ++i)
			assert(lhs[i] == rhs[i]);
	}
	ft::vector<T>	_ftv;
	std::vector<T>	_stdv;
public:
	Test() {}
	~Test() {}
	void	ConstructorTest() {
		AssertCompareContent(ft::vector<T>(), std::vector<T>());
		AssertCompareContent(ft::vector<T>(10, T()), std::vector<T>(10, T()));
		std::vector<T> tmp(15, T());
		AssertCompareContent(ft::vector<T>(tmp.begin(), tmp.end()),
							 std::vector<T>(tmp.begin(), tmp.end()));
		std::cout << "Constructor Test - SUCCESS\n";
	}
	void	AssignOperatorTest() {
		ft::vector<T>	ftTmp(10, 0);
		std::vector<T>	stdTmp(10, 0);
		_ftv = ftTmp;
		_stdv = stdTmp;
		AssertCompareContent(_ftv, ftTmp);
		AssertCompareContent(_stdv, stdTmp);
		AssertCompareContent(_ftv, _stdv);
		ftTmp.push_back(1);
		stdTmp.push_back(1);
		_ftv = ftTmp;
		_stdv = stdTmp;
		AssertCompareContent(_ftv, ftTmp);
		AssertCompareContent(_stdv, stdTmp);
		AssertCompareContent(_ftv, _stdv);
		std::cout << "Assign Operator Test - SUCCESS\n";
	}
	void	IteratorsTest() {
		typename ft::vector<T>::iterator it = _ftv.begin();
		typename ft::vector<T>::iterator it1(it);
		assert(it == it1);
		assert(*_ftv.begin() == _ftv[0]);
		assert(*(_ftv.end() - 1) == _ftv[_ftv.size() - 1]);
		assert(*(_ftv.rbegin()) == _ftv[_ftv.size() - 1]);
		assert(*(_ftv.rend() - 1) == _ftv[0]);
		std::cout << "Iterators Test - SUCCESS\n";
	}
	void	SizeTest() {
		_ftv.resize(15);
		_stdv.resize(15);
		assert(_ftv.size() == _stdv.size());
		_ftv.push_back(0);
		_stdv.push_back(0);
		assert(_ftv.size() == _stdv.size());
	}
	void	EmptyTest() {
		_ftv.resize(0);
		assert(_ftv.size() == 0);
	}
	void	ReserveTest() {
		_ftv.reserve(30);
		assert(_ftv.capacity() == 30);
		_stdv.reserve(30);
		assert(_stdv.capacity() == 30);
	}
	void	AllCapacityMethodsTest() {
		SizeTest();
		EmptyTest();
		ReserveTest();
		std::cout << "All Capacity Methods Test - SUCCESS\n";
	}
	void	AccessOperatorTest() {
		for (size_t i = 0; i < _ftv.size(); ++i) {
			_ftv[i] = i;
			assert(_ftv[i] == i);
		}
		std::cout << "Access Operator Test - SUCCESS\n";
	}
	void	AtTest() {
		for (size_t i = 0; i < _ftv.size(); ++i) {
			_ftv.at(i) = i;
			assert(_ftv.at(i) == (int)i);
		}
		try {
			_ftv.at(_ftv.size());
		}
		catch (std::out_of_range &e) {
			std::cout << "At Test - SUCCESS\n";
		}
	}
	void	FrontTest() {
		_ftv.resize(1);
		_ftv[0] = 0;
		assert(_ftv.front() == _ftv[0]);
		std::cout << "Front Test - SUCCESS\n";
	}
	void	BackTest() {
		_ftv.resize(1);
		_ftv.at(_ftv.size() - 1) = 0;
		assert(_ftv.back() == _ftv[_ftv.size() - 1]);
		std::cout << "Back Test - SUCCESS\n";
	}
	void	AssignTest() {
		_ftv.resize(0);
		_stdv.resize(0);
		_ftv.assign(10, 5);
		_stdv.assign(10, 5);
		AssertCompareContent(_ftv, _stdv);
		_ftv.assign(1, 10);
		_stdv.assign(1, 10);
		AssertCompareContent(_ftv, _stdv);
		std::vector<int>	tmp;
		for (size_t i = 0; i < 10; ++i)
			tmp.push_back(i);
		_ftv.assign(tmp.begin(), tmp.end());
		_stdv.assign(tmp.begin(), tmp.end());
		AssertCompareContent(_ftv, _stdv);
		std::cout << "Assign Test - SUCCESS\n";
	}
	void	PushBackTest() {
		_ftv.resize(0);
		_stdv.resize(0);
		for (size_t i = 0; i < 10; ++i) {
			_ftv.push_back(i);
			_stdv.push_back(i);
		}
		AssertCompareContent(_ftv, _stdv);
		std::cout << "PushBack Test - SUCCESS\n";
		
	}
	void	PopBackTest() {
		_ftv.pop_back();
		_stdv.pop_back();
		AssertCompareContent(_ftv, _stdv);
		std::cout << "PopBack Test - SUCCESS\n";
	}
	void	InsertTest() {
		_ftv.resize(0);
		_stdv.resize(0);
		for (size_t i = 0; i < 5; ++i) {
			_ftv.push_back(i);
			_stdv.push_back(i);
		}
		_stdv.insert(_stdv.begin(), 10);
		_stdv.insert(_stdv.begin(), 5, 11);
		assert(*_ftv.insert(_ftv.begin(), 10) == 10);
		_ftv.insert(_ftv.begin(), 5, 11);
		AssertCompareContent(_ftv, _stdv);
		std::vector<T>	range(3, -7);
		_ftv.insert(_ftv.begin() + 4, range.begin(), range.end());
		_stdv.insert(_stdv.begin() + 4, range.begin(), range.end());
		AssertCompareContent(_ftv, _stdv);
		std::cout << "Insert Test - SUCCESS\n";
	}
	void	EraseTest() {
		assert(*_ftv.erase(_ftv.begin() + 1) == *_stdv.erase(_stdv.begin() + 1));
		assert(*_ftv.erase(_ftv.begin(), _ftv.begin() + 3) == *_stdv.erase(_stdv.begin(), _stdv.begin() + 3));
		AssertCompareContent(_ftv, _stdv);
		std::cout << "Erase Test - SUCCESS\n";
	}
	void	ClearTest() {
		_ftv.clear();
		assert(_ftv.empty());
		std::cout << "Clear Test - SUCCESS\n";
	}
	void	RelationalOperatorsTest() {
		ft::vector<T>	CompareElem;
		_ftv.resize(0);
		_ftv.push_back(1);
		assert(_ftv != CompareElem);
		CompareElem.push_back(1);
		assert(_ftv == CompareElem);
		_ftv[0] = 4;
		assert(_ftv > CompareElem);
		assert(CompareElem < _ftv);
		CompareElem.insert(CompareElem.begin(), 2);
		assert(_ftv > CompareElem);
		std::cout << "Relational Operators Test - SUCCESS\n";
	}
	void	TestAll() {
		ConstructorTest();
		AssignOperatorTest();
		IteratorsTest();
		AllCapacityMethodsTest();
		AtTest();
		FrontTest();
		BackTest();
		AssignTest();
		PushBackTest();
		PopBackTest();
		InsertTest();
		EraseTest();
		ClearTest();
		RelationalOperatorsTest();
		_ftv.~vector();
	}
};

#endif
