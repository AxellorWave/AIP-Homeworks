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
const Book ** copy()

void cut(const Book *** books, size_t k)
{
  const Book ** new_books = new const Book * [k];

}

const Book ** same_author(
  size_t& out, // размер массива-результата
  const Lib & db, // библиотека для поиска
  const Book* book // книга-образец (из неё нужен автор)
)
{
  size_t count = 0;
  const char * author = book->author;
  const Book ** res = new const Book * [db.books];
  for (size_t i = 0; i < db.books; ++i) {
    if (db.lib[i]->author == author) {
      res[count++] = db.lib[i];
    }
  }
}
const Book ** same_author(
  size_t& out,
  const Lib * libs, // библиотеки
  size_t l, // количество библиотек
  const Book* book
);
const Book ** same_author(
  size_t& out,
  const Lib & db,
  const Book* const* match, // книги-образцы
  size_t b // количество книг-образцов
);
const Book ** same_author(
  size_t& out,
  const Lib * libs,
  size_t l,
  const Book* const* match,
  size_t b
);

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
