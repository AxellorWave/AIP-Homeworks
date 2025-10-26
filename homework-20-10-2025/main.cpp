#include <iostream>

using u_t = unsigned;
u_t get_progression_sum(u_t b, u_t q, u_t n);
u_t add(u_t a, u_t b);
u_t isAddErr(u_t res, u_t a, u_t b);
u_t sub(u_t a, u_t b);
u_t isSubErr(u_t res, u_t a, u_t b);
u_t mp(u_t a, u_t b);
u_t max_u();
u_t min_u();

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
