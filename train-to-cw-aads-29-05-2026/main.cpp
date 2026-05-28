#include <cstddef>
#include <utility>

// Вектор
template< class T >
struct Vec
{
  T* data;
  size_t size, cap;
};

// Список
template< class T >
struct List
{
  List< T >* next;
  T val;
};

// Хеш-таблица с закрытой адресацией
// Разрешение коллизий методом цепочек
// Хешируемый ключ - K, хранимое значение - V
template< class K, class V >
struct Table
{
  Vec< List< std::pair< K, V > >* > tb;
};

// Бинарное дерево
// Параметр K - ключ дерева, V - значение
template< class K, class V >
struct Tree
{
  Tree< K, V >*lhs, *rhs;
  Tree< K, V >* parent;
  std::pair< K, V > val;
};

template< class T, class U, class W >
using ds_t = Tree< T, Table< U, W > >;

// Полагая, что бинарное дерево организовано как дерево поиска,
// а все данные располагаются во Free Store
// решите ниже описанные задачи
// Считайте, что функциональные объекты (типа CMP, HASH, EQ)
// предоставляют строгую гарантию безопасности и не меняют передаваемых
// параметров

// Освободить память, занимаемую структурой
template< class T >
void clear(List< T >* root) noexcept
{
  if (!root)
  {
    return;
  }
  clear(root->next);
  delete root;
}

template< class U, class W >
void clear(Table< U, W >& table) noexcept
{
  for (size_t i = 0; i < table.tb.cap; ++i)
  {
    clear(table.tb.data[i]);
  }
  delete[] table.tb.data;
}

template< class T, class U, class W >
void clear(ds_t< T, U, W >* root) noexcept
{
  if (!root)
  {
    return;
  }
  clear(root->lhs);
  clear(root->rhs);
  clear(root->val.second);
  delete root;
}

// Освободить память, занимаемую структурой ИТЕРАТИВНО
// Подсказка: с помощью поворотов превратите дерево в список
template< class K, class V >
Tree< K, V >* rotateRight(Tree< K, V >* node)
{
  Tree< K, V >* y = node->lhs;
  Tree< K, V >* tmp = y->rhs;
  y->rhs = node;
  y->parent = node->parent;
  if (node->parent && node->parent->lhs == node)
  {
    node->parent->lhs = y;
  }
  else if (node->parent && node->parent->rhs == node)
  {
    node->parent->rhs = y;
  }
  node->parent = y;
  node->lhs = tmp;
  if (tmp)
  {
    tmp->parent = node;
  }
  return y;
}

template< class K, class V >
Tree< K, V >* convertToLine(Tree< K, V >* root)
{
  Tree< K, V >* curr = root;
  Tree< K, V >* res = root;
  while (curr)
  {
    if (curr->lhs)
    {
      curr = rotateRight(curr);
      if (!curr->parent)
      {
        res = curr;
      }
    }
    else
    {
      curr = curr->rhs;
    }
  }
  return res;
}

template< class T >
void clearit(List< T >* root) noexcept
{
  while (root)
  {
    List< T >* next = root->next;
    delete root;
    root = next;
  }
}

template< class U, class W >
void clearit(Table< U, W >& table) noexcept
{
  for (size_t i = 0; i < table.tb.cap; ++i)
  {
    clearit(table.tb.data[i]);
  }
  delete[] table.tb.data;
}

template< class T, class U, class W >
void clearit(ds_t< T, U, W >* root) noexcept
{
  root = convertToLine(root);
  while (root)
  {
    ds_t< T, U, W >* next = root->rhs;
    clearit(root->val.second);
    delete root;
    root = next;
  }
}

// Добавить узел дерева с пустой хеш-таблицей
// Вернуть указатель на этот узел
// Параметры пустой хеш-таблицы определяются реализацией
// Поддержите строгую гарантию
template< class U, class W >
Table< U, W > make_table()
{
  Table< U, W > table;
  table.tb.data = new List< std::pair< U, W > >*[10]{};
  table.tb.size = 0;
  table.tb.cap = 10;
  return table;
}

template< class T, class U, class W, class CMP >
ds_t< T, U, W >* make_node(ds_t< T, U, W >* root, T key, CMP cmp)
{
  ds_t< T, U, W >* curr = root;
  ds_t< T, U, W >* parent = nullptr;
  bool is_left = true;
  while (curr)
  {
    parent = curr;
    if (cmp(key, curr->val.first))
    {
      curr = curr->lhs;
      is_left = true;
    }
    else if (cmp(curr->val.first, key))
    {
      curr = curr->rhs;
      is_left = false;
    }
    else
    {
      return curr;
    }
  }

  ds_t< T, U, W >* node = new ds_t< T, U, W >{};
  try
  {
    node->val.second = make_table< U, W >();
    node->val.first = key;
  }
  catch (...)
  {
    delete node;
    throw;
  }
  node->parent = parent;
  if (parent)
  {
    if (is_left)
    {
      parent->lhs = node;
    }
    else
    {
      parent->rhs = node;
    }
  }

  return node;
}

// Вставить элемент в хеш-таблицу соответствующего узла дерева (создать узел при необходимости)
// Вернуть указатель на узел и номер слота
// Хеш-таблица не расширяется, новые элементы вставляются в конец цепочки
// Поддержите строгую гарантию
template< class T, class U, class W, class CMP, class HASH, class EQ >
std::pair< ds_t< T, U, W >*, size_t >
insert(ds_t< T, U, W >* root, T key, CMP cmp, U tkey, HASH h, EQ eq, W val)
{
  bool is_new = (find_node(root, key, cmp) == nullptr);
  ds_t< T, U, W >* node = make_node(root, key, cmp);
  try
  {
    size_t index = h(tkey) % node->val.second.tb.cap;
    List< std::pair< U, W > >* curr = node->val.second.tb.data[index];
    List< std::pair< U, W > >* prev = nullptr;
    while (curr && !eq(curr->val.first, tkey))
    {
      prev = curr;
      curr = curr->next;
    }
    if (!curr)
    {
      List< std::pair< U, W > >* new_node = new List< std::pair< U, W > >;
      new_node->val = {tkey, val};
      new_node->next = nullptr;
      if (prev)
      {
        prev->next = new_node;
      }
      else
      {
        node->val.second.tb.data[index] = new_node;
        ++node->val.second.tb.size;
      }
    }
    else
    {
      curr->val.second = val;
    }
    return {node, index};
  }
  catch (...)
  {
    if (is_new)
    {
      if (node->parent)
      {
        if (node->parent->lhs == node)
        {
          node->parent->lhs = nullptr;
        }
        else
        {
          node->parent->rhs = nullptr;
        }
      }
      clear(node->val.second);
      delete node;
    }
    throw;
  }
}

// Подсчитать значения в хеш-таблицах, равные заданному
// Поддержите строгую гарантию
template< class T, class U, class W >
struct dsIT
{
  ds_t< T, U, W >* curr_tree;
  size_t curr_i;
  List< std::pair< U, W > >* curr_list;
};

template< class T, class U, class W >
bool hasNext(dsIT< T, U, W > it)
{
  return it.curr_tree != nullptr;
}

template< class T, class U, class W >
ds_t< T, U, W >* next(ds_t< T, U, W >* node) noexcept
{
  if (node->rhs)
  {
    node = node->rhs;
    while (node->lhs)
    {
      node = node->lhs;
    }
    return node;
  }
  while (node->parent && node->parent->rhs == node)
  {
    node = node->parent;
  }
  return node->parent;
}

template< class T, class U, class W >
dsIT< T, U, W > getValidNode(ds_t< T, U, W >* node)
{
  while (node && node->val.second.tb.size == 0)
  {
    node = next(node);
  }
  if (!node)
  {
    return {nullptr, 0, nullptr};
  }
  size_t i = 0;
  while (i < node->val.second.tb.cap && !node->val.second.tb.data[i])
  {
    ++i;
  }
  return {node, i, node->val.second.tb.data[i]};
}

