#include <cstddef>
#include <algorithm>

//3. Перепишите заданный шаблон, используя алгоритмы стандартной библиотеки: замените циклы, обращения к std::accumulate и std::for_each на более подходящие алгоритмы
template< class It1, class It2, class It3, class C, class F >
size_t mistic_algoritm(It1 b, It1 e, It2 yab, It3 res, C cond, F bin) {
  auto yares = res;
  size_t f_id = 0;
  std::for_each(b, e,
   [&](const auto& curr) {
     if (cond(curr)) {
      *yab = curr;
      *res = bin(curr, *(b + f_id));
      ++yab, ++res, ++f_id;
   }});
  return std::accumulate(yares, res, size_t{0},
   [&](size_t count, const auto& elem) {
     return cond(elem) ? count + 1 : count;
   });
}

template< class It1, class It2, class It3, class C, class F >
size_t mistic_algoritm(It1 b, It1 e, It2 yab, It3 res, C cond, F bin) {
  auto yabend = std::copy_if(b, e, yab, cond);
  auto resend = std::transform(yab, yabend, b, res, bin);
  return std::count_if(res, resend, cond);
}

template< class It, class G, class CMP, class T >
void undercover_algorithm(It b, It e, G gen, CMP cmp, const T& v1, const T& v2) {
  auto it_1 = b, it_2 = b;
  for (auto it = b; it != e; it++) {
    *it = gen();
    it_1 = cmp(*it, *it_1) ? it : it_1;
    it_2 = cmp(*it_2, *it) ? it : it_2;
  }

  auto pred = [=, &v1, &v2](T& val) {
    return cmp(it_1 < it_2 ? v1 : v2, val);
  };

  if (it_2 < it_1) std::swap(it_2, it_1);
  for (; it_1 != it_2; ++it_1) if (!pred(*it_1)) break;
  if (it_1 == it_2) return;

  for (auto it = std::next(it_1); it != it_2; it++)
    if (pred(*it)) std::iter_swap(it, it_1++);
}

template< class It, class G, class CMP, class T >
void undercover_algorithm(It b, It e, G gen, CMP cmp, const T& v1, const T& v2) {
  std::generate(b, e, gen);
  auto it_1 = std::min_element(b, e, cmp);
  auto it_2 = std::max_element(b, e, cmp);

  auto pred = [=, &v1, &v2](T& val) {
    return cmp(it_1 < it_2 ? v1 : v2, val);
  };

  if (it_2 < it_1) std::swap(it_2, it_1);
  it_1 = std::find_if_not(it_1, it_2, pred);
  if (it_1 == it_2) return;

  std::partition(it_1, it_2, pred);
}