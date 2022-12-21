#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <ostream>
#include <mutex>
#include <optional>

template <typename Num> 
class matrix
{
  Num* mat = nullptr;
  unsigned int rows, cols;
  
public:
  matrix<Num>(unsigned int rows, unsigned int cols);
  matrix<Num>(const std::initializer_list<std::initializer_list<Num>>& list);
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
  
  unsigned int get_rows() const { return rows; }
  unsigned int get_cols() const { return cols; }

  Num determinant() const;
  static matrix<Num> identity(unsigned int size);

  std::ostream& out(std::ostream& os) const;

  matrix<Num> minor(unsigned int row, unsigned int col) const;

private:
  Num cofactor(unsigned int row, unsigned int col) const;

};

template <typename Num>
std::ostream& operator<<(std::ostream& os, const matrix<Num>& mat);

#endif
