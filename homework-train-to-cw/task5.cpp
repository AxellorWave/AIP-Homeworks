#include <iostream>

struct Book {
  const char * title;
  const char * author;
};

bool eq(const char * s1, const char * s2)
{
  if (s1 == s2) {
    return true;
  }
  if (s1 == nullptr || s2 == nullptr) {
    return false;
  }
  while (*s1 && *s2) {
    if (*s1 != *s2) {
      return false;
    }
    ++s1;
    ++s2;
  }
  return *s1 == '\0' && *s2 == '\0';
}

size_t authored_by(const Book * const * lib, size_t books, const char * author)
{
  size_t res = 0;
  for (size_t i = 0; i < books; ++i) {
    if (eq(lib[i]->author,author)) {
      ++res;
    }
  }
  return res;
}

size_t len(const char * str) {
  if (str == nullptr) {
    return 0;
  }
  size_t count = 0;
  for (size_t i = 0; str[i]; ++i) {
    ++count;
  }
  return count;
}

const Book * longest_title(const Book * const * lib, size_t books)
{
  size_t max_i = 0;
  for (size_t i = 0; i < books; ++i) {
    if (len(lib[max_i]->title) < len(lib[i]->title)) {
      max_i = i;
    }
  }  
  const Book * res = lib[max_i];
  return res;
}

// Задача 3.1.
// Пусть структура книжного каталога задана структурой Lib
// Количество различных наименований задаётся полем books
// Информация о книгах записана в массиве lib
// Количество каждой книги под учётом записано в массив counts на соответствующих позициях
// Количество каждой книги в наличии - в массиве stocks

// Вернуть массив из указателей на книги, которые закончились
// Массив с результатами должен располагаться во Free Store,
// ...но ссылаться на книги в каталоге. Количество книг записать в out
struct Lib {
  size_t books;
  const Book * const * lib;
  const size_t * counts;
  const size_t * stocks;
};

const Book ** out_of_stocks(const Lib & db, size_t & out)
{
  
}

// Задача 3.2.
// Найти хотя бы одного автора, чьих книг не осталось
// Если таких авторов нет - вернуть nullptr
// Есди таких авторов несколько - вернуть любого
// Учитывать только авторов книг каталога
const char * out_of_author(const Lib & db);

// Задача 3.3.
// Найти списанные книги (под учётом - 0), но оставшиеся в наличии
// Вернуть массив из указателей на эти книги, а количество этих книг
// ...записать в disc
const Book ** discarded(const Lib & db, size_t & disc);

// Задача 3.4.
// Найти всех авторов, чьих книг не осталось
// Вернуть массив из имён авторов и записать количество
// ...этих авторов в out
// Если таких авторов нет, то вернуть nullptr, а в out записать 0
const char ** out_of_authors(const Lib & db, size_t & out);
