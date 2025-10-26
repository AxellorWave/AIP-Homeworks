#include <iostream>
#include <limits>

using u_t = unsigned;
u_t getProgressionSum(u_t b, u_t q, u_t n);
u_t add(u_t a, u_t b);
u_t mp(u_t a, u_t b);
u_t max_u();


int main()
{
  u_t b, q, n;
  std::cin >> b >> q >> n;
  try {
    u_t res = getProgressionSum(b, q, n);
    std::cout << res << "\n";
  } catch (const std::overflow_error &e){
    std::cerr << e.what() << "\n";
    return 1;
  }
}

u_t getProgressionSum(u_t b, u_t q, u_t n)
{
  u_t sum = 0;
  while (n > 0) {
    sum = add(sum, b);
    b = mp(b, q);
    n--;
  }
  return sum;
}

u_t max_u()
{
  return std::numeric_limits<unsigned>::max();
}

u_t add(u_t a, u_t b)
{
  if (a < max_u() - b){
    return a+b;
  }
  throw
    std::overflow_error("Error add");
}

u_t mp(u_t a, u_t b)
{
  if (max_u() / a > b){
    return a*b;
  }
  throw
    std::overflow_error("Error multiply");
}
