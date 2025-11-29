#include <iostream>

// Задача 2.1.
// Пусть определена структура книги Book с автором и названием книги
// Посчитать, сколько книг указанного автора находится в массиве
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

// Задача 2.2.
// Найти книгу с самым длинным названием. Вернуть указатель на неё
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

int main()
{
  const Book books[] = {
    {"123", "aff"},
    {"32gjgjfkfkfkuyf1", "affhgghg"},
    {"111", "b"}
  };
  const Book* lib[] = {
    &books[0],
    &books[1],
    &books[2]
  };
  size_t res = authored_by(lib, 3, "aff");
  std::cout << res << "\n";
  std::cout << longest_title(lib, 3)->title << "\n";
}
