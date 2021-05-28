#include "ft_vector.hpp"
#include <vector>
#include <iostream>
int main()
{
  std::vector<int> mass(5, 0);

  mass[0] = 1;
  mass[2] = 3;
  mass.insert(mass.begin() + 1, 2);
  mass.insert(mass.begin() + 1, 2);
  for (size_t i = 0; i < mass.size(); ++i)
    std::cout << mass[i] << ' ';
  std::cout << '\n';
  ft::vector<int> arr(5, 0);
  arr[0] = 1;
  arr[2] = 3;
  arr.insert(arr.begin() + 1, 2);
  arr.insert(arr.begin() + 1, 2);
  for (size_t i = 0; i < arr.size(); ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
}
