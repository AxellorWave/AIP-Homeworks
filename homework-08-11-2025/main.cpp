#include <iostream>
#include <cctype>
#include <fstream>

std::istream & createMatrix(std::istream & input, int * mtx, size_t rows, size_t cols);
void addCol(int * matrix, size_t rows, size_t cols, size_t col_number, size_t value);
void addRowAndCol(int * matrix, size_t rows, size_t cols, size_t row_number, size_t col_number);
void printMatrix(int * matrix, size_t rows, size_t cols);


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
  input.close();

  size_t command = 0, arg_1 = 0, arg_2 = 0;
  while (std::cin >> command) {
    std::cin >> arg_1 >> arg_2;
    if (!std::cin) {
      delete[] matrix;
      std::cerr << "Not enough arguments in command\n";
      return 3;
    }
    if (command == 1) {
      addCol(matrix, rows, cols, arg_1, arg_2);
      printMatrix(matrix, rows, cols);
    } else if (command == 2) {
      addRowAndCol(matrix, rows, cols, arg_1, arg_2);
      printMatrix(matrix, rows, cols);
    } else {
      std::cerr << "Command not found\n";
      return 3;
    }
  }

  delete[] matrix;
  if (!std::cin.eof()) {
    std::cerr << "Bad enter command\n";
    return 3;
  }
  std::cout << "Enter commans successfully end\n";
}

void printMatrix(int * matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    std::cout << matrix[rows*i];
    for (size_t j = 1; j < cols; ++j) {
      std::cout << matrix[rows * i + j];
    }
    std::cout << "\n";
  }
}
