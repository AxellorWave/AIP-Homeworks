#include <iostream>
#include <limits>

using u_t = unsigned;
u_t getProgressionSum(u_t b, u_t q, u_t n);
u_t add(u_t a, u_t b);
bool isAddErr(u_t res, u_t a, u_t b);
u_t mp(u_t a, u_t b);
bool isMpErr(u_t res, u_t a, u_t b);
u_t max_u();
bool isProgressionErr(u_t res, u_t b, u_t q, u_t n);

int main()
{
  u_t b, q, n;
  std::cin >> b >> q >> n;
  u_t res = getProgressionSum(b, q, n);
  if (isProgressionErr(res, b, q, n)){
    return 1;
  }
  std::cout << res << "\n";
}

u_t getProgressionSum(u_t b, u_t q, u_t n)
{
  u_t sum = 0;
  u_t b_old;
  u_t sum_old;
  while (n > 0) {
    sum_old = sum;
    sum = add(sum, b);
    if (isAddErr(sum, sum_old, b)) {
      return 0;
    }
    b_old = b;
    b = mp(b, q);
    if (isMpErr(b, b_old, q)) {
      return 0;
    }
    n--;
  }
  return sum;
}

bool isProgressionErr(u_t res, u_t b, u_t q, u_t n)
{
  return !res && b && q && n;
}

u_t max_u()
{
  return std::numeric_limits<unsigned>::max();
}

u_t add(u_t a, u_t b)
{
  if (a > max_u() - b){
    return 0;
  }
  return a+b;
}

bool isAddErr(u_t res, u_t a, u_t b)
{
  return !res && (a || b);
}

u_t mp(u_t a, u_t b)
{
  if (max_u() / a < b){
    return 0;
  }
  return a*b;
}

bool isMpErr(u_t res, u_t a, u_t b)
{
  return !res && a && b;
}