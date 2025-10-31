#include <iostream>

using ll_t = long long;

ll_t gcd(ll_t a, ll_t b);
ll_t lcm(ll_t a, ll_t b);

int main()
{
  std::cout << gcd(155, 15) << "\n" << lcm(155, 15) << "\n";
}


ll_t gcd(ll_t a, ll_t b)
{
  while (a != 0 && b != 0){
	  if (a > b){
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