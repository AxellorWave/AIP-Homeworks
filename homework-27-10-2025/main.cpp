#include <iostream>

using ll_t = long long int;

int main()
{
  size_t size = 0;
  std::cin >> size;
  if (!std::cin) {
    std::cerr << "Bad enter\n";
    return 1;
  }
  ll_t * arr = nullptr;
  try {
    arr = new ll_t[size];
  } catch (std::bad_alloc & e) {
    std::cerr << "Bad Alloc\n";
    return 2; 
  }
  for (size_t i = 0; i < size; ++i) {
    std::cin >> arr[i];
    if (!std::cin) {
      std::cerr << "Bad enter\n";
      return 1;
    }
  }


  for (size_t i = 0; i < size; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";
  delete[] arr;

}