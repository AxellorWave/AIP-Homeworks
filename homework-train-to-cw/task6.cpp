#include <iostream>

struct Book {
  const char * title;
  const char * author;
};
struct Lib {
  size_t books;
  const Book * const * lib;
  const size_t * counts;
  const size_t * stocks;
};
/* Какие книги написал заданный автор (или авторы)?
 * Найти в библиотеке все книги, авторы которых
    соответствуют автору заданной книги
    или одному из авторов книг в заданном наборе
 * Поиск нужно выполнить для одной библиотеки
    и для нескольких
 * Автор один и тот же, если соответствующие указатели
    в Book равны
 * Функция должна вовзращать nullptr, если таких книг нет
 * Массивы с результатами должны располагаться во Free Store
 */
const Book ** copy(const Book * const * src, const Book ** dest, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    dest[i] = src[i];
  }
  return dest + k;
}

void cut(const Book *** books, size_t k)
{
  const Book ** new_books = new const Book * [k];
  copy(*books, new_books, k);
  delete[] * books;
  *books = new_books;
}

void extend(const Book *** books, size_t k, const Book * const * new_books, size_t new_k)
{
  const Book ** res_books = new const Book * [k + new_k];
  copy(new_books, copy(*books, res_books, k), new_k);
  delete[] *books;
  *books = res_books;
}

const Book ** same_author(
  size_t& out, // размер массива-результата
  const Lib & db, // библиотека для поиска
  const Book* book // книга-образец (из неё нужен автор)
)
{
  size_t count = 0;
  const Book ** res = new const Book * [db.books];
  for (size_t i = 0; i < db.books; ++i) {
    if (db.lib[i]->author == book->author) {
      res[count++] = db.lib[i];
    }
  }
  if (count == 0) {
    delete[] res;
    return nullptr;
  }
  cut(&res, count);
  out = count;
  return res;
}

const Book ** same_author(
  size_t& out,
  const Lib * libs, // библиотеки
  size_t l, // количество библиотек
  const Book* book
)
{
  const Book ** res = new const Book * [1];
  size_t count = 0;
  for (size_t i = 0; i < l; ++i) {
    size_t k = 0;
    const Book ** new_books = same_author(k, libs[i], book);
    extend(&res, count, new_books, k);
    delete[] new_books;
    count += k;
  }
  if (count == 0) {
    delete[] res;
    return nullptr;
  }
  return res;
}

bool isCorrectAuthor(const Book * const * match, size_t b, const Book * book)
{
  for (size_t i = 0; i < b; ++i) {
    if (match[i]->author == book->author) {
      return true;
    }
  }
  return false;
}

const Book ** same_author(
  size_t& out,
  const Lib & db,
  const Book* const* match, // книги-образцы
  size_t b // количество книг-образцов
)
{
  size_t count = 0;
  const Book ** res = new const Book * [db.books];
  for (size_t i = 0; i < db.books; ++i) {
    if (isCorrectAuthor(match, b, db.lib[i])) {
      res[count++] = db.lib[i];
    }
  }
  if (count == 0) {
    delete[] res;
    return nullptr;
  }
  cut(&res, count);
  out = count;
  return res;
}

const Book ** same_author(
  size_t& out,
  const Lib * libs,
  size_t l,
  const Book* const* match,
  size_t b
)
{
  const Book ** res = new const Book * [1];
  size_t count = 0;
  for (size_t i = 0; i < l; ++i) {
    size_t k = 0;
    const Book ** new_books = same_author(k, libs[i], match, b);
    extend(&res, count, new_books, k);
    delete[] new_books;
    count += k;
  }
  if (count == 0) {
    delete[] res;
    return nullptr;
  }
  return res;
}

/*
 * Сколько книг определённого автора (авторов) нужно изъять из библиотеки (библиотек)?
 * Посчитать копии списанных книг, авторы которых
    соответствуют автору заданной книги
    или одному из авторов книг в заданном наборе
 * Книга отправлена под списание, если она в наличии
    но под учётом не находится. Её количество копий в наличии
    добавляется к общему количеству под списание
 * Поиск нужно выполнить для одной библиотеки
    и для нескольких
 */
size_t space_after_out(const Lib & db, const Book* book);
size_t space_after_out(const Lib * libs, size_t l, const Book* book);
size_t space_after_out(const Lib & db, const Book* const* match, size_t b);
size_t space_after_out(const Lib * libs, size_t l, const Book* const* match, size_t b);

int main()
{}
