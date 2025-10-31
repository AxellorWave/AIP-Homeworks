#include <iostream>
#include <limits>

using ll_t = long long;

ll_t max_ll();
ll_t min_ll();
ll_t gcd(ll_t a, ll_t b);
ll_t lcm(ll_t a, ll_t b);
ll_t abs(ll_t a);
ll_t add(ll_t a, ll_t b);
ll_t mp(ll_t a, ll_t b);


int main()
{
  ll_t a, last_lcm, sum_sqr;
  bool first = true;
  while (std::cin >> a) {
    try {
      a = abs(a);
      if (!first) { 
        last_lcm = lcm(last_lcm, a);
      } else {
        last_lcm = a;
        first = false;
      }
      sum_sqr = add(sum_sqr, mp(a, a));
    } catch (const std::overflow_error &e){
      std::cerr << e.what() << "\n";
      return 1;
    }
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
  return add(a, b);
}

ll_t max_ll()
{
  return std::numeric_limits<ll_t>::max();
}

ll_t min_ll()
{
  return std::numeric_limits<ll_t>::min();
}

ll_t abs(ll_t a)
{
  if (min_ll() != a) {
    if (a < 0) {
      return -a;
    }
    return a;
  }
  throw 
    std::overflow_error("Overflow in abs");
}

ll_t lcm(ll_t a, ll_t b)
{           
  return (mp(a, b)) / gcd(a,b);
}

ll_t add(ll_t a, ll_t b)
{
  if (a < max_ll() - b){
    return a+b;
  }
  throw
    std::overflow_error("Overflow in add");
}

ll_t mp(ll_t a, ll_t b)
{
  if (max_ll() / a > b){
    return a*b;
  }
  throw
    std::overflow_error("Overflow in multiply");
}
