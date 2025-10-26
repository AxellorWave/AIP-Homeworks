#include <iostream>
#include <limits>

using u_t = unsigned;
u_t get_progression_sum(u_t b, u_t q, u_t n);
u_t add(u_t a, u_t b);
bool isAddErr(u_t res, u_t a, u_t b);
u_t mp(u_t a, u_t b);
bool isMpErr(u_t res, u_t a, u_t b);
u_t max_u();

int main()
{
    std::cout << get_progression_sum(2,2,3) << "\n";
}

u_t get_progression_sum(u_t b, u_t q, u_t n)
{
    u_t sum = b;
    while (n > 1) {
        b *= q;
        sum += b;
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
    if (a > max_u() - b){
        return 0;
    }
    return a+b;
}

bool isSumErr(u_t res, u_t a, u_t b)
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