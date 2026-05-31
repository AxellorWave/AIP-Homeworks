// 4. Составьте программу по описанию. Определите указанные типы и необходимые операторы.
// Используйте подходящие стандартные алгоритмы

// Пусть задана композиция из двух целых чисел.
// Определите для неё пользовательский конструктор, инициализирующий оба поля
// одним и тем же значением. Определите так же конструктор по умолчанию,
// инициализирующий поля нулём. Класс должен поддерживать копирование.
// Так же определите пользовательский оператор присваивания,
// который меняет значения полей на заданное.
// Считайте со стандартного ввода последовательность таких объектов:
// элементы пары разделены запятой, ввод заканчивается EOF.
// Сохраните их в любой последовательный контейнер.
// Выведите на стандартный вывод те пары, в которых нет чётных элементов.
// Для этого нужно перегрузить операторы ввода и вывода.
// Пары в выводе должны быть отсортированы по возрастанию суммы элементов пары.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>


struct DelimiterIO
{
  char exp;
};

struct DataStruct
{
  int a, b;
  DataStruct():
    a(0),
    b(0)
  {}
  DataStruct(int v):
    a(v),
    b(v)
  {}
  DataStruct& operator=(int v)
  {
    a = v;
    b = v;
    return *this;
  }
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (in && c != dest.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  in >> input.a >> DelimiterIO{','} >> input.b;
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << src.a << ',' << src.b;
  return out;
}

bool operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  return (lhs.a + lhs.b) < (rhs.a + rhs.b);
}

int main()
{
  std::vector< DataStruct > data;
  {
    while (!std::cin.eof())
    {
      using iit_t = std::istream_iterator< DataStruct >;
      std::copy(iit_t{std::cin}, iit_t{}, std::back_inserter(data));
      if (std::cin.fail())
      {
        std::cin.clear();
        std::streamsize max = std::numeric_limits< std::streamsize >::max();
        std::cin.ignore(max, '\n');
      }
    }
  }
  auto it = std::remove_if(data.begin(), data.end(),
    [](const DataStruct& p) { return p.a % 2 == 0 || p.b % 2 == 0; });
  data.erase(it, data.end());
  std::sort(data.begin(), data.end(), std::less< DataStruct >{});
  {
    using oit_t = std::ostream_iterator< DataStruct >;
    std::copy(data.begin(), data.end(), oit_t{std::cout, "\n"});
  }
}

// Пусть композиция содержит массив фиксированного размера из двух целых чисел.
// Определите пользовательский конструктор, который позволяет инициализировать
// элементы этого массива. Так же определите конструктор по умолчанию,
// инициализирующий массив нулями. Класс должен поддерживать копирование.
// Так же определите пользовательский оператор присваивания,
// который заполняет массив заданным числом.
// Считайте со стандартного ввода последовательность таких объектов:
// сначала идет количество не нулевых элементов (0, 1 или 2), затем сами элементы.
// Ввод заканчивается EOF. Сохраните объекты в любой последовательный контейнер.
// Выведите на стандартный вывод те элементы, в которых по итогу не оказалось
// нулевых элементов. Формат вывода соответствует вводу.
// Массивы в выводе должны быть отсортированы по убыванию суммы их элементов.

struct DataStruct2 {
  DataStruct2():
    arr_{0, 0}
  {}

  DataStruct2(int a, int b):
    arr_{a, b}
  {}

  DataStruct2& operator=(int v)
  {
    std::fill(arr_, arr_ + 2, v);
    return *this;
  }

  int arr_[2];
};

std::istream& operator>>(std::istream& in, DataStruct2& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct2 input;
  int count;
  in >> count;
  for (size_t i = 0; i < count; ++i) {
    in >> input.arr_[i];
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct2& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  size_t count = std::count_if(src.arr_, src.arr_ + 2, [](int v){ return v != 0; });
  out << count;
  for (size_t i = 0; i < count; ++i) {
    out << ' ' << src.arr_[i];
  }
  return out;
}

bool operator<(const DataStruct2& lhs, const DataStruct2& rhs)
{
  return (lhs.arr_[0] + lhs.arr_[1]) < (rhs.arr_[0] + rhs.arr_[1]);
}

int main()
{
  std::vector< DataStruct2 > data;
  {
    while (!std::cin.eof())
    {
      using iit_t = std::istream_iterator< DataStruct2 >;
      std::copy(iit_t{std::cin}, iit_t{}, std::back_inserter(data));
      if (std::cin.fail())
      {
        std::cin.clear();
        std::streamsize max = std::numeric_limits< std::streamsize >::max();
        std::cin.ignore(max, '\n');
      }
    }
  }
  auto it = std::remove_if(data.begin(), data.end(),
    [](const DataStruct2& p) { return p.arr_[0] == 0 || p.arr_[1] == 0; });
  data.erase(it, data.end());
  std::sort(data.begin(), data.end(), std::greater< DataStruct2 >{});
  {
    using oit_t = std::ostream_iterator< DataStruct2 >;
    std::copy(data.begin(), data.end(), oit_t{std::cout, "\n"});
  }
}
