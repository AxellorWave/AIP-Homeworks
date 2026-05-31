#include <cstddef>

// 3. Замените в шаблонах и функциях тип int на шаблонный параметр T. Повторите анализ

// Часть 1 

template<class T>
T* odd_even(const T* src, size_t s) {
  T* res = new T[s]; // бросает bad_alloc или исключение конструктора T
  for (size_t i = 0; i < s; i += 2) {
    res[i] = src[i + 1];   // присваивание T может бросить — res утечёт (нет catch)
    res[i + 1] = src[i];
  }
  return res;
}
// нет гарантии: если присваивание T бросит внутри цикла — res утечёт
// UB при нечётном s — остаётся

template<class T>
void odd_even(T* src, size_t s) {
  for (size_t i = 0; i < (s / 2) * 2; i += 2) {
    T buffer = src[i];       // конструктор копирования T может бросить
    src[i] = src[i + 1];     // присваивание T может бросить — src уже частично изменён
    src[i + 1] = buffer;
  }
}
// базовая гарантия: при исключении src частично изменён (для int была гарантия нет исключений)

template<class T>
void shift_right(T* src, size_t s) {
  T buffer = src[s - 1];      // конструктор копирования T может бросить — src не тронут, строгая
  for (size_t i = 0; i < s - 1; ++i) {
    src[s - i] = src[s - i - 1]; // присваивание T может бросить — src частично изменён
  }
  src[0] = buffer;
}
// базовая гарантия: при исключении в цикле src частично изменён (для int была гарантия нет исключений)
// UB баги остаются: i=0 → src[s], при s=0 size_t underflow

template<class T, class F>
size_t paring(T* begin, T* end, T* seq, F f) {
  size_t count = 0;
  while (begin != end) {
    T val;
    try {
      val = f(*begin);
    } catch (...) {
      return count;
    }
    *seq = val;  // присваивание T вне try — если бросит, исключение пробросится наружу
    ++count, ++begin, ++seq;
  }
  return count;
}
// базовая гарантия: *seq = val вне try — если присваивание T бросит, исключение не перехватывается

template<class T, class F>
T* transform(T* begin, size_t size, size_t& count, F f) {
  auto result = new T[size]; // бросает bad_alloc или исключение конструктора T
  count = 0;
  auto end = begin + size;
  while (begin != end) {
    const auto v = *begin;   // конструктор копирования T вне try — если бросит, result утечёт
    try {
      result[count] = f(v);
    } catch (...) {
      return result;
    }
    ++count, ++begin;
  }
  return result;
}
// нет гарантии: если конструктор копирования T в const auto v бросит — result утечёт (вне try)

// Часть 2

template<class T> bool is_required(T, T) noexcept;
template<class T> T promote(T*);

template<class T>
T* mutate(T* left, size_t left_k, const T* right, size_t right_k) {
  size_t size = left_k > right_k ? left_k : right_k;
  auto result = new T[size]; // бросает bad_alloc — строгая гарантия: ничего не изменено

  size_t id = 0;
  while (is_required(*left, *right) && (id < size)) {
    // копирование T для аргументов is_required вне try — если бросит, result утечёт
    try {
      result[id++] = promote(left++); // promote может бросить
    } catch (...) {
      delete[] result;
      throw;
    }
  }
  if (left_k >= right_k) return result;
  while (id < size) {
    if (!is_required(*left, *right)) {
      result[id] = *(right++); // присваивание T может бросить — result утечёт (нет catch)
    }
    ++id;
  }
  return result;
}
// нет гарантии: копирование T при передаче в is_required и присваивание T во втором цикле — вне try

template<class T> T propagate(T&);
template<class T> bool check(T) noexcept;

template<class T>
size_t extract(T* src, size_t size, T* dest, size_t& count) {
  count = 0;
  for (size_t i = 0; i < size; ++i) {
    *dest = propagate(*src); // propagate<T> может бросить; присваивание T тоже может бросить
    ++dest, ++count;
  }
  return count;
}
// базовая гарантия: нет динамической памяти — утечек нет, count отражает число успешных итераций
// логический баг: src не инкрементируется — остаётся
