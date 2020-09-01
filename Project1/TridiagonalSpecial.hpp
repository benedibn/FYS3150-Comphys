#ifndef TRIDIAGONALSPECIAL_HPP
#define TRIDIAGONALSPECIAL_HPP
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class TridiagonalSpecial{
private:
  double m_a, m_b, m_c;
  int m_N,m_FLOP;

public:
  TridiagonalSpecial(int&, double&, double&, double&);
  vec rightMultiplication(vec&);
  bool checkVector(vec&);
  vec solve(vec&);
  int getFLOP();
};

#endif
