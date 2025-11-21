#include <iostream>
#include <fstream>

std::istream & createMatrix(std::istream & input, int * mtx, size_t rows, size_t cols);
void addCol(int ** matrix, size_t & rows, size_t & cols, size_t col_number, size_t value);
void addRow(int ** matrix, size_t & rows, size_t & cols, size_t row_number, size_t value);
void printMatrix(int * matrix, size_t rows, size_t cols);


int main(int argc, char ** argv)
{
  if (argc < 2) {
    std::cerr << "Not enough arguments\n";
    return 3;
  }
  if (argc > 2) {
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
  if (!input) {
    delete[] matrix;
    std::cerr << "Bad enter from file\n";
    return 1;
  }
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
      if (arg_1 > rows || arg_1 < 0) {
        std::cerr << "Bad enter row";
        return 3;
      } 
      try {
        addRow(& matrix, rows, cols, arg_1, arg_2);
      } catch (const std::bad_alloc &) {
        delete[] matrix;
        std::cerr << "Bad alloc\n";
        return 2;
      }
      printMatrix(matrix, rows, cols);
    } else if (command == 2) {
      if (arg_1 > cols || arg_1 < 0) {
        std::cerr << "Bad enter col";
        return 3;
      } 
      try {
        addCol(& matrix, rows, cols, arg_1, arg_2);
      } catch (const std::bad_alloc &) {
        delete[] matrix;
        std::cerr << "Bad alloc\n";
        return 2;
      }
      printMatrix(matrix, rows, cols);
    } else if (command == 3) {
      if (arg_1 > rows || arg_1 < 0 || arg_2 > cols || arg_2 < 0) {
        std::cerr << "Bad enter col or row";
        return 3;
      } 
      try {
      addRow(& matrix, rows, cols, arg_1, 0);
      addCol(& matrix, rows, cols, arg_2, 0);
      } catch (const std::bad_alloc &) {
        delete[] matrix;
        std::cerr << "Bad alloc\n";
        return 2;
      }
      printMatrix(matrix, rows, cols);
    } else {
      std::cerr << "Command not found\n";
    }
  }

  delete[] matrix;
  if (!std::cin.eof()) {
    std::cerr << "Bad enter command\n";
    return 3;
  }
  std::cout << "Enter commans successfully end\n";
}

std::istream & createMatrix(std::istream & input, int * mtx, size_t rows, size_t cols) 
{
  for (size_t i = 0; i < rows * cols; ++i) {
    input >> mtx[i];
  } 
  return input;
}

void printMatrix(int * matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    std::cout << matrix[cols*i];
    for (size_t j = 1; j < cols; ++j) {
      std::cout << " " << matrix[cols * i + j];
    }
    std::cout << "\n";
  }
}

void addCol(int ** matrix, size_t & rows, size_t & cols, size_t col_number, size_t value)
{
  ++cols;
  int * new_matrix = new int[rows * (cols)];
  int k = 0;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (j == col_number) {
        ++k;
        new_matrix[i * cols + j] = value;
      } else {
        new_matrix[i * cols + j] = (* matrix)[i * cols + j - k]; 
      }
    }
  }
  delete[] * matrix;
  * matrix = new_matrix;
}

void addRow(int ** matrix, size_t & rows, size_t & cols, size_t row_number, size_t value)
{
  ++rows;
  int * new_matrix = new int[rows * (cols)];
  int k = 0;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (i == row_number) {
        k = 1;
        new_matrix[i * cols + j] = value;
      } else {
        new_matrix[i * cols + j] = (* matrix)[(i - k) * cols + j]; 
      }
    }
  }
  delete[] * matrix;
  * matrix = new_matrix;
}

