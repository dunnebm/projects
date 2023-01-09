/*
  Author: Brandon Dunne

  This program test my matrix class by randomly generating matrices and performing operations
  on them, and then comparing their results with the Verifier.
  The Verifier gets its results from the Numpy API. Since this is a python API, I wrote a python
  script that communitcates with the Verifier server-client style.
*/

#include "matrix.h"
#include <iostream>
#include <string>
#include <random>
#include <regex>
#include <cctype>
#include <limits>
#include <cmath>
#include "Verifier.h"

static bool testScalarMultiplication(Verifier& verifier);
static bool testScalarDivision(Verifier& verifier);
static bool testScalarAddition(Verifier& verifier);
static bool testScalarSubtraction(Verifier& verifier);
static bool testMatrixMultiplication(Verifier& verifier);
static bool testMatrixAddition(Verifier& verifier);
static bool testMatrixSubtraction(Verifier& verifier);
static bool testInverse(Verifier& verifier);
static bool testDeterminant(Verifier& verifier);

static std::regex regx{R"(<(matrix|scalar)>([\.\d\s,e\+-]*?)</\1>)"};

int main()
{ 
  Verifier verifier{4096};
  if (verifier.failed())
  {
    std::cerr << "Failed to construct Verifier!\n";
    return 1;
  }

  try {
    if (!testScalarAddition(verifier))
      std::cerr << "Scalar addition failed!\n";
    else
      std::cout << "Scalar addition passed!\n";

    if (!testScalarSubtraction(verifier))
      std::cerr << "Scalar subtraction failed!\n";
    else
      std::cout << "Scalar subtraction passed!\n";

    if (!testScalarMultiplication(verifier))
      std::cerr << "Scalar multiplication failed!\n";
    else
      std::cout << "Scalar multiplication passed!\n";

    if (!testScalarDivision(verifier))
      std::cerr << "Scalar division failed!\n";
    else
      std::cout << "Scalar division passed!\n";

    if (!testMatrixAddition(verifier))
      std::cerr << "Matrix addition failed!\n";
    else
      std::cout << "Matrix addition passed!\n";

    if (!testMatrixSubtraction(verifier))
      std::cerr << "Matrix subtraction failed!\n";
    else
      std::cout << "Matrix subtraction passed!\n";

    if (!testMatrixMultiplication(verifier))
      std::cerr << "Matrix multiplication failed!\n";
    else
      std::cout << "Matrix multiplication passed!\n";

    if (!testInverse(verifier))
      std::cerr << "Inverse failed!\n";
    else
      std::cout << "Inverse passed!\n";

    if (!testDeterminant(verifier))
      std::cerr << "Determinant failed!\n";
    else
      std::cout << "Determinant passed!\n";
  } 
  catch (const char* error)
  {
    std::cerr << error << '\n';
  }

  verifier.send_request("<exit></exit>");

  return 0;
}

/**
 * Format the data so the python script can interpret it
 */
static std::string formatArgs(const matrix<double>& m1, const matrix<double>& m2)
{
  std::string xml = "<matrix>\n" + m1.to_string() + "</matrix>\n";
  xml += "<matrix>\n" + m2.to_string() + "</matrix>\n";
  return xml;
}

static std::string formatArgs(const matrix<double>& m, double scalar)
{
  std::string xml = "<matrix>\n" + m.to_string() + "</matrix>\n";
  xml += "<scalar> " + std::to_string(scalar) + " </scalar>\n";
  return xml;
}

static std::string formatArg(const matrix<double>& m)
{
  return "<matrix>\n" + m.to_string() + "</matrix>\n";
}

/**
 * Parse the result from the Verifier and use that data to instantiate
 * a matrix
 */
static matrix<double> parseMatrixResult(std::string& xml_result)
{
  std::sregex_iterator match_iter{xml_result.begin(), xml_result.end(), regx};
  std::sregex_iterator last_match;

  if (match_iter == last_match) throw "Empty result";

  std::string result = (*match_iter).str(2);

  ++match_iter;

  if (match_iter != last_match) throw "Too many results";

  return matrix<double>{result};
}

/**
 * Same as parseMatrixResult, but just convert the string to a double
 */
static double parseScalarResult(std::string& xml_result)
{
  std::sregex_iterator match_iter{xml_result.begin(), xml_result.end(), regx};
  std::sregex_iterator last_match;

  if (match_iter == last_match) throw "Empty result";

  std::string str{(*match_iter).str(2)};
  
  ++match_iter;

  if (match_iter != last_match) throw "Too many results";

  double result = strtod(str.c_str(), nullptr);

  return result;
}

/**
 * This function generates a double that is in the range [-1e9, 1e9].
 */
static double randDouble()
{
  std::random_device rand;

  // generate values from [-1,1]
  double normalized = 2.0*(static_cast<double>(rand()) / rand.max()) - 1.0;

  // expand range [-1e9,1e9]
  return normalized * 1e9;
}

/**
 * This function creates a matrix with randomly generated entries.
 */
static matrix<double> generateMatrix(unsigned int rows, unsigned int cols)
{
  matrix<double> mat{rows, cols};
  for (unsigned int i = 0; i < rows; ++i)
  {
    for (unsigned int j = 0; j < cols; ++j)
    {
      mat(i,j) = randDouble();
    }
  }
  
  return mat;
}

/**
 * This function is used to generate matrix dimensions.
 * It only generates integers in the range [2,10]
 */
static inline unsigned int randUint()
{
  std::random_device rand;
  return (rand() % 8) + 2;
}

bool testScalarAddition(Verifier& verifier)
{
  std::random_device rand;
  unsigned int rows = randUint(), cols = randUint();
  matrix<double> m1 = generateMatrix(rows, cols);
  double scalar = randDouble();

  std::string xml_request = "<add>\n";
  xml_request += formatArgs(m1, scalar);
  xml_request += "</add>\n";

  std::string xml_response = verifier.send_request(xml_request);

  matrix<double> expected = parseMatrixResult(xml_response);

  auto result = m1 + scalar;

  return result == expected;
}

bool testScalarSubtraction(Verifier& verifier)
{ 
  std::random_device rand;
  unsigned int rows = randUint(), cols = randUint();
  matrix<double> m1 = generateMatrix(rows, cols);
  double scalar = randDouble();
 
  std::string xml_request = "<sub>\n";
  xml_request += formatArgs(m1, scalar);
  xml_request += "</sub>\n";

  auto xml_result = verifier.send_request(xml_request);

  auto expected = parseMatrixResult(xml_result);

  auto result = m1 - scalar;

  return result == expected;
}

bool testScalarMultiplication(Verifier& verifier)
{
  std::random_device rand;
  unsigned int rows = randUint(), cols = randUint();
  auto mat = generateMatrix(rows, cols);
  double scalar = randDouble();

  std::string xml_request = "<mul>\n" + formatArgs(mat, scalar) + "</mul>";

  auto xml_response = verifier.send_request(xml_request);

  auto expected = parseMatrixResult(xml_response);

  auto result = mat * scalar;

  return result == expected;
}

bool testScalarDivision(Verifier& verifier)
{
  std::random_device rand;
  unsigned int rows = randUint(), cols = randUint();
  auto mat = generateMatrix(rows, cols);
  double scalar = randDouble();

  std::string xml_request = "<div>\n"  + formatArgs(mat, scalar) + "</div>";
  
  auto xml_response = verifier.send_request(xml_request);

  auto expected = parseMatrixResult(xml_response);

  auto result = mat / scalar;

  return result == expected;
}

bool testMatrixMultiplication(Verifier& verifier)
{
  std::random_device rand;
  unsigned int m1_rows = randUint(), m1_cols = randUint();
  unsigned int m2_cols = randUint();
  auto m1 = generateMatrix(m1_rows, m1_cols); 
  auto m2 = generateMatrix(m1_cols, m2_cols);

  std::string xml_request = "<mul>\n" + formatArgs(m1, m2) + "</mul>";

  auto xml_response = verifier.send_request(xml_request);

  auto expected = parseMatrixResult(xml_response);

  auto result = m1 * m2;

  return result == expected;
}

bool testMatrixAddition(Verifier& verifier)
{
  std::random_device rand;
  unsigned int rows = randUint(), cols = randUint();
  auto m1 = generateMatrix(rows, cols);
  auto m2 = generateMatrix(rows, cols);

  auto xml_request = "<add>\n" + formatArgs(m1, m2) + "</add>";

  auto xml_response = verifier.send_request(xml_request);

  auto expected = parseMatrixResult(xml_response);

  auto result = m1 + m2;

  return result == expected;
}

bool testMatrixSubtraction(Verifier& verifier)
{
  std::random_device rand;
  unsigned int rows = randUint(), cols = randUint();
  auto m1 = generateMatrix(rows, cols);
  auto m2 = generateMatrix(rows, cols);

  auto xml_request = "<sub>\n" + formatArgs(m1, m2) + "</sub>";

  auto xml_response = verifier.send_request(xml_request);

  auto expected = parseMatrixResult(xml_response);

  auto result = m1 - m2;

  return result == expected;
}

bool testInverse(Verifier& verifier)
{
  std::random_device rand;
  unsigned int rows = randUint();
  auto m = generateMatrix(rows, rows);

  auto xml_request = "<inv>\n" + formatArg(m) + "</inv>";

  auto xml_response = verifier.send_request(xml_request);

  auto expected = parseMatrixResult(xml_response);

  auto result = ~m;

  return result == expected;
}

static bool almostEqual(double a, double b, double epsilon)
{
  auto threshold = std::numeric_limits<double>::min();
  auto min = std::min(std::abs(a), std::abs(b));

  if (std::abs(min) == 0.0)
    return std::abs(a-b) < epsilon;

  return (std::abs(a-b) / std::max(threshold, min)) < epsilon;
}

bool testDeterminant(Verifier& verifier)
{
  std::random_device rand;
  unsigned int rows = randUint();
  auto m = generateMatrix(rows, rows);

  auto xml_request = "<det>\n" + formatArg(m) + "</det>";

  auto xml_response = verifier.send_request(xml_request);

  auto expected = parseScalarResult(xml_response);

  auto result = m.determinant();

  return almostEqual(result, expected, 1e9);
}