#ifndef TRIDIAGONALMATRIX_HPP
#define TRIDIAGONALMATRIX_HPP
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class TridiagonalMatrix{
private:
  vec m_a, m_b, m_c, m_v, m_u;
  int m_N;

public:
  void initialize(vec a, vec b, vec c);
  vec rightMultiplication(vec v);
  vec leftMultiplication(vec v);
  bool checkVector(vec v);
  void decompose();
};

#endif
