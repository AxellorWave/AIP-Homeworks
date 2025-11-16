#include <iostream>

struct p_t 
{
  int x, y;
};

const p_t & left_bot(const p_t & lhs, const p_t & rhs)
{
  if (lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y)) {
    return lhs;
  }
  return rhs;
}

const p_t & right_top(const p_t & lhs, const p_t & rhs)
{
  if (lhs.x > rhs.x || (lhs.x == rhs.x && lhs.y > rhs.y)) {
    return lhs;
  }
  return rhs;
}

const p_t * left_bot(const p_t * lhs, size_t size)
{
  if (size == 1) {
    return lhs;
  }
  const p_t * res = lhs;
  for (size_t i = 1; i < size; ++i) {
    res = & left_bot(*res, lhs[i]);
  }
  return res;
}

const p_t * right_top(const p_t * lhs, size_t size)
{
  if (size == 1) {
    return lhs;
  }
  const p_t * res = lhs;
  for (size_t i = 1; i < size; ++i) {
    res = & right_top(*res, lhs[i]);
  }
  return res;
}

int main()
{
  p_t a = {-2, -2};
  p_t b = {2, 2};
  p_t c = {5, 5};
  const p_t * arr = new p_t[3] {a, b, c};
  std::cout << left_bot(a, b).x << " " << left_bot(a, b).y << "\n";
  std::cout << right_top(a, b).x << " " <<  right_top(a, b).y << "\n";
  std::cout << left_bot(arr, 3)->x << " " << left_bot(arr, 3)->y << "\n";
  std::cout << right_top(arr, 3)->x << " " << right_top(arr, 3)->y << "\n";
  delete[] arr;
}