template< class T, class U, class W >
dsIT< T, U, W > begin(ds_t< T, U, W >* root)
{
  while (root && root->lhs)
  {
    root = root->lhs;
  }
  return getValidNode(root);
}

template< class T, class U, class W >
dsIT< T, U, W > next(dsIT< T, U, W > it)
{
  if (it.curr_list->next)
  {
    return {it.curr_tree, it.curr_i, it.curr_list->next};
  }
  size_t next_i = it.curr_i + 1;
  while (next_i < it.curr_tree->val.second.tb.cap && !it.curr_tree->val.second.tb.data[next_i])
  {
    ++next_i;
  }
  if (next_i < it.curr_tree->val.second.tb.cap)
  {
    return {it.curr_tree, next_i, it.curr_tree->val.second.tb.data[next_i]};
  }
  return getValidNode(next(it.curr_tree));
}

template< class T, class U, class W, class EQ >
size_t count(ds_t< T, U, W >* root, W val, EQ eq)
{
  size_t res = 0;
  dsIT< T, U, W > it = begin(root);
  while (hasNext(it))
  {
    if (eq(it.curr_list->val.second, val))
    {
      ++res;
    }
    it = next(it);
  }
  return res;
}

template< class T, class U, class W, class EQ >
size_t count_rec(ds_t< T, U, W >* root, W val, EQ eq)
{
  if (!root)
  {
    return 0;
  }
  size_t res = count_rec(root->lhs, val, eq) + count_rec(root->rhs, val, eq);
  for (size_t i = 0; i < root->val.second.tb.cap; ++i)
  {
    for (List< std::pair< U, W > >* node = root->val.second.tb.data[i]; node; node = node->next)
    {
      if (eq(node->val.second, val))
      {
        ++res;
      }
    }
  }
  return res;
}

// Подсчитать значения в хеш-таблицах, удовлетворяющих условию
// Поддержите строгую гарантию
template< class T, class U, class W, class COND >
size_t count_if(ds_t< T, U, W >* root, COND cond)
{
  if (!root)
  {
    return 0;
  }
  size_t res = count_if(root->lhs, cond) + count_if(root->rhs, cond);
  for (size_t i = 0; i < root->val.second.tb.cap; ++i)
  {
    for (List< std::pair< U, W > >* node = root->val.second.tb.data[i]; node; node = node->next)
    {
      if (cond(node->val.second))
      {
        ++res;
      }
    }
  }
  return res;
}

// Переместить элементы хеш-таблицы из указанного узла в другой
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Хеш-таблица не расширяется, новые элементы вставляются в конец цепочки
// Поддержите базовую гарантию: данные не должны теряться
// В параметр запишите количество перенесенных элементов
template< class T, class U, class W, class CMP >
ds_t< T, U, W >* find_node(ds_t< T, U, W >* root, T key, CMP cmp)
{
  while (root)
  {
    if (cmp(key, root->val.first))
    {
      root = root->lhs;
    }
    else if (cmp(root->val.first, key))
    {
      root = root->rhs;
    }
    else
    {
      return root;
    }
  }
  return nullptr;
}

template< class T, class U, class W, class CMP, class HASH, class EQ >
void move(size_t& moved, ds_t< T, U, W >* root, T from, T to, CMP cmp, HASH h, EQ eq)
{
  moved = 0;
  ds_t< T, U, W >* from_node = find_node(root, from, cmp);
  ds_t< T, U, W >* to_node = find_node(root, to, cmp);
  if (!from_node || !to_node)
  {
    return;
  }
  Table< U, W >& from_tb = from_node->val.second;
  Table< U, W >& to_tb = to_node->val.second;
  for (size_t i = 0; i < from_tb.tb.cap; ++i)
  {
    while (from_tb.tb.data[i])
    {
      List< std::pair< U, W > >* curr = from_tb.tb.data[i];
      size_t index = h(curr->val.first) % to_tb.tb.cap;
      from_tb.tb.data[i] = curr->next;
      if (!from_tb.tb.data[i])
      {
        --from_tb.tb.size;
      }
      curr->next = nullptr;
      if (!to_tb.tb.data[index])
      {
        to_tb.tb.data[index] = curr;
        ++to_tb.tb.size;
      }
      else
      {
        List< std::pair< U, W > >* tail = to_tb.tb.data[index];
        while (tail->next)
        {
          tail = tail->next;
        }
        tail->next = curr;
      }
      ++moved;
    }
  }
}

