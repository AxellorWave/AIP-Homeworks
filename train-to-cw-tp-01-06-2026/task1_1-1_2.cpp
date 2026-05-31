#include <cstddef>

// Подготовка к проверочной работе по ТП
// Часть I. Безопасность относительно исключений
// 1. Проанализируйте заданные функции и шаблоны на безопасность относительно исключений
int* odd_even(const int* src, size_t s) {
  int* res = new int[s]; // бросает bad_alloc;
  for (size_t i = 0; i < s; i += 2) {
    res[i] = src[i + 1];   // UB при нечётном s: последняя итерация i=s-1, src[s] — выход за границу
    res[i + 1] = src[i];   // аналогично res[s] — выход за границу res
  }
  return res; // noexcept
}
//сторгая гарантия тк при исключении src остается. Может быть UB при s%2!=0

void odd_even(int* src, size_t s) {
  for (size_t i = 0; i < (s / 2) * 2; i += 2) { //(s/2)*2 отсекает нечётный хвост — выхода за границу нет
    int buffer = src[i];
    src[i] = src[i + 1];
    src[i + 1] = buffer;
  }
}
// гарантия - нет исключений: int операции noexcept


void shift_right(int* src, size_t s) {
  int buffer = src[s - 1];
  for (size_t i = 0; i < s - 1; ++i) {
    src[s - i] = src[s - i - 1];
  }
  src[0] = buffer;
}
// гарантия - нет исключений: все операции над int, исключений не бросает
// UB: при i=0 запись в src[s] — выход за границу; при s=0 size_t underflow в src[s-1]
// логический баг: src[1] никогда не перезаписывается — цикл должен начинаться с i=1 и условие i < s

template< class F > 
size_t paring(int* begin, int* end, int* seq, F f) 
{
  size_t count = 0;
  while (begin != end) {
    int val;
    try {
      val = f(*begin);
    } catch (...) {
      return count;
    }
    *seq= val;
    ++count, ++begin, ++seq;
  }
  return count;
}
//Базовая гарантия. Мможет быть исключение в val = f(*begin),
//но мы его ловим и передаем пользователю уже количество скопированных элементов

template< class F >
int* transform(int* begin,
  size_t size, size_t& count, F f)
{
  auto result = new int[size]; //bad_alloc
  count = 0;
  auto end = begin + size;
  while (begin != end) {
    const auto v = *begin;
    try {
      result[count] = f(v); // Исключение в f()
    } catch (...) {
      return result;
    }
    ++count, ++begin;
  }
  return result;
}
// Базовая гарантия если bad_alloc, то исключение проброситься дальше и
// старый массив останется в прежнем состоянии. Если в f() то передастся массив с count элементами


// 2. Проанализируйте функции с определениями на безопасность относительно исключений
bool is_required(int, int) noexcept;
int promote(int *);

int * mutate(int * left, size_t left_k, const int * right, size_t right_k) {
  size_t size = left_k > right_k ? left_k : right_k;
  auto result = new int[size]; // бросает bad_alloc — строгая гарантия: ничего не изменено

  size_t id = 0;
  while (is_required(*left, *right) && (id < size)) { // is_required — noexcept
    try {
      result[id++] = promote(left++); // promote может бросить
    } catch (...) {
      delete[] result; // утечки нет, но promote мог изменить данные по указателю
      throw;
    }
  }
  if (left_k >= right_k) return result;
  while (id < size) {
    if (!is_required(*left, *right)) {
      result[id] = *(right++);
    }
    ++id;
  }
  return result;
}
// базовая гарантия: утечек нет, но promote мог изменить данные до броска исключения

int propagate(int &);
bool check(int) noexcept;

size_t extract(int * src, size_t size, int * dest, size_t & count) {
  count = 0;
  for (size_t i = 0; i < size; ++i) {
    *dest = propagate(*src); // propagate может бросить — исключение пробрасывается наружу
    ++dest, ++count;         // логический баг: src не инкрементируется — всегда propagate src[0]
  }
  return count;
}
// базовая гарантия: нет динамической памяти — утечек нет, count отражает число успешных итераций
