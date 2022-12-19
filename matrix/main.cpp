#include "matrix.h"
#include <iostream>

using namespace std;

static bool testMultiplication();
static bool testAddition();
//static bool testSubtraction();
static bool testAssignment();
static bool testTranspose();
static bool testInverse();
static bool testDeterminant();

int main()
{
  if (!testAddition())
    cerr << "testAddition() failed" << endl;

  if (!testMultiplication())
    cerr << "testMultiplication() failed" << endl;

  if (!testAssignment())
    cerr << "testAssignment()" << endl;

  if (!testTranspose())
    cerr << "testTranspose()" << endl;
  
  if (!testInverse())
    cerr << "testInverse()" << endl;

  if (!testDeterminant())
    cerr << "testDeterminant()" << endl;

  return 0;
}

bool testMultiplication()
{
  matrix<double> m1 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0}
  };

  matrix<double> m2 = {
    {7.0, 8.0},
    {9.0, 10.0},
    {11.0, 12.0}
  };

  matrix<double> m3 = m1 * m2;

  cout << m3 << endl;

  return true;
}

bool testAddition()
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

  cout << m3 << endl;

  return true;
}

bool testSubtraction()
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

  cout << m3 << endl;

  return true;
}

bool testAssignment()
{
  bool testPassed;
  matrix<double> m1 = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  auto m2 = m1;

  testPassed = m2 == m1;

  cout << m2 << endl;

  return testPassed;
}

bool testTranspose()
{
  matrix<double> expected = {
    {1.0, 3.0},
    {2.0, 4.0}
  };

  matrix<double> m1 = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  auto result = m1.transpose();

  cout << result << endl;

  return result == expected;
}

bool testInverse()
{
  matrix<double> m1 = {
    {1.0, 2.0},
    {3.0, 4.0}
  };

  auto result = m1.inverse();

  cout << result << endl;

  return true;
}

bool testDeterminant()
{
  matrix<double> m1 = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
  };

  double det = m1.determinant();

  cout << det << endl;

  return true;
}