#include <iostream>
#include <limits>

void sort(int * arr, size_t size);
double median(int * arr, size_t size);
int add(int a, int b);

int main()
{
  size_t size = 0;
  std::cin >> size;
  if (!std::cin) {
    std::cerr << "Bad enter\n";
    return 1;
  }
  int * arr = nullptr;
  try {
    arr = new int[size];
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
  try {
    std::cout << "median = " << median(arr, size) << "\n";
  } catch (const std::overflow_error& e) {
    std::cerr << "Overflow: " << e.what() << "\n";
    delete[] arr;
    return 3;
  } catch (const std::underflow_error& e) {
    std::cerr << "Underflow: " << e.what() << "\n";
    delete[] arr;
    return 3;
  }
  delete[] arr;
}

int min_ll()
{
  return std::numeric_limits<int>::min();
}

int max_ll()
{
  return std::numeric_limits<int>::max();
}

int add(int a, int b)
{
  if (a > 0 && b > 0 && a > max_ll() - b) {
    throw std::overflow_error("Overflow add");
  }
  if (a < 0 && b < 0 && a < min_ll() - b) {
    throw std::underflow_error("Underflow add");
  }
  return a + b;
}

void sort(int * arr, size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    size_t min_index = i;
    for (size_t j = i+1; j < size; ++j) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    int temp = arr[min_index];
    arr[min_index] = arr[i];
    arr[i] = temp;
  }
}

double median(int * arr, size_t size)
{
  sort(arr, size);
  if (size % 2 == 0) {
    return (add(arr[(size / 2) - 1], arr[(size / 2)])) / 2.0;
  }
  return arr[(size - 1) / 2];
}
