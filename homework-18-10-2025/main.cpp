#include <iostream>

int get_len(size_t n)
{
  if (n == 0){
    return 1;
  }
  int len = 1;
  while (n >> 1){
    n>>=1;
    len++;
  }
  return len;
}

bool is_bit_palindrom_iter(size_t n)
{
  if (n == 0){
    return 1;
  }
  int len = get_len(n);
  int left = len-1;
  int right = 0;
  while (left > right){
    if (((n >> left) & 1) != ((n >> right) & 1)){
      return 0;
    }
    left--;
    right++;
  }
  return 1;
}

bool is_bit_palindrom_recursion(size_t n, int len)
{
  if (len <= 1){
    return 1;
  }
  if (((n >> (len - 1)) & 1) != (n&1)){
    return 0;
  }
  n >>= 1;
  n &= (1 << (len-2))-1;
  return is_bit_palindrom_recursion(n, len - 2);
 }

int main()
{
  size_t n;
  while (true){
    std::cin >> n;
    std::cout << is_bit_palindrom_iter(n) << '\n';
    std::cout << is_bit_palindrom_recursion(n, get_len(n)) << '\n';

  }
}

