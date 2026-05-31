#include <cstddef>
#include <vector>

//2. Определите типы-функторы, соответствующие лямбда выражениям и создайте эквивалентный лямбдам функциональные объекты
std::vector< int > src{1, 2, 3, 4, 5};
auto result = src.end();
int pattern = 3;
size_t deep = 5;
auto cmp = std::less< int >{};
auto find = [=, &result, &deep](auto begin) {
  auto found = [&, cmp](auto v) {
    auto ret = (!cmp(*v, pattern) && !cmp(pattern, *v));
    result = ret ? v : result;
    return ret;
  };
  while (--deep && !found(begin++));
};

using iter = std::vector<int>::iterator;
struct Found {
  Found(iter& result, int& pattern, std::less<int> cmp):
    result_(result), pattern_(pattern), cmp_(cmp)
  {}

  template<class T>
  auto operator()(T v) const {
    auto ret = (!cmp_(*v, pattern_) && !cmp_(pattern_, *v));
    result_ = ret ? v : result_;
    return ret;
  }
  iter& result_;
  int& pattern_;
  std::less<int> cmp_;
};

struct Find {
  Find(iter& result, int pattern, size_t& deep, std::less< int > cmp):
    result_(result),
    pattern_(pattern),
    deep_(deep),
    cmp_(cmp)
  {}

  template<class T>
  auto operator()(T begin)
  {
    auto found = Found{result_, pattern_, cmp_};
    while (--deep_ && !found(begin++));
  }

  iter& result_;
  int pattern_;
  size_t& deep_;
  std::less< int > cmp_;
};

auto find = Find{result, pattern, deep, cmp};



std::vector< int > src{1, 2, 3, 4, 5, 6, 7};
size_t fixes = 2;
int mod = 2;
auto fix = [=, &fixes](auto start, auto finish) {
  auto increased = [=](auto v) {
    auto ret = !(*v % mod);
    *v = ret ? (*v + 1) : *v;
    return ret;
  };
  while ((start != finish) && fixes) {
    if (increased(start)) --fixes;
    ++start;
  }
};

struct Increased {
  Increased(int mod):
  mod_(mod)
  {}

  template<class T>
  auto operator()(T v)
  {
    auto ret = !(*v % mod_);
    *v = ret ? (*v + 1) : *v;
    return ret;
  }

  int mod_;
};

struct Fix {
  Fix(size_t& fixes, int mod):
    fixes_(fixes),
    mod_(mod)
  {}

  template< class T, class V >
  auto operator()(T start, V finish)
  {
    auto increased = Increased{mod_};
    while ((start != finish) && fixes_) {
      if (increased(start)) --fixes_;
      ++start;
    }
  }

  size_t& fixes_;
  int mod_;
};

auto fix = Fix{fixes, mod};