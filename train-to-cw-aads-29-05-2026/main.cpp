#include <cstddef>
#include <utility>

// Вектор
template < class T >
struct Vec
{
  T* data;
  size_t size, cap;
};

// Список
template < class T >
struct List
{
  List< T >* next;
  T val;
};

// Хеш-таблица с закрытой адресацией
// Разрешение коллизий методом цепочек
// Хешируемый ключ - K, хранимое значение - V
template < class K, class V >
struct Table
{
  Vec< List< std::pair< K, V > >* > tb;
};

// Бинарное дерево
// Параметр K - ключ дерева, V - значение
template < class K, class V >
struct Tree
{
  Tree< K, V >*lhs, *rhs;
  Tree< K, V >* parent;
  std::pair< K, V > val;
};

template < class T, class U, class W >
using ds_t = Tree< T, Table< U, W > >;

// Полагая, что бинарное дерево организовано как дерево поиска,
// а все данные располагаются во Free Store
// решите ниже описанные задачи
// Считайте, что функциональные объекты (типа CMP, HASH, EQ)
// предоставляют строгую гарантию безопасности и не меняют передаваемых
// параметров

// Освободить память, занимаемую структурой
template < class T >
void clear(List< T >* root) noexcept
{
  if (!root)
  {
    return;
  }
  clear(root->next);
  delete root;
}

template < class U, class W >
void clear(Table< U, W >& table) noexcept
{
  for (size_t i = 0; i < table.tb.size; ++i)
  {
    clear(table.tb.data[i]);
  }
  delete[] table.tb.data;
}

template < class T, class U, class W >
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
template < class T, class U, class W >
void clearit(ds_t< T, U, W >* root) noexcept;

// Добавить узел дерева с пустой хеш-таблицей
// Вернуть указатель на этот узел
// Параметры пустой хеш-таблицы определяются реализацией
// Поддержите строгую гарантию
template < class T, class U, class W, class CMP >
ds_t< T, U, W >* make_node(ds_t< T, U, W >* root, T key, CMP cmp);

// Вставить элемент в хеш-таблицу соответствующего узла дерева (создать узел при необходимости)
// Вернуть указатель на узел и номер слота
// Хеш-таблица не расширяется, новые элементы вставляются в конец цепочки
// Поддержите строгую гарантию
template < class T, class U, class W, class CMP, class HASH, class EQ >
std::pair< ds_t< T, U, W >*, size_t >
insert(ds_t< T, U, W >* root, T key, CMP cmp, U tkey, HASH h, EQ eq, W val);

// Подсчитать значения в хеш-таблицах, равные заданному
// Поддержите строгую гарантию
template < class T, class U, class W, class EQ >
size_t count(ds_t< T, U, W >* root, W val, EQ eq);
// Подсчитать значения в хеш-таблицах, удовлетворяющих условию
// Поддержите строгую гарантию
template < class T, class U, class W, class COND >
size_t count_if(ds_t< T, U, W >* root, COND cond);

// Переместить элементы хеш-таблицы из указанного узла в другой
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Хеш-таблица не расширяется, новые элементы вставляются в конец цепочки
// Поддержите базовую гарантию: данные не должны теряться
// В параметр запишите количество перенесенных элементов
template < class T, class U, class W, class CMP, class HASH, class EQ >
void move(size_t& moved, ds_t< T, U, W >* root, T from, T to, CMP cmp, HASH h, EQ eq);

// Переместить элементы хеш-таблицы из указанного узла в другой
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Новые элементы вставляются в конец цепочки в хещ-таблице
// Таблица должна быть перестроена, если размер цепочки превышает заданный порог
// Количество слотов в новой хеш-таблице определяется реализацией
// Поддержите базовую гарантию: данные не должны теряться
// В параметр запишите количество перенесенных элементов, узел в который выполнялся перенос
// ...и узел из которого выполнялся перенос
template < class T, class U, class W, class CMP, class HASH, class EQ >
void move(size_t& moved,
  ds_t< T, U, W >** dest,
  ds_t< T, U, W >** src,
  ds_t< T, U, W >* root,
  T from,
  T to,
  CMP cmp,
  HASH h,
  EQ eq,
  size_t load);

// Преобразовать дерево хеш-таблиц в одну хеш-таблицу
// Данные должны быть скопированы
// Поддержите строгую гарантию
template < class T, class U, class W, class HASH, class EQ >
Table< U, W > convert(const ds_t< T, U, W >* root, HASH h, EQ eq);

// Перенести данные из хеш-таблиц в одну хеш-таблицу
// Элементы цепочек хеш-таблицы не должны пересоздаваться
// Поддержите базовую гарантию: данные не должны теряться
// При генерации исключения вынесенные элементы должны быть
// записаны в параметр в виде единого списка (то есть когда не удалось создать таблицу)
template < class T, class U, class W, class HASH, class EQ >
Table< U, W > move(List< std::pair< U, W > >** backup, ds_t< T, U, W >* root, HASH h, EQ eq);

// Слить два дерева хеш-таблиц в одно общее дерево
// Данные должны быть скоприованы
// Поддержите строгую гарантию
template < class T, class U, class W, class CMP, class HASH, class EQ >
ds_t< T, U, W >*
merge(const ds_t< T, U, W >* root1, const ds_t< T, U, W >* root2, CMP cmp, HASH h, EQ eq);

// Перенести данные из второго дерева в первое дерево
// Элементы цепочеке хеш-таблицы не должны пересоздаваться
// Освобождать память второго дерева не нужно
// Поддержите базову гарантию: данные не должны теряться
// В параметр запишите количество перенесенных элементов хеш-таблиц
template < class T, class U, class W, class CMP, class HASH, class EQ >
ds_t< T, U, W >*
merge(size_t& moved, ds_t< T, U, W >* root1, ds_t< T, U, W >* root2, CMP cmp, HASH h, EQ eq);
