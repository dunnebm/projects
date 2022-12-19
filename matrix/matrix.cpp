#include "matrix.h"
#include <iostream>

template <typename Num>
matrix<Num>::matrix(unsigned int rows, unsigned int cols)
:rows(rows), cols(cols)
{
  mat = new Num[rows*cols];
}

template <typename Num>
matrix<Num>::matrix(const std::initializer_list<std::initializer_list<Num>>& list)
{
  auto iter1 = list.begin();
  auto iter2 = iter1->begin();

  rows = list.size();
  cols = iter1->size();

  mat = new Num[rows*cols];

  for (; iter1 < list.end(); ++iter1)
  {
    if (iter1->size() != cols)
      throw "All columns must be the same length!";
  }

  iter1 = list.begin();
  for (unsigned int i = 0; i < rows; ++i, ++iter1)
  {
    iter2 = iter1->begin();
    for (unsigned int j = 0; j < cols; ++j, ++iter2)
    {
      (*this)(i,j) = *iter2;
    }
  }
}

template <typename Num>
matrix<Num>::matrix(const matrix<Num>& mat)
{
  (*this) = mat;
}

template <typename Num>
matrix<Num>::~matrix<Num>()
{
  delete [] mat;
}

template <typename Num>
const matrix<Num>& matrix<Num>::operator=(const matrix<Num>& rhs)
{
  delete [] mat;

  rows = rhs.rows;
  cols = rhs.cols;

  mat = new Num[rows*cols];

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      (*this)(i,j) = rhs(i,j);
    }
  }

  return rhs;
}

template <typename Num>
Num matrix<Num>::operator()(unsigned int row, unsigned int col) const
{
  return mat[cols*row + col];
}

template <typename Num>
Num& matrix<Num>::operator()(unsigned int row, unsigned int col)
{
  return mat[cols*row + col];
}

