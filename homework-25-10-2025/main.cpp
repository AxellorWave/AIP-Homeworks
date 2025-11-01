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
  ll_t a = 0, last_lcm = 1, sum_sqr = 0;
  while (std::cin >> a) {
    try {
      if (a == 0) {
        std::cerr << "Undefind lcm with 0";
        return 2;
      }
      a = abs(a);
      last_lcm = lcm(last_lcm, a);
      sum_sqr = add(sum_sqr, mp(a, a));
    } catch (const std::overflow_error &e){
      std::cerr << e.what() << "\n";
      return 1;
    }
  }

  if (std::cin.eof()) {
    if (last_lcm == 1 && a == 0) {
      std::cerr << "Entered 0 numbers";
      return 1;
    }
    std::cout << "LCM: " << last_lcm << "\n" ;
    std::cout << "SUM OF SQR: "<< sum_sqr << "\n";
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
