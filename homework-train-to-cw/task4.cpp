#include <iostream>

// Задача 2.1.
// Пусть определена структура книги Book с автором и названием книги
// Посчитать, сколько книг указанного автора находится в массиве
struct Book {
  const char * title;
  const char * author;
};

size_t authored_by(const Book * const * lib, size_t books, const char * author)
{
  size_t res = 0;
  for (size_t i = 0; i < books; ++i) {
    if (lib[i]->author == author) {
      ++res;
    }
  }
  return res;
}
int main()
{
  const Book books[] = {
    {"123", "aff"},
    {"321", "adf"},
    {"111", "b"}
  };
  const Book* lib[] = {
    &books[0],
    &books[1],
    &books[2]
  };
  size_t res = authored_by(lib, 3, "aff");
  std::cout << res << "\n";
}

// Задача 2.2.
// Найти книгу с самым длинным названием. Вернуть указатель на неё
const Book * longest_title(const Book * const * lib, size_t books);