template< class U, class W, class HASH >
void rebuild(Table< U, W >& table, size_t new_cap, HASH h)
{
  size_t total = 0;
  for (size_t i = 0; i < table.tb.cap; ++i)
  {
    for (List< std::pair< U, W > >* n = table.tb.data[i]; n; n = n->next)
    {
      ++total;
    }
  }

  size_t* targets = new size_t[total]{};
  size_t k = 0;
  try
  {
    for (size_t i = 0; i < table.tb.cap; ++i)
    {
      for (List< std::pair< U, W > >* n = table.tb.data[i]; n; n = n->next)
      {
        targets[k++] = h(n->val.first) % new_cap;
      }
    }
  }
  catch (...)
  {
    delete[] targets;
    throw;
  }

  List< std::pair< U, W > >** new_data;
  try
  {
    new_data = new List< std::pair< U, W > >*[new_cap]{};
  }
  catch (...)
  {
    delete[] targets;
    throw;
  }

  k = 0;
  size_t new_size = 0;
  for (size_t i = 0; i < table.tb.cap; ++i)
  {
    while (table.tb.data[i])
    {
      List< std::pair< U, W > >* curr = table.tb.data[i];
      size_t target = targets[k++];
      table.tb.data[i] = curr->next;
      curr->next = nullptr;
      if (!new_data[target])
      {
        new_data[target] = curr;
        ++new_size;
      }
      else
      {
        List< std::pair< U, W > >* tail = new_data[target];
        while (tail->next)
        {
          tail = tail->next;
        }
        tail->next = curr;
      }
    }
  }

  delete[] targets;
  delete[] table.tb.data;
  table.tb.data = new_data;
  table.tb.cap = new_cap;
  table.tb.size = new_size;
}

// Переместить элементы хеш-таблицы из указанного узла в другой
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Новые элементы вставляются в конец цепочки в хещ-таблице
// Таблица должна быть перестроена, если размер цепочки превышает заданный порог
// Количество слотов в новой хеш-таблице определяется реализацией
// Поддержите базовую гарантию: данные не должны теряться
// В параметр запишите количество перенесенных элементов, узел в который выполнялся перенос
// ...и узел из которого выполнялся перенос
template< class T, class U, class W, class CMP, class HASH, class EQ >
void move(size_t& moved,
  ds_t< T, U, W >** dest,
  ds_t< T, U, W >** src,
  ds_t< T, U, W >* root,
  T from,
  T to,
  CMP cmp,
  HASH h,
  EQ eq,
  size_t load)
{
  moved = 0;
  ds_t< T, U, W >* from_node = find_node(root, from, cmp);
  ds_t< T, U, W >* to_node = find_node(root, to, cmp);
  if (!from_node || !to_node || from_node == to_node)
  {
    return;
  }
  *src = from_node;
  *dest = to_node;
  Table< U, W >& from_tb = from_node->val.second;
  Table< U, W >& to_tb = to_node->val.second;
  for (size_t i = 0; i < from_tb.tb.cap; ++i)
  {
    while (from_tb.tb.data[i])
    {
      List< std::pair< U, W > >* curr = from_tb.tb.data[i];
      size_t target = h(curr->val.first) % to_tb.tb.cap;
      from_tb.tb.data[i] = curr->next;
      if (!from_tb.tb.data[i])
      {
        --from_tb.tb.size;
      }
      curr->next = nullptr;
      size_t chain_len = 1;
      if (!to_tb.tb.data[target])
      {
        to_tb.tb.data[target] = curr;
        ++to_tb.tb.size;
      }
      else
      {
        List< std::pair< U, W > >* tail = to_tb.tb.data[target];
        while (tail->next)
        {
          tail = tail->next;
          ++chain_len;
        }
        tail->next = curr;
        ++chain_len;
      }
      ++moved;
      if (chain_len > load)
      {
        rebuild(to_tb, to_tb.tb.cap * 2, h);
      }
    }
  }
}

