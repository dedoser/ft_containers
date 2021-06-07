/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:28:59 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/07 22:41:37 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include <cmath>
#include "ft_list.hpp"

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

int main1 ()
{
  double mydoubles[]={2.72,  3.14, 12.15, 12.77, 12.77,
                      15.3,  72.25, 72.25, 73.0,  73.35};
  ft::list<double> mylist (mydoubles,mydoubles+10);
  
//   mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
                             // 15.3,  72.25, 72.25, 73.0,  73.35

  mylist.unique();           //  2.72,  3.14, 12.15, 12.77
                             // 15.3,  72.25, 73.0,  73.35

  mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
                                       // 15.3,  72.25, 73.0

  mylist.unique (is_near());           //  2.72, 12.15, 72.25

  std::cout << "mylist contains:";
  for (ft::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}

int main() {
	int	arr[] = {5, 4, 7, 100, 1, 7, 9000};
	int	marr[] = {13, 1, 1, 1, 100000, 5, 7};
	std::list<int>	myList(arr, arr + 7);
	std::list<int>	mergeList(marr, marr + 7);
	myList.merge(mergeList);
	 for (auto it = myList.begin(); it != myList.end(); ++it) {
		std::cout << *it << '\n';
	}
	// ft::list<int>	cont(3, 2);
	// ft::list<int>	spl(4, 1);
	
	// spl.front() = -1;
	// cont.splice(cont.begin(), spl, spl.begin(), spl.end());
	// cont.remove(1);
	// for (auto it = cont.begin(); it != cont.end(); ++it) {
	// 	std::cout << *it << '\n';
	// }
	// std::cout << cont.size()  << ' ' << spl.size() << '\n';
	// int i = 0;
	// for (auto it = cont.begin(); it != cont.end(); ++it)
	// 	*it = ++i;
	// ft::list<int>	list(cont.begin(), cont.end());
	// // for (auto it = list.begin(); it != list.end(); ++it)
	// // 	std::cout << *it << '\n';
	
	// list.insert(list.begin(), cont.begin(), cont.end());
	// // for (auto it = list.begin(); it != list.end(); ++it)
	// // 	std::cout << *it << '\n';
	// // std::cout << "--------------\n";
	// // list.erase(list.begin(), ++++list.begin());
	// list.resize(10);
	// for (auto it = list.begin(); it != list.end(); ++it)
	// 	std::cout << *it << '\n';
}