template <typename Num>
matrix<Num> matrix<Num>::operator+(const matrix<Num>& rhs) const
{
  if (rows != rhs.rows || cols != rhs.cols)
    throw "dimensions don't match!";

  matrix retval(rows, cols);
  
  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(i,j) = (*this)(i,j) + rhs(i,j);
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::operator-(const matrix<Num>& rhs) const
{
  if (rows != rhs.rows || cols != rhs.cols)
    throw "dimensions don't match!";

  matrix retval(rows, cols);

  for (unsigned int i = 0; i < rows; ++i) 
  {
    for (unsigned int j = 0; j < cols; ++j) 
    {
      retval(i,j) = (*this)(i,j) - rhs(i,j);
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::operator*(const matrix<Num>& rhs) const
{
  if (cols != rhs.rows)
    throw "Undefined matrix operation!";

  matrix retval(rows, rhs.cols);

  for (unsigned int i = 0; i < retval.rows; ++i)
  {
    for (unsigned int j = 0; j < retval.cols; ++j)
    {
      for (unsigned int k = 0; k < cols; ++k)
      {
        retval(i,j) += (*this)(i,k) * rhs(k,j);
      }
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::operator~() const
{
  return inverse();
}

template <typename Num>
matrix<Num> matrix<Num>::inverse() const
{
  if (rows != cols)
    throw "Not a square matrix!";
  
  matrix<Num> augmat = augment(matrix<Num>::identity(rows));

  augmat = augmat.rref();

  matrix<Num> retval(rows, cols);

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(i,j) = augmat(i,j+cols);
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::rref() const
{
  matrix<Num> retval(*this);

  for (unsigned int i = 0; i < rows && i < cols; ++i)
  {
    // retval(i,i) == 0 then find a row with col i not equal to zero and
    // add it to row i.
    if (retval(i,i) == 0)
    {
      for (unsigned int j = 0; j < rows; ++j)
      {
        // doesn't make sense to add a row with its self
        if (i == j) continue;

        if (retval(j,i) != 0)
        {
          for (unsigned int k = 0; k < cols; ++k)
            retval(i,k) += retval(j,k);
        }
      }
    }
    
    // perform Guass-Jordan reduction
    for (unsigned int j = 0; j < rows; ++j)
    {
      if (i == j || retval(j,i) == 0) continue;

      Num scale_factor = retval(i,i) / retval(j,i);

      for (unsigned int k = 0; k < cols; ++k)
      {
        retval(j,k) = scale_factor*retval(j,k) - retval(i,k);
      }
    }
  }

  // normalize
  for (unsigned int i = 0; i < rows && i < cols; ++i)
  {
    if (retval(i,i) == 0) continue;
    
    Num scale_factor = retval(i,i);

    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(i,j) /= scale_factor;
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::augment(const matrix<Num>& mat) const
{
  if (rows != mat.rows)
    throw "Rows don't match!";

  matrix<Num> retval{rows, cols + mat.cols};

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(i,j) = (*this)(i,j);
    }

    for (unsigned int j = 0; j < mat.cols; ++j)
    {
      retval(i,cols+j) = mat(i,j);
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::transpose() const
{
  matrix<Num> retval{cols, rows};

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(j,i) = (*this)(i,j);
    }
  }

  return retval;
}

template <typename Num>
Num matrix<Num>::determinant() const
{
  if (rows != cols)
    throw "Dimensions don't match!";

  if (rows == 2)
  {
    return (*this)(0,0)*(*this)(1,1) - (*this)(0,1)*(*this)(1,0);
  }

  Num det = 0;
  for (unsigned int j = 0; j < cols; ++j)
  {
    det += (*this)(0,j) * cofactor(0,j);
  }

  return det;
}

template <typename Num>
matrix<Num> matrix<Num>::minor(unsigned int row, unsigned int col) const
{
  matrix<Num> retval{rows - 1, cols - 1};
  unsigned int m = 0, n = 0;

  for (unsigned int i = 0; i < rows; ++i)
  {
    if (i == row) continue;

    for (unsigned int j = 0; j < cols; ++j)
    {
      if (j == col) continue;

      retval(m,n) = (*this)(i,j);

      ++n;
    }
    
    n = 0;
    ++m;
  }

  return retval;
}

template <typename Num>
Num matrix<Num>::cofactor(unsigned int row, unsigned int col) const
{
  Num sign = ((row + col)%2 == 0)? 1 : -1;

  return sign * minor(row, col).determinant();
}

template <typename Num>
matrix<Num> matrix<Num>::operator+(const Num& num) const
{
  matrix retval(*this);

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(i,j) += num;
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::operator-(const Num& num) const
{
  matrix retval(*this);

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(i,j) -= num;
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::operator*(const Num& num) const
{
  matrix retval(*this);

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(i,j) *= num;
    }
  }

  return retval;
}

template <typename Num>
matrix<Num> matrix<Num>::operator/(const Num& num) const
{
  matrix retval(*this);

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      retval(i,j) /= num;
    }
  }

  return retval;
}

template <typename Num>
bool matrix<Num>::operator==(const matrix<Num>& rhs) const
{
  if (rows != rhs.rows || cols != rhs.cols)
    return false;

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      if ((*this)(i,j) != rhs(i,j))
        return false;
    }
  }

  return true;
}

template <typename Num>
bool matrix<Num>::operator!=(const matrix<Num>& rhs) const
{
  return !(*this == rhs);
}

template <typename Num>
matrix<Num> matrix<Num>::identity(unsigned int size)
{
  matrix<Num> retval(size, size);

  for (unsigned int i = 0; i < size; ++i)
  {
    for (unsigned int j = 0; j < size; ++j)
    {
      if (i == j)
        retval(i,j) = static_cast<Num>(1);
      else
        retval(i,j) = static_cast<Num>(0);
    }
  }

  return retval;
}

template <typename Num>
std::ostream& matrix<Num>::out(std::ostream& os) const
{
  os << "[";

  for (unsigned int i = 0; i < rows; ++i)
  {
    if (i == 0)
      os << "[";
    else
      os << " [";
    
    unsigned int j;
    for (j = 0; j < cols - 1; ++j)
    {
      os << (*this)(i,j) << ", ";
    }

    if (i < rows - 1)
      os << (*this)(i,j) << "]" << std::endl;
    else
      os << (*this)(i,j) << "]]" << std::endl;
  }

  return os;
}

template <typename Num>
std::ostream& operator<<(std::ostream& os, const matrix<Num>& mat)
{
  return mat.out(os);
}

template class matrix<float>;
template class matrix<double>;

template std::ostream& operator<<(std::ostream& os, const matrix<float>& mat);
template std::ostream& operator<<(std::ostream& os, const matrix<double>& mat);