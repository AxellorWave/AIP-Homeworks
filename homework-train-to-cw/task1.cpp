char f1(int); //f1 - Функция принимающая целое и возвращающая символ
int f2(double(*)(const char *)); //f2 - функция принимающая указатель на функцию,
//принимающую  указатель на неизменяемый символ, возвращающую дробное, возвращающее целое
double(*(f3))(char *[3]); //f3 -
char * (*(f4))(bool(*)(double &&, int));

bool(*pg1)(const long *[5]) = nullptr;
const int *(*pg2)(int(*)(int[])) = nullptr;
double(*(*pg3)(int[]))(bool) = nullptr;
int(*(*pg4)(int(*)(int)))(int(*)(int)) = nullptr;

using v1_t = void(*)(int, char *);
using v2_t = const char *(*)(int[5], unsigned **);
using v3_t = double(*)(int, bool[3], char &);
using v4_t = int(*(*)(bool))(char[255], char[255]);
