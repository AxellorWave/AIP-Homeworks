#include <iostream>

struct Point3d 
{
  Point3d(int x, int y, int z);
  Point3d();
  ~Point3d();
  Point3d(const Point3d & c);
  Point3d(Point3d && c);
  Point3d & operator=(const Point3d & r);
  Point3d & operator=(Point3d && c);
  int x() const;
  int y() const;
  int z() const;
  Point3d & operator+=(const Point3d & r);
  Point3d & operator-=(const Point3d & r);
  Point3d & operator*=(int k);
  int operator*(const Point3d & r) const;
private:
  int * data;
};

Point3d::Point3d(int x, int y, int z):
  data(new int[3] {x, y, z})
{}

Point3d::Point3d():
  data(new int[3] {0, 0, 0})
{}

Point3d::~Point3d()
{
  delete[] data;
}

Point3d::Point3d(const Point3d & c):
  data(new int[3] {c.data[0], c.data[2], c.data[2]})
{}

Point3d::Point3d(Point3d && c):
  data(c.data)
{
  c.data = nullptr;
}

Point3d & Point3d::operator=(const Point3d & r)
{
  if (this != &r) {
    int * new_data = new int[3];
    new_data[0] = r.data[0];
    new_data[1] = r.data[1];
    new_data[2] = r.data[2];
    delete[] data;
    data = new_data;
  }
  return * this;
}

Point3d & Point3d::operator=(Point3d && c)
{
  if (this != &c) {
    delete[] data;
    data = c.data;
    c.data = nullptr;
  }
  return * this;
}

int Point3d::x() const
{
  return data[0];
}

int Point3d::y() const
{
  return data[1];
}

int Point3d::z() const
{
  return data[2];
}

Point3d & Point3d::operator+=(const Point3d & r)
{
  data[0] += r.data[0];
  data[1] += r.data[1];
  data[2] += r.data[2];
  return * this;
}

Point3d & Point3d::operator-=(const Point3d & r)
{
  data[0] -= r.data[0];
  data[1] -= r.data[1];
  data[2] -= r.data[2];
  return * this;
}

Point3d & Point3d::operator*=(int k)
{
  data[0] *= k;
  data[1] *= k;
  data[2] *= k;
  return * this;
}

int Point3d::operator*(const Point3d & r) const
{
  return data[0] * r.data[0] + data[1] * r.data[1] + data[2] * r.data[2];
}

int main()
{
  Point3d a{1, 2, 3};
  Point3d b{3, 2, 1};
  Point3d t;
  std::cout << "t: " << t.x() << " " << t.y() << " " << t.z() << "\n";
  std::cout << "a: " << a.x() << " " << a.y() << " " << a.z() << "\n";
  std::cout << "b: " << b.x() << " " << b.y() << " " << b.z() << "\n";
  a *= 2;
  b += a;
  std::cout << "a: " << a.x() << " " << a.y() << " " << a.z() << "\n";
  std::cout << "b: " << b.x() << " " << b.y() << " " << b.z() << "\n";
  Point3d c(b);
  c = a;
  c -= b;
  std::cout << "c: " << c.x() << " " << c.y() << " " << c.z() << "\n";
  std::cout << "c * a: " << (c * a) << "\n";
  Point3d d = std::move(c);
  std::cout << "d: " << d.x() << " " << d.y() << " " << d.z() << "\n";
}