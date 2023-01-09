#include "matrix.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>

using size_t = std::size_t;

template <typename Num>
matrix<Num>::matrix(unsigned int rows, unsigned int cols)
:rows(rows), cols(cols)
{
  // Do not allow dimensions less than 2.
  if (rows < 2 || cols < 2)
    throw "Invalid dimensions!";

  mat = new Num[rows*cols];

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      (*this)(i,j) = (Num) 0;
    }
  }
}

template <typename Num>
matrix<Num>::matrix(const std::initializer_list<std::initializer_list<Num>>& list)
{
  auto iter1 = list.begin();
  auto iter2 = iter1->begin();

  rows = list.size();
  cols = iter1->size();

  // Do not allow dimensions less than 2
  if (rows < 2 || cols < 2)
    throw "Invalid dimensions!";

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

static bool isDigit(char c)
{
  return c >= '0' && c <= '9';
}

template <typename Num>
matrix<Num>::matrix(std::string csv)
{
  unsigned int row_count = 0, col_count = 1;

  // Used to assign the first row's column count member variable rows
  bool first_row_read = false;

  /* At the start of a new entry all of the flags below are reset */

  // This flag is raised when a decimal digit is found in an entry.
  // However, it will be reset if an exponent 'e' is found so it can be reused
  // to detect a number in the exponent
  bool digit_found = false;

  // There can only be one decimal point per number, this flag is used to
  // spot multiple occurences.
  bool decimal_found = false;

  // Signs can only occur at the beginning of a number and an exponent;
  // only minus signs are allowed at the beginning of numbers, but plus or
  // minus signs may appear at the start of an exponent.
  bool sign_found = false;

  // Denotes the start of an exponent
  bool exponent_found = false;

  // This flag is used to detect multiple numbers in an entry.
  bool entry_filled = false;

  // check the format, and if formatted corectly, save the dimensions
  // for memory allocation.
  for (size_t i = 0; i < csv.size(); ++i)
  {
    if (csv[i] == ',')
    {
      if (digit_found)
        ++col_count;
      else
        throw "All entries must be filled";

      // reset flags for next entry
      digit_found = false;
      decimal_found = false;
      entry_filled = false;
      exponent_found = false;
      sign_found = false;
    }
    else if (isDigit(csv[i]))
    {
      if (entry_filled)
        throw "There are two numbers in one entry spot";
      digit_found = true;
    }
    else if (csv[i] == '.')
    {
      if (decimal_found)
        throw "There are two decimal points in this entry";
      if (exponent_found)
        throw "Decimals are not allowed in the exponent";
      if (entry_filled)
        throw "There are two numbers in one entry spot";
      decimal_found = true;
    }
    else if (csv[i] == ' ')
    {
      if (digit_found)
        entry_filled = true;
      else if (decimal_found)
        throw "There can't be space between decimal points and digits";
      else if (sign_found)
        throw "There can't be space between a sign and the number";
      else if (exponent_found)
        throw "This exponent does not have a number in it";
    }
    else if (csv[i] == '-')
    {
      if (digit_found || decimal_found)
        throw "Incorrect location for a minus sign";
      if (sign_found)
        throw "Too many signs in this entry";

      sign_found = true;
    }
    else if (csv[i] == '+')
    {
      if (exponent_found && !digit_found)
        sign_found = true;
      else
        throw "Incorrect location for a plus sign";
    }
    else if (csv[i] == 'e')
    {
      if (!digit_found)
        throw "Invalid number";
      if (entry_filled)
        throw "Invalid entry";

      exponent_found = true;

      // reset flags so they can be used for the exponent
      digit_found = false;
      decimal_found = false;
      sign_found = false;
    }
    else if (csv[i] == '\n')
    {
      if (!digit_found && !decimal_found && !sign_found && !exponent_found && col_count == 1)
        continue; //This is an empty row, so nothing to do 
      
      if (first_row_read && col_count != cols)
        throw "This row does not have the same number of columns as the first row";
      
      if (!first_row_read)
      {
        if (col_count < 2)
          throw "Column count must be greater than or equal to 2";
        cols = col_count;
        first_row_read = true;
      }
      
      // reset flags for next entry
      digit_found = false;
      decimal_found = false;
      sign_found = false;
      exponent_found = false;
      entry_filled = false;
      col_count = 1; // set to 1 because I increment every comma, and there is one less comma then column
      ++row_count;
    }
    else
      throw "Unexpected character";
    
    // Just in case the last row does not have a newline, increment
    // the row count here
    if (i == csv.size() - 1 && csv[i] != '\n')
    {
      if (digit_found && first_row_read && (col_count != cols))
        throw "Every row must have an equal number of columns";
      if (digit_found && first_row_read && (col_count == cols))
        ++row_count;
    }
  }

  if (row_count < 2)
    throw "Row count must be greater than or equal to 2";

  rows = row_count;

  mat = new Num[rows*cols];

  row_count = 0;
  col_count = 0;
  char* end; // used for strtod()

  // Just in case there is additional newlines, this flag is
  // used so empty rows do not increment the row_count.
  bool empty_row = true;

  // Parse the numbers from the string and assign 
  // them to their respective matrix locations
  for (size_t i = 0; i < csv.size(); ++i)
  {
    if (isDigit(csv[i]) || csv[i] == '.' || csv[i] == '-')
    {
      (*this)(row_count, col_count) = static_cast<Num>(strtod(&csv[i], &end));
      ++col_count;
      i += static_cast<size_t>(end - &csv[i]);
      empty_row = false;
    }
    if (csv[i] == '\n' && !empty_row)
    {
      ++row_count;
      col_count = 0;
      empty_row = true;
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
  
  // Augment *this matrix with an identity matrix 
  // that has the same dimensions.
  matrix<Num> augmat = augment(matrix<Num>::identity(rows));

  // The result of putting the augmented matrix in RREF
  // is that the identity matrix that was augmented with *this matrix
  // will now be the inverse of *this.
  augmat = augmat.rref();

  matrix<Num> retval(rows, cols);

  // The augmented matrix contains two matrices side-by-side; extract
  // right-most matrix because it represents the inverse of *this.
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
      // Don't reduce row i, and no need to reduce a row if its ith column
      // is already zero.
      if (i == j || retval(j,i) == 0) continue;

      Num scale_factor = retval(i,i) / retval(j,i);

      // Multiply the scale_factor to the jth row and subtract that
      // row by ith row. This will have the effect of zeroing the 
      // retval(j,i) entry 
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
static bool almostEqual(Num a, Num b, Num epsilon)
{
  auto threshold = std::numeric_limits<Num>::min();
  auto min = std::min(std::abs(a), std::abs(b));

  if (std::abs(min) == 0.0)
    return std::abs(a-b) < epsilon;

  return (std::abs(a-b) / std::max(threshold, min)) < epsilon;
}

template <typename Num>
bool matrix<Num>::operator==(const matrix<Num>& rhs) const
{
  if (rows != rhs.rows || cols != rhs.cols)
    return false;

  auto epsilon = std::numeric_limits<Num>::epsilon();

  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      almostEqual((*this)(i,j), rhs(i,j), epsilon);
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
std::string matrix<Num>::to_string() const
{
  std::string str;
  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      str += std::to_string(static_cast<double>((*this)(i,j)));
      if (j < cols - 1)
        str += ',';
    }
    str += '\n';
  }
  return str;
}

template <typename Num>
std::ostream& matrix<Num>::out(std::ostream& os) const
{
  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      if (j == cols - 1)
        os << (*this)(i,j);
      else
        os  << (*this)(i,j) << ",";
    }
    os << std::endl;
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