#include <iostream>

using ll_t = long long int;
void sort(ll_t * arr, size_t size);
ll_t median(ll_t * arr, size_t size);

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
      delete[] arr;
      return 1;
    }
  }
  std::cout << "median = " << median(arr, size) << "\n";
  delete[] arr;

}

void sort(ll_t * arr, size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    size_t min_index = i;
    for (size_t j = i+1; j < size; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    ll_t temp = arr[min_index];
    arr[min_index] = arr[i];
    arr[i] = temp;
    }
  }
}

ll_t median(ll_t * arr, size_t size)
{
  sort(arr, size);
  if (size % 2 == 0) {
    return (arr[(size / 2) - 1] + arr[(size / 2)]) / 2.0;
  }
  return arr[(size - 1) / 2];
}
