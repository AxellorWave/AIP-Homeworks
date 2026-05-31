// Часть II. Алгоритмы стандартно библиотеки и функциональные объекты
// 1. По заданным описаниям функций составьте функциональные объекты с использованием std::bind и стандартных функцторов
// f(x: int, y: float) -> float = (x / 2.0f - y) ^ 3.14f
#include <functional>
#include <cmath>
using namespace std::placeholders;
using div_f = std::divides<float>;
using minus_f = std::minus<float>;
auto f = std::bind(powf,
  std::bind(minus_f{},
    std::bind(div_f{}, _1, 2.0f),
    _2),
  3.14f);

// g(x: bool, y: int, z: int) -> bool = (y > z) || x
using greater_i = std::greater<int>;
using or_b = std::logical_or<bool>;
auto g = std::bind(
  or_b{},
  std::bind(
    greater_i{}, _2, _3),
  _1);

// o(x: bool, y: bool, z: bool) -> bool = (x && y) || (y && z)
using and_b = std::logical_and<bool>;
auto o = std::bind(
  or_b{},
  std::bind(and_b{}, _1, _2),
  std::bind(and_b{}, _2, _3)
);

// r(x: int, y: int, z: int) -> int = x * y + z * y - 2 * z
using mul = std::multiplies<int>;
using plus = std::plus<int>;
using minus_i = std::minus<int>;
auto r = std::bind(
  minus_i{},
  std::bind(
    plus{},
    std::bind(mul{}, _1, _2),
    std::bind(mul{}, _3, _2)
  ),
  std::bind(mul{}, 2, _3)
);