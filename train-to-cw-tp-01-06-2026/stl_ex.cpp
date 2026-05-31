#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>
// ======== std::transform ========
// возвращает: итератор за последним записанным элементом выходного диапазона
void ex_transform() {
  std::vector<int> src{1, 2, 3, 4};
  std::vector<int> dst(4);
  // унарный: каждый элемент умножить на 2
  auto end = std::transform(src.begin(), src.end(), dst.begin(),
    [](int x) { return x * 2; });
  // end == dst.end(), dst = {2, 4, 6, 8}
  std::vector<int> src2{10, 20, 30, 40};
  std::vector<int> dst2(4);
  // бинарный: попарно сложить два диапазона
  auto end2 = std::transform(src.begin(), src.end(), src2.begin(), dst2.begin(),
    [](int a, int b) { return a + b; });
  // end2 == dst2.end(), dst2 = {11, 22, 33, 44}
}
// ======== std::find / std::find_if / std::find_if_not ========
// возвращает: итератор на найденный элемент, или end если не нашёл
void ex_find() {
  std::vector<int> v{1, 2, 3, 4, 5};
  // find: по значению
  auto it = std::find(v.begin(), v.end(), 3);
  // it указывает на элемент 3; если нет — it == v.end()
  // find_if: по предикату — найти первое чётное
  auto it2 = std::find_if(v.begin(), v.end(),
    [](int x) { return x % 2 == 0; });
  // it2 указывает на 2; если нет — it2 == v.end()
  // find_if_not: найти первый не удовлетворяющий предикату
  auto it3 = std::find_if_not(v.begin(), v.end(),
    [](int x) { return x % 2 == 0; });
  // it3 указывает на 1; если нет — it3 == v.end()
}
// ======== std::copy / std::copy_if ========
// возвращает: итератор за последним скопированным элементом в выходном диапазоне
void ex_copy() {
  std::vector<int> src{1, 2, 3, 4, 5, 6};
  std::vector<int> dst;
  // copy_if: скопировать только чётные
  auto new_end = std::copy_if(src.begin(), src.end(), std::back_inserter(dst),
    [](int x) { return x % 2 == 0; });
  // new_end — итератор за последним скопированным в dst
  // dst = {2, 4, 6}
}
// ======== std::sort / std::stable_sort ========
// возвращает: void (ничего не возвращают)
void ex_sort() {
  std::vector<int> v{5, 2, 4, 1, 3};
  std::sort(v.begin(), v.end());
  // v = {1, 2, 3, 4, 5}
  std::sort(v.begin(), v.end(), std::greater<int>{});
  // v = {5, 4, 3, 2, 1}
  std::stable_sort(v.begin(), v.end());
  // сохраняет порядок равных элементов
}
// ======== std::partition / std::stable_partition ========
// возвращает: итератор на начало второй части (первый элемент НЕ удовл. предикату)
void ex_partition() {
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  auto mid = std::partition(v.begin(), v.end(),
    [](int x) { return x % 2 == 0; });
  // [v.begin(), mid) — чётные; [mid, v.end()) — нечётные
  auto mid2 = std::stable_partition(v.begin(), v.end(),
    [](int x) { return x % 2 == 0; });
  // mid2 — то же, порядок внутри частей сохранён: {2,4,6,1,3,5}
}
// ======== std::remove / std::remove_if ========
// возвращает: итератор на начало "мусорного" хвоста (новый логический конец)
// ВАЖНО: сам не удаляет — нужен .erase() после
void ex_remove() {
  std::vector<int> v{1, 2, 3, 2, 4, 2, 5};
  auto new_end = std::remove(v.begin(), v.end(), 2);
  // [v.begin(), new_end) = {1, 3, 4, 5}; [new_end, v.end()) — мусор
  v.erase(new_end, v.end());
  std::vector<int> v2{1, 2, 3, 4, 5, 6};
  auto new_end2 = std::remove_if(v2.begin(), v2.end(),
    [](int x) { return x % 2 == 0; });
  // [v2.begin(), new_end2) = {1, 3, 5}
  v2.erase(new_end2, v2.end());
}
// ======== std::for_each ========
// возвращает: переданную функцию (fn) — можно использовать если у неё есть состояние
void ex_for_each() {
  std::vector<int> v{1, 2, 3, 4, 5};
  int sum = 0;
  std::for_each(v.begin(), v.end(),
    [&sum](int x) { sum += x; });
  // sum == 15
}
// ======== std::accumulate ========
// возвращает: итоговое накопленное значение (не итератор)
void ex_accumulate() {
  std::vector<int> v{1, 2, 3, 4, 5};
  int sum = std::accumulate(v.begin(), v.end(), 0);
  // sum == 15
  int prod = std::accumulate(v.begin(), v.end(), 1,
    std::multiplies<int>{});
  // prod == 120
}
// ======== std::count_if ========
// возвращает: количество элементов (difference_type, обычно ptrdiff_t) — не итератор
void ex_count_if() {
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  auto cnt = std::count_if(v.begin(), v.end(),
    [](int x) { return x % 2 == 0; });
  // cnt == 3
}
// ======== std::generate ========
// возвращает: void (ничего не возвращает)
void ex_generate() {
  std::vector<int> v(5);
  int n = 0;
  std::generate(v.begin(), v.end(),
    [&n]() { return n++; });
  // v = {0, 1, 2, 3, 4}
}
// ======== std::min_element / std::max_element ========
// возвращает: итератор на минимальный/максимальный элемент
void ex_minmax() {
  std::vector<int> v{3, 1, 4, 1, 5, 9, 2};
  auto min_it = std::min_element(v.begin(), v.end());
  // min_it указывает на 1
  auto max_it = std::max_element(v.begin(), v.end());
  // max_it указывает на 9
}
