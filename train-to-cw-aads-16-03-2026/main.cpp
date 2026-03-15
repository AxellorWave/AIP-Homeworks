#include <iostream>

template< class T >
struct BiList {
  T val;
  BiList< T >* next, * prev;
};
template< class T >
struct Vector {
  T* data;
  size_t size, cap;
};

// 1. Посчитать количество элементов данных
template< class T >
size_t size(const Vector< const BiList< T > * > v)
{
  size_t res = 0;
  for (size_t i = 0; i < v.size; ++i) {
    const BiList< T > * curr = v.data[i];
    while (curr) {
      ++res;
      curr = curr->next;
    }
  }
  return res;
}

// 2. Посчитать количество элементов,
// ...удовлетворяющих заданному условию
// ...и сохранить количество таких элементов
template< class T, class P >
size_t count_if(const Vector< const BiList< T > * > v, P p)
{
  size_t res = 0;
  for (size_t i = 0; i < v.size; ++i) {
    const BiList< T > * curr = v.data[i];
    while (curr) {
      if(p(curr->val)) {
        ++res;
      }
      curr = curr->next;
    }
  }
  return res;
}

// 3. Посчитать количество элементов данных
// ...и сохранить размеры каждого списка
template< class T >
size_t size(const Vector< const BiList< T > * > v, BiList< size_t > ** sizes)
{
  size_t res = 0;
  size_t * temp_sizes = new size_t[v.size];
  for (size_t i = 0; i < v.size; ++i) {
    size_t temp = 0;
    const BiList< T > * curr = v.data[i];
    while (curr) {
      ++temp;
      curr = curr->next;
    }
    temp_sizes[i] = temp;
    res += temp;
  }
  *sizes = temp_sizes;
  return res;
}

// 4. Посчитать количество элементов,
// ...удовлетворяющих заданному условию
// ...и сохранить количество таких элементов
// ...в каждом списке
template< class T, class P >
size_t count_if(const Vector< const BiList< T > * > v, BiList< size_t > ** sizes, P p)
{
  size_t res = 0;
  size_t * temp_sizes = new size_t[v.size];
  for (size_t i = 0; i < v.size; ++i) {
    size_t temp = 0;
    const BiList< T > * curr = v.data[i];
    while (curr) {
      if (p(curr->val)) {
        ++temp;
      }
      curr = curr->next;
    }
    temp_sizes[i] = temp;
    res += temp;
  }
  *sizes = temp_sizes;
  return res;
}

// 5. Посчитать количество элементов,
// ...которые удовлетворяют всем условиям
// ...и сохранить количество таких элементов
// ...в каждом списке
template<class T, class P>
bool check(const T& v, P cond)
{
  return cond(v);
}

template< class T , class P, class ... P_s>
bool check(const T & v, P cond, P_s ... conds)
{
  return cond(v) && check(v, conds...);
}

template< class T, class ... P_S >
size_t count_if_all(const Vector< const BiList< T > * > v, BiList< size_t > ** sizes, P_S ... pi)
{
  size_t res = 0;
  size_t * temp_sizes = new size_t[v.size];
  for (size_t i = 0; i < v.size; ++i) {
    size_t temp = 0;
    const BiList< T > * curr = v.data[i];
    while (curr) {
      if (check(curr->val, pi...)) {
        ++temp;
      }
      curr = curr->next;
    }
    temp_sizes[i] = temp;
    res += temp;
  }
  *sizes = temp_sizes;
  return res;
}

// 6. Найти элементы, удовлетворяющие заданному условию
// ...и сформировать список из указателей на такие элементы
template< class T, class P >
BiList< const BiList< T > * > * find_if(const Vector< const BiList< T > * > v, P p)
{
  BiList< const BiList< T > * > * head = nullptr;
  BiList< const BiList< T > * > * tail = nullptr;
  for (size_t i = 0; i < v.size; ++i) {
    const BiList< T > * curr = v.data[i];
    while (curr) {
      if (p(curr->val)) {
        BiList< const BiList< T > * > * new_node = new BiList< const BiList< T > * > {curr, nullptr, tail};
        if (tail) {
          tail->next = new_node;
        } else {
          head = new_node;
        }
        tail = new_node;
      }
      curr = curr->next;
    }
  }
  return head;
}

// 7. Освободить память, занимаемую структурой
template< class T >
void clear(Vector< BiList< T > * > v)
{
  for (size_t i = 0; i < v.size; ++i) {
    BiList< T > * curr = v.data[i];
    while (curr) {
      BiList< T > * next = curr->next;
      delete curr;
      curr = next;
    }
  }
}

// 8. Удалить из структуры списки,
// ...в которых хотя бы один элемент списка
// ...удовлетворяет заданному условию
// Вернуть количество удаленных элементов данных (!)
template< class T >
void delete_list(BiList< T > * head)
{
  while (head) {
    BiList< T > * next = head->next;
    delete head;
    head = next;
  }
}

