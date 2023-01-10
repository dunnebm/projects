#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <ostream>
#include <string>
#include <cstddef>

template <typename Num> 
class matrix
{
  Num* mat = nullptr;
  size_t rows, cols;
  
public:
  matrix<Num>(size_t rows, size_t cols);
  matrix<Num>(const std::initializer_list<std::initializer_list<Num>>& list);
  matrix<Num>(std::string csv);
  matrix<Num>(const matrix<Num>& mat);
  ~matrix<Num>();
  const matrix<Num>& operator=(const matrix<Num>& rhs);
  Num operator()(unsigned int row, unsigned int col) const;
  Num& operator()(unsigned int row, unsigned int col);
  matrix<Num> operator+(const matrix<Num>& rhs) const; // matrix addition
  matrix<Num> operator-(const matrix<Num>& rhs) const; // matrix subtraction
  matrix<Num> operator*(const matrix<Num>& rhs) const; // matrix multiplication
  matrix<Num> operator~() const; // inverse
  matrix<Num> inverse() const;
  matrix<Num> rref() const; // row-reduced row-echelon form
  matrix<Num> augment(const matrix<Num>& mat) const;
  matrix<Num> transpose() const;
  
  // scalar operations
  matrix<Num> operator+(const Num& num) const; // scalar addition
  matrix<Num> operator-(const Num& num) const; // scalar subtraction
  matrix<Num> operator*(const Num& num) const; // scalar multiplication
  matrix<Num> operator/(const Num& num) const; // scalar division

  // boolean operators
  bool operator==(const matrix<Num>& rhs) const;
  bool operator!=(const matrix<Num>& rhs) const;
  
  size_t get_rows() const { return rows; }
  size_t get_cols() const { return cols; }

  Num determinant() const;
  static matrix<Num> identity(unsigned int size);

  std::string to_string() const;
  std::ostream& out(std::ostream& os) const;

private:
  // These two functions are helpers for the determinant function
  matrix<Num> minor(size_t row, size_t col) const;
  Num cofactor(size_t row, size_t col) const;

};

template <typename Num>
std::ostream& operator<<(std::ostream& os, const matrix<Num>& mat);

#endif
