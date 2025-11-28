#include <iostream>

// Задача 1.1.
// Найти в массиве data все значения f
// ...и вернуть массив указателей на эти значения
// В found записать количество найденных элементов
// Массив с результатами должен располагаться во Free Store
const int ** find_all(const int * data, size_t s, int f, size_t & found)
{
  size_t count= 0;
  for (size_t i = 0; i < s; ++i) {
    if (data[i] == f) {
      ++count;
    }
  }

  const int ** res = new const int * [count];
  found = count;
  count = 0;
  for (size_t i = 0; i < s; ++i) {
    if (data[i] == f) {
      res[count] = &data[i];
      ++count;
    }
  }
  return res;
}

int main()
{
  size_t found;
  const int * data = new const int[5] {1, 2, 1, 5, 56};
  const int ** res = find_all(data, 5, 1, found);
  std::cout << found << "\n";
  for (size_t i = 0; i < found; ++i) {
    std::cout << res[i] << "\n";
  }
  delete[] res;
  delete[] data;
}

// Задача 1.2.
// В массиве из массивов data размером s найти самый длинный
// ...и самый короткий массив. Вернуть массив массивов,
// ...состоящий из копий этих массивов. Размеры массивов хранятся в sizes
// Результаты должны располагаться во Free Store
int ** find_big_and_tiny(const int * const * data, size_t s, const size_t * sizes)
{
  size_t max_i = 0;
  size_t min_i = 0;
  for (size_t i = 0; i < s; ++i) {
    if (sizes[i] < sizes[min_i]) {
      min_i = i;
    }
    if (sizes[i] > sizes[max_i]) {
      max_i = i;
    }
  }
  int ** res = new int * [2]; 
  int * max_arr = new int[sizes[max_i]];
  for (size_t j = 0; j < sizes[max_i]; ++j) {
    max_arr[j] = data[max_i][j];
  }
  res[0] = max_arr;
  int * min_arr = new int[sizes[min_i]];
  for (size_t j = 0; j < sizes[min_i]; ++j) {
    min_arr[j] = data[min_i][j];
  }
  res[1] = min_arr;
  return res;
}

// Задача 1.3.
// Построить новый массив из массивов, чередуя строки двух существующих
// На чётных позициях (начиная с 0) должны идти строки массива массивов aa1
// На нечётных позициях должны идти строки массива aa2
// Если строк не хватает в каком-то из массивов, то записывать nullptr
// Таким образом количество полученных строк не превышает удвоенного количества
// ...строк массива массивов с самым большим числом строк
// Количество строк и столбцов в каждом массиве массивов задано отдельно
// Массив массивов с результатами должен располагаться во Free Store и
// ...полностью скопировать данные оригинальных массивов
int ** merge_odd_even(const int * const * aa1, size_t n1, size_t m1,
 const int * const * aa2, size_t n2, size_t m2)
{
  size_t max_len = std::max(n1, n2);
  int ** res = new int * [max_len * 2];
  for (size_t i = 0; i < max_len * 2; ++i) {
    int * new_line = nullptr;
    if (i%2 == 0 && n1 > i / 2) {
      new_line = new int[m1];
      for (size_t j = 0; j < m1; ++j) {
        new_line[j] = aa1[i / 2][j];
      }
    } else if (i%2 != 0 && n2 > (i - 1) / 2) {
      new_line = new int[m2];
      for (size_t j = 0; j < m2; ++j) {
        new_line[j] = aa2[(i-1) / 2][j];
      }
    }
    res[i] = new_line;
  }  
  return res;
}
