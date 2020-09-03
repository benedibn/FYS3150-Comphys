#ifndef TRIDIAGONALMATRIX_HPP
#define TRIDIAGONALMATRIX_HPP
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class TridiagonalMatrix{
private:
  vec m_a, m_b, m_c;
  int m_N, m_FLOP;

public:
  TridiagonalMatrix(vec&, vec&, vec&);
  vec rightMultiplication(vec&);
  bool checkVector(vec&);
  vec solve(vec&);
  int getFLOP();
};

#endif
