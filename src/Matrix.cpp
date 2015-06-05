#include "Matrix.h"
#include <stdexcept>

Matrix operator*(const Matrix& a, const Matrix& b)
{
  if(a.mC != b.mR)
    throw std::runtime_error("Dimension mismatch.");

  int rows1 = a.mR;
  int cols1 = a.mC;
  int cols2 = b.mC;

  Matrix result(rows1, cols2);

  for (int k = 0; k < rows1; k++)
    for (int i = 0; i < cols2; i++)
      for (int j = 0; j < cols1; j++)
	result(k, i) += a(k, j) * b(j, i);

  return result;
}