template< class T, class U, class W, class HASH >
void convert_into(Table< U, W >& dst, const ds_t< T, U, W >* src, HASH h)
{
  if (!src)
  {
    return;
  }
  convert_into(dst, src->lhs, h);
  for (size_t i = 0; i < src->val.second.tb.cap; ++i)
  {
    for (const List< std::pair< U, W > >* node = src->val.second.tb.data[i]; node; node = node->next)
    {
      size_t target = h(node->val.first) % dst.tb.cap;
      List< std::pair< U, W > >* new_node = new List< std::pair< U, W > >{};
      new_node->val = node->val;
      new_node->next = nullptr;
      if (!dst.tb.data[target])
      {
        dst.tb.data[target] = new_node;
        ++dst.tb.size;
      }
      else
      {
        List< std::pair< U, W > >* tail = dst.tb.data[target];
        while (tail->next)
        {
          tail = tail->next;
        }
        tail->next = new_node;
      }
    }
  }
  convert_into(dst, src->rhs, h);
}

// Преобразовать дерево хеш-таблиц в одну хеш-таблицу
// Данные должны быть скопированы
// Поддержите строгую гарантию
template< class T, class U, class W, class HASH, class EQ >
Table< U, W > convert(const ds_t< T, U, W >* root, HASH h, EQ eq)
{
  Table< U, W > result = make_table< U, W >();
  try
  {
    convert_into(result, root, h);
  }
  catch (...)
  {
    clear(result);
    throw;
  }
  return result;
}

template< class T, class U, class W >
List< std::pair< U, W > >* collect_all_nodes(ds_t< T, U, W >* root)
{
  if (!root)
  {
    return nullptr;
  }
  List< std::pair< U, W > >* result = collect_all_nodes(root->lhs);
  List< std::pair< U, W > >** tail = &result;
  while (*tail)
  {
    tail = &(*tail)->next;
  }
  for (size_t i = 0; i < root->val.second.tb.cap; ++i)
  {
    if (root->val.second.tb.data[i])
    {
      *tail = root->val.second.tb.data[i];
      root->val.second.tb.data[i] = nullptr;
      while (*tail)
      {
        tail = &(*tail)->next;
      }
    }
  }
  root->val.second.tb.size = 0;
  *tail = collect_all_nodes(root->rhs);
  return result;
}

// Перенести данные из хеш-таблиц в одну хеш-таблицу
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Поддержите базовую гарантию: данные не должны теряться
// При генерации исключения вынесенные элементы должны быть
// записаны в параметр в виде единого списка (то есть когда не удалось создать таблицу)
template< class T, class U, class W, class HASH, class EQ >
Table< U, W > move(List< std::pair< U, W > >** backup, ds_t< T, U, W >* root, HASH h, EQ eq)
{
  *backup = nullptr;
  List< std::pair< U, W > >* flat = collect_all_nodes(root);
  Table< U, W > result;
  try
  {
    result = make_table< U, W >();
  }
  catch (...)
  {
    *backup = flat;
    throw;
  }
  try
  {
    while (flat)
    {
      List< std::pair< U, W > >* curr = flat;
      size_t target = h(curr->val.first) % result.tb.cap;
      flat = curr->next;
      curr->next = nullptr;
      if (!result.tb.data[target])
      {
        result.tb.data[target] = curr;
        ++result.tb.size;
      }
      else
      {
        List< std::pair< U, W > >* tail = result.tb.data[target];
        while (tail->next)
        {
          tail = tail->next;
        }
        tail->next = curr;
      }
    }
  }
  catch (...)
  {
    for (size_t i = 0; i < result.tb.cap; ++i)
    {
      while (result.tb.data[i])
      {
        List< std::pair< U, W > >* curr = result.tb.data[i];
        result.tb.data[i] = curr->next;
        curr->next = flat;
        flat = curr;
      }
    }
    delete[] result.tb.data;
    *backup = flat;
    throw;
  }
  return result;
}

