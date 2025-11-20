#include <iostream>
#include <cctype>
#include <fstream>

std::istream & createMatrix(std::istream & input, int * mtx, size_t rows, size_t cols);

int main(int argc, char ** argv)
{
  if (argc < 1) {
    std::cerr << "Not enough arguments\n";
    return 3;
  }
  if (argc > 1) {
    std::cerr << "Too many arguments\n";
    return 3;
  }
  
  std::ifstream input(argv[1]);
  size_t rows, cols;
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Bad read (rows and cols)\n";
    return 1;
  }

  int * matrix = nullptr;
  try {
    matrix = new int[rows * cols];
  } catch (const std::bad_alloc &) {
    std::cerr << "Bad alloc\n";
    return 2;
  }

  createMatrix(input, matrix, rows, cols);
  input.close()

  size_t command = 0, arg_1 = 0, arg_2 = 0;
  while (std::cin) {
    std::cin >> command >> arg_1 >> arg_2;
    
    if (command == 1) {
      addCol(matrix, rows, cols, arg_1, arg_2);
    } else if (command == 2) {
      addRowAndCol(matrix, rows, cols, arg_1, arg_2);
    } else {
      std::cerr << "Command not found\n";
      return 3;
    }
  }
}