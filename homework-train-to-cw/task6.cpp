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

bool isCorrectAuthor(const Book * b1, const Book * b2)
{
  if (b1->author == b2->author) {
    return true;
  }
  return false;
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
    if (isCorrectAuthor(db.lib[i], book)) {
      res[count++] = db.lib[i];
    }
  }
  if (count == 0) {
    delete[] res;
    return nullptr;
  }
  try {
    cut(&res, count);
  } catch (const std::bad_alloc & e) {
    delete[] res;
    throw;
  }
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
  const Book ** res = nullptr;
  size_t count = 0;
  for (size_t i = 0; i < l; ++i) {
    size_t k = 0;
    const Book ** new_books = same_author(k, libs[i], book);
    try {
      extend(&res, count, new_books, k);
    } catch (const std::bad_alloc & e) {
      delete[] res;
      delete[] new_books;
      throw;
    }
    delete[] new_books;
    count += k;
  }
  out = count;
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
  try {
    cut(&res, count);
  } catch (const std::bad_alloc & e) {
    delete[] res;
    throw;
  }
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
    try {
      extend(&res, count, new_books, k);
    } catch (const std::bad_alloc & e) {
      delete[] res;
      delete[] new_books;
      throw;
    }
    delete[] new_books;
    count += k;
  }
  out = count;
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
bool isBookOut(size_t counts, size_t stocks)
{
  if (counts == 0 && stocks != 0) {
    return true;
  }
  return false;
}

size_t space_after_out(const Lib & db, const Book* book)
{
  size_t res = 0;
  for (size_t i = 0; i < db.books; ++i) {
    if (isCorrectAuthor(db.lib[i], book) && isBookOut(db.counts[i], db.stocks[i])) {
      res += db.stocks[i];
    }
  }
  return res;
}

size_t space_after_out(const Lib * libs, size_t l, const Book* book)
{
  size_t res = 0;
  for (size_t i = 0; i < l; ++i) {
    res += space_after_out(libs[i], book);
  }
}

size_t space_after_out(const Lib & db, const Book* const* match, size_t b)
{
  {
  size_t res = 0;
  for (size_t i = 0; i < db.books; ++i) {
    if (isCorrectAuthor(match, b, db.lib[i]) && isBookOut(db.counts[i], db.stocks[i])) {
      res += db.stocks[i];
    }
  }
  return res;
}
}

size_t space_after_out(const Lib * libs, size_t l, const Book* const* match, size_t b)
{
  size_t res = 0;
  for (size_t i = 0; i < l; ++i) {
    res += space_after_out(libs[i], match, b);
  }
}

/*
 * Сколько и каких книг определённого автора (авторов) нужно
    изъять из библиотеки (библиотек)?
 * Сформировать смету списанных книг, авторы которых
    соответствуют автору заданной книги
    или одному из авторов книг в заданном наборе
 */
// возвращает размер сметы

size_t * copy(size_t * src, size_t * dest, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    dest[i] = src[i];
  }
  return dest + k;
}

void cut(size_t ** counts, size_t k)
{
  size_t * res = new size_t[k];
  copy(*counts, res, k);
  delete[] *counts;
  *counts = res;
}

size_t out_list(
  // (результат) указатель на набор книг сметы
  const Book *** to_out,

  // (результат) указатель на массив из количеств каждой книги сметы
  // Т.е. в i-ом элементе массива записано количество соответствующих книг для изъятия
  const size_t ** out_each,
  const Lib & db, // библиотека
  const Book* book // книга-образец
)
{
  size_t count = 0;
  const Book ** out_books = nullptr;
  size_t * out_count = nullptr;
  try {
    out_books = new Book * [db.books];
    out_count = new size_t[db.books];
    for (size_t i = 0; i < db.books; ++i) {
      if (isCorrectAuthor(db.lib[i], book) && isBookOut(db.counts[i], db.stocks[i])) {
        out_books[count] = db.lib[i];
        out_count[count++] = db.stocks[i];
      }
    }
    cut(&out_books, count);
    cut(&out_count, count);
  } catch (const std::bad_alloc & e) {
    delete[] out_books;
    delete[] out_count;
    throw;
  }
  *to_out = out_books;
  *out_each = out_count;
  return count;
}

size_t out_list(
  // (результат) указатель на книги из сметы
  //   книги не должны повторяться, если одна книга
  //   соответствует нескольким образцам
  const Book *** to_out,

  // (результат) указатель на массив из количеств каждой книги сметы
  const size_t ** out_each,
  const Lib & db,
  const Book* const* match, // книги-образцы
  size_t b // количество книг
);

// возвращает массив с размерами смет
// количество смет равно количеству библиотек (l)
size_t * out_list(
  // (результат) указатель на массивы книг из сметы каждой библиотеки
  const Book **** to_out,

  // (результат) указатель на массив из
  //   массивов количеств книг в сметах
  const size_t *** out_each,
  const Lib * libs, // массив библиотек
  size_t l, // количество библиотек
  const Book* book
);
size_t * out_list(
  const Book **** to_out,
  const size_t *** out_each,
  const Lib * libs,
  size_t l,
  const Book* const* match,
  size_t b
);


int main()
{}
