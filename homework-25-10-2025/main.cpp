#include <iostream>

using ll_t = long long;

ll_t gcd(ll_t a, ll_t b);
ll_t lcm(ll_t a, ll_t b);
ll_t sqr(ll_t a);

int main()
{
  ll_t a, last_lcm, sum_sqr;
  bool first = true;
  while (std::cin >> a) {
    if (!first) { 
      last_lcm = lcm(last_lcm, a);
    } else {
      last_lcm = a;
      first = false;
    }
    sum_sqr += sqr(a);
  }

  if (std::cin.eof()) {
    std::cout << last_lcm << "\n" << sum_sqr << "\n";
  } else if (std::cin.fail()) {
    std::cerr << "Brooo, it is FAIL!!!\n";
    return 1;
  }
}

ll_t gcd(ll_t a, ll_t b)
{
  while (a != 0 && b != 0) {
	  if (a > b) {
      a = a % b;
    } else {
      b = b % a;
    }
  }
  return a+b;
}

ll_t lcm(ll_t a, ll_t b)
{           
  return (a * b) / gcd(a,b);
}

ll_t sqr(ll_t a)
{
  return a*a;
}