template< class T, class U, class W, class CMP, class HASH >
void copy_into(ds_t< T, U, W >*& result, const ds_t< T, U, W >* src, CMP cmp, HASH h)
{
  if (!src)
  {
    return;
  }
  copy_into(result, src->lhs, cmp, h);
  for (size_t i = 0; i < src->val.second.tb.cap; ++i)
  {
    for (const List< std::pair< U, W > >* node = src->val.second.tb.data[i]; node; node = node->next)
    {
      ds_t< T, U, W >* tree_node = make_node(result, src->val.first, cmp);
      if (!result)
      {
        result = tree_node;
      }
      size_t target = h(node->val.first) % tree_node->val.second.tb.cap;
      List< std::pair< U, W > >* new_node = new List< std::pair< U, W > >{};
      new_node->val = node->val;
      new_node->next = nullptr;
      if (!tree_node->val.second.tb.data[target])
      {
        tree_node->val.second.tb.data[target] = new_node;
        ++tree_node->val.second.tb.size;
      }
      else
      {
        List< std::pair< U, W > >* tail = tree_node->val.second.tb.data[target];
        while (tail->next)
        {
          tail = tail->next;
        }
        tail->next = new_node;
      }
    }
  }
  copy_into(result, src->rhs, cmp, h);
}

// Слить два дерева хеш-таблиц в одно общее дерево
// Данные должны быть скоприованы
// Поддержите строгую гарантию
template< class T, class U, class W, class CMP, class HASH, class EQ >
ds_t< T, U, W >*
merge(const ds_t< T, U, W >* root1, const ds_t< T, U, W >* root2, CMP cmp, HASH h, EQ eq)
{
  ds_t< T, U, W >* result = nullptr;
  try
  {
    copy_into(result, root1, cmp, h);
    copy_into(result, root2, cmp, h);
  }
  catch (...)
  {
    clear(result);
    throw;
  }
  return result;
}

template< class T, class U, class W, class CMP, class HASH, class EQ >
ds_t< T, U, W >*
merge(size_t& moved, ds_t< T, U, W >* root1, ds_t< T, U, W >* root2, CMP cmp, HASH h, EQ eq)
{
  if (!root2)
  {
    return root1;
  }
  root1 = merge(moved, root1, root2->lhs, cmp, h, eq);
  ds_t< T, U, W >* node1 = make_node(root1, root2->val.first, cmp);
  if (!root1)
  {
    root1 = node1;
  }
  Table< U, W >& from_tb = root2->val.second;
  Table< U, W >& to_tb = node1->val.second;
  for (size_t i = 0; i < from_tb.tb.cap; ++i)
  {
    while (from_tb.tb.data[i])
    {
      List< std::pair< U, W > >* curr = from_tb.tb.data[i];
      size_t target = h(curr->val.first) % to_tb.tb.cap;
      from_tb.tb.data[i] = curr->next;
      if (!from_tb.tb.data[i])
      {
        --from_tb.tb.size;
      }
      curr->next = nullptr;
      if (!to_tb.tb.data[target])
      {
        to_tb.tb.data[target] = curr;
        ++to_tb.tb.size;
      }
      else
      {
        List< std::pair< U, W > >* tail = to_tb.tb.data[target];
        while (tail->next)
        {
          tail = tail->next;
        }
        tail->next = curr;
      }
      ++moved;
    }
  }
  return merge(moved, root1, root2->rhs, cmp, h, eq);
}
