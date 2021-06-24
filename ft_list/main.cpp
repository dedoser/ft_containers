/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:28:59 by fignigno          #+#    #+#             */
/*   Updated: 2021/06/24 01:31:47 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include <cmath>
#include "ft_list.hpp"

// // a binary predicate implemented as a function:
// bool same_integral_part (double first, double second)
// { return ( int(first)==int(second) ); }

// // a binary predicate implemented as a class:
// struct is_near {
//   bool operator() (double first, double second)
//   { return (fabs(first-second)<5.0); }
// };

// int main1 ()
// {
//   double mydoubles[]={2.72,  3.14, 12.15, 12.77, 12.77,
//                       15.3,  72.25, 72.25, 73.0,  73.35};
//   ft::list<double> mylist (mydoubles,mydoubles+10);
  
// //   mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
//                              // 15.3,  72.25, 72.25, 73.0,  73.35

//   mylist.unique();           //  2.72,  3.14, 12.15, 12.77
//                              // 15.3,  72.25, 73.0,  73.35

//   mylist.unique (same_integral_part);  //  2.72,  3.14, 12.15
//                                        // 15.3,  72.25, 73.0

//   mylist.unique (is_near());           //  2.72, 12.15, 72.25

//   std::cout << "mylist contains:";
//   for (ft::list<double>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

//   return 0;
// }

// int main10() {
// 	int	arr[] = {1, 2, 3, 4, 5, 20};
// 	int	marr[] = {1, 2, 3, 7, 1000, 10000};
// 	std::list<int>	myList(arr, arr + 6);
// 	std::list<int>	mergeList(marr, marr + 6);
	
// 	myList.merge(mergeList);
// 	// myList.splice(myList.begin(), mergeList, mergeList.begin(), mergeList.end());
// 	 for (auto it = myList.begin(); it != myList.end(); ++it) {
// 		std::cout << *it << '\n';
// 	}
// 	std::cout << myList.size()  << ' ' << mergeList.size() << '\n';
// 	// ft::list<int>	cont(3, 2);
// 	// ft::list<int>	spl(4, 1);
	
// 	// spl.front() = -1;
// 	// cont.splice(cont.begin(), spl, spl.begin(), spl.begin());
// 	// for (auto it = cont.begin(); it != cont.end(); ++it) {
// 	// 	std::cout << *it << '\n';
// 	// }
// 	// for (auto it = spl.begin(); it != spl.end(); ++it) {
// 	// 	std::cout << *it << '\n';
// 	// }
// 	// std::cout << cont.size()  << ' ' << spl.size() << '\n';
// 	// int i = 0;
// 	// for (auto it = cont.begin(); it != cont.end(); ++it)
// 	// 	*it = ++i;
// 	// ft::list<int>	list(cont.begin(), cont.end());
// 	// // for (auto it = list.begin(); it != list.end(); ++it)
// 	// // 	std::cout << *it << '\n';
	
// 	// list.insert(list.begin(), cont.begin(), cont.end());
// 	// // for (auto it = list.begin(); it != list.end(); ++it)
// 	// // 	std::cout << *it << '\n';
// 	// // std::cout << "--------------\n";
// 	// // list.erase(list.begin(), ++++list.begin());
// 	// list.resize(10);
// 	// for (auto it = list.begin(); it != list.end(); ++it)
// 	// 	std::cout << *it << '\n';
// }

// // compare only integral part:
// bool mycomparison (double first, double second)
// { return ( int(first)<int(second) ); }

// int main1()
// {
//   std::list<double> first, second;

//   first.push_back (3.1);
//   first.push_back (2.2);
//   first.push_back (2.9);

//   second.push_back (3.7);
//   second.push_back (7.1);
//   second.push_back (1.4);

//   first.sort();
//   second.sort();

//   first.merge(second);

//   // (second is now empty)

//   second.push_back (2.1);

//   first.merge(second,mycomparison);

//   std::cout << "first contains:";
//   for (auto it=first.begin(); it!=first.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';
// std::cout << (first == second) << '\n';
//   return 0;
// }

// #include <string>
// #include <cctype>

// // comparison, not case sensitive.
// bool compare_nocase (const std::string& first, const std::string& second)
// {
//   unsigned int i=0;
//   while ( (i<first.length()) && (i<second.length()) )
//   {
//     if (tolower(first[i])<tolower(second[i])) return true;
//     else if (tolower(first[i])>tolower(second[i])) return false;
//     ++i;
//   }
//   return ( first.length() < second.length() );
// }

// int main45 ()
// {
//   ft::list<std::string> mylist;
//   ft::list<std::string>::iterator it;
//   mylist.push_back ("one");
//   mylist.push_back ("two");
//   mylist.push_back ("Three");

//   mylist.sort();

//   std::cout << "mylist contains:";
//   for (it=mylist.begin(); it!=mylist.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

//   mylist.sort(compare_nocase);

//   std::cout << "mylist contains:";
//   for (it=mylist.begin(); it!=mylist.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

// 	mylist.reverse();
// 	std::cout << "mylist contains:";
//   for (it=mylist.begin(); it!=mylist.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';
//   return 0;
// }

int main() {
  std::list<int> k;
  k.pop_front();
}