template< class T, class P >
size_t remove_if_any_in_list(Vector< BiList< T > * > v, P p)
{
 size_t res = 0;
  for (size_t i = 0; i < v.size; ++i) {
    BiList< T > * curr = v.data[i];
    bool to_delete = false;
    while (curr) {
      BiList< T > * next = curr->next;
      if (p(curr->val)) {
        to_delete = true;
        ++res;
      } else if (to_delete) {
        ++res;
      }
      curr = next;
    }
    if (to_delete) {
      delete_list(v.data[i]);
    }
  }
  return res; 
}

// 9. Удалить из структуры элементы,
// ...которые удовлетворяют заданному условию
// Вернуть количество этих элементов
template< class T >
void delete_node(BiList< T > * node)
{
  BiList< T > * prev = node->prev;
  BiList< T > * next = node->next;
  delete node;
  if (prev) {
    prev->next = next;
  }
  if (next) {
    next->prev = prev;
  }
}

template< class T, class P >
size_t remove_if(Vector< BiList< T > * > v, P p)
{
  size_t res = 0;
  for (size_t i = 0; i < v.size; ++i) {
    BiList< T > * curr = v.data[i];
    while (curr) {
      BiList< T > * next = curr->next;
      if (p(curr->val)) {
        delete_node(curr);
        ++res;
      }
      curr = next;
    }
  }
  return res;
}

// 10. Выполнить глубокое копирование структуры данных
template< class T >
void clear(BiList< T > * h)
{
  while (h) {
    BiList< T > * next = h->next;
    delete h;
    h = next;
  }
  
}

template< class T >
BiList< T > * copy_list(const BiList< T > * h)
{
  if (!h) {
    return nullptr;
  }
  BiList< T > * head = new BiList< T > {h->val, nullptr, nullptr};
  BiList< T > * tail = head;
  try {
    h = h->next;
    while (h) {
      BiList< T > * new_node = new BiList< T > {h->val, tail, nullptr};
      tail->next = new_node;
      tail = new_node;
      h = h->next;
    }
  } catch (...) {
    clear(head);
  }
  return head;
}

template< class T >
Vector< BiList< T > * > copy(const Vector< const BiList< T > * > v)
{
  Vector< BiList< T > * > res {nullptr, 0, v.size};
  res.data = new BiList< T > * [v.size];
  try {
    for (size_t i = 0; i < v.size; ++i) {
      res.data[i] = copy_list(v.data[i]);
      ++res.size;    
    }
    return res;
  } catch (...) {
    delete[] res.data;
    throw;
  }
}

// 11. Выполнить глубокое копирования структуры данных,
// ...оставляя только элементы, удовлетворяющие заданному условию
template< class T, class P >
BiList< T > * copy_list(const BiList< T > * h, P p)
{
  if (!h) {
    return nullptr;
  }
  while (!p(h->val)) {
    h = h->next;
  }
  BiList< T > * head = new BiList< T > {h->val, nullptr, nullptr};
  BiList< T > * tail = head;
  try {
    h = h->next;
    while (h) {
      if (p(h->val)) {
        BiList< T > * new_node = new BiList< T > {h->val, tail, nullptr};
        tail->next = new_node;
        tail = new_node;
      }
      h = h->next;
    }
  } catch (...) {
    clear(head);
  }
  return head;
}

template< class T, class P >
Vector< BiList< T > * > copy_if(const Vector< const BiList< T > * > v, P p)
{
  Vector< BiList< T > * > res {new BiList< T > * [v.size], 0, v.size};
  try {
    for (size_t i = 0; i < v.size; ++i) {
      res.data[i] = copy_list(v.data[i], p);
      ++res.size;    
    }
    return res;
  } catch (...) {
    delete[] res.data;
    throw;
  }
}

// 12. Преобразовать структуру данных в вектор
template< class T >
Vector< T > convert_to_vector(const Vector< const BiList< T > * > v)
{
  Vector< T > res {new T[size(v)], 0, size(v)};
  try {
    for (size_t i = 0; i < v.size; ++i) {
      const BiList< T > * curr = v.data[i];
      while (curr) {
        res.data[res.size] = curr->val;
        ++res.size;
        curr = curr->next;
      }
    }
  } catch (...) {
    delete[] res.data;
    throw;
  }
  return res;
}

// 13. Преобразовать структуру данных в список
template< class T >
BiList< T > * convert_to_list(const Vector< const BiList< T > * > v);

// 14. Преобразовать структуру даннных в список,
// ...перенеся узлы из оригинальной структуры
template< class T >
BiList< T > * moved_convert_to_list(Vector< BiList< T > * > v);

// 15. Проверить структуру данных:
// ...убедиться, что в векторе нет списков с общими элементами
template< class T >
bool is_different_lists(const Vector< const BiList< T > * > v);

// 16. Исправить структуру данных:
// ...убрать пустые списки из вектора
// Вернуть количество таких списков
template< class T >
size_t remove_empty(Vector< const BiList< T > * > & v);
