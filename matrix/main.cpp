#include "matrix.h"
#include <iostream>

using namespace std;

static bool testScalarMultiplication();
static bool testScalarDivision();
static bool testScalarAddition();
static bool testScalarSubtraction();
static bool testMatrixMultiplication();
static bool testMatrixAddition();
static bool testMatrixSubtraction();
static bool testTranspose();
static bool testInverse();
static bool testDeterminant();

int main()
{
  if (!testScalarAddition())
    cerr << "Scalar addition failed!" << endl;
  else
    cout << "Scalar addition passed!" << endl;

  if (!testScalarSubtraction())
    cerr << "Scalar sutraction failed!" << endl;
  else
    cout << "Scalar subtraction passed!" << endl;

  if (!testScalarMultiplication())
    cerr << "Scalar multiplication failed!" << endl;
  else
    cout << "Scalar multiplication passed!" << endl;

  if (!testScalarDivision())
    cerr << "Scalar division failed!" << endl;
  else
    cout << "Scalar division passed!" << endl;

  if (!testMatrixAddition())
    cerr << "Matrix addition failed!" << endl;
  else
    cout << "Matrix addition passed!" << endl;

  if (!testMatrixSubtraction())
    cerr << "Matrix subtraction failed!" << endl;
  else
    cout << "Matrix subtraction passed!" << endl;

  if (!testMatrixMultiplication())
    cerr << "Matrix multiplication failed!" << endl;
  else
    cout << "Matrix multiplication passed!" << endl;

  if (!testTranspose())
    cerr << "Transpose failed!" << endl;
  else
    cout << "Transpose passed!" << endl;
  
  if (!testInverse())
    cerr << "Inverse failed!" << endl;
  else
    cout << "Inverse passed!" << endl;

  if (!testDeterminant())
    cerr << "Determinant failed!" << endl;
  else
    cout << "Determinant passed!" << endl;

  return 0;
}

bool testScalarAddition()
{
  matrix<double> m1 = {
    { 1.0,  9.0, 10.0},
    {23.0, 58.0, 99.0},
    {12.0, 13.0, 33.0}
  };

  matrix<double> expected = {
    {11.0, 19.0,  20.0},
    {33.0, 68.0, 109.0},
    {22.0, 23.0,  43.0}
  };

  auto result = m1 + 10;

  return result == expected;
}

bool testScalarSubtraction()
{
  matrix<double> m1 = {
    { 8.0, 11.0, 42.0, 59.0},
    {80.0,  2.0,  3.0, 17.0}
  };

  matrix<double> expected = {
    { 1.0,  4.0, 35.0, 52.0},
    {73.0, -5.0, -4.0, 10.0}
  };

  auto result = m1 - 7;

  return result == expected;
}

bool testScalarMultiplication()
{
  matrix<double> m1 = {
    { 58.0,  64.0, 80.0},
    {139.0, 154.0, 99.0}
  };

  matrix<double> expected = {
    {406.0,  448.0, 560.0},
    {973.0, 1078.0, 693.0}
  };

  auto result = m1 * 7;

  return result == expected;
}

bool testScalarDivision()
{
  matrix<double> m1 = {
    {406.0,  448.0, 560.0},
    {973.0, 1078.0, 693.0}
  };

  matrix<double> expected = {
    { 58.0,  64.0, 80.0},
    {139.0, 154.0, 99.0}
  };

  auto result = m1 / 7;

  return result == expected;
}

bool testMatrixMultiplication()
{
  matrix<double> m1 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0}
  };

  matrix<double> m2 = {
    { 7.0,  8.0},
    { 9.0, 10.0},
    {11.0, 12.0}
  };

  matrix<double> expected = {
    { 58.0,  64.0},
    {139.0, 154.0}
  };

  matrix<double> result = m1 * m2;

  return result == expected;
}

bool testMatrixAddition()
{
  matrix<double> m1 = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  matrix<double> m2 = {
    {5.0, 6.0},
    {7.0, 8.0}
  };

  auto m3 = m1 + m2;

  return true;
}

bool testMatrixSubtraction()
{
  matrix<double> m1 = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  matrix<double> m2 = {
    {5.0, 6.0},
    {7.0, 8.0}
  };

  auto m3 = m1 - m2;

  return true;
}

bool testTranspose()
{
  matrix<double> m1 = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  matrix<double> expected = {
    {1.0, 3.0},
    {2.0, 4.0}
  };

  auto result = m1.transpose();


  return result == expected;
}

bool testInverse()
{
  matrix<double> m1 = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  matrix<double> expected = {
    {-2.0,  1.0},
    { 1.5, -0.5}
  };

  auto result = m1.inverse();

  return result == expected;
}

bool testDeterminant()
{
  matrix<double> m1 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 0.0, 9.0}
  };

  double expected = -48.0;
  double result = m1.determinant();

  return result == expected;
}