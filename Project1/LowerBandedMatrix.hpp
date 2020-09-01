#ifndef LOWERBANDEDMATRIX_HPP
#define LOWERBANDMEDATRIX_HPP
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class LowerBandedMatrix{
private:
  vec m_h;
  int m_N, m_FLOP;

public:
  LowerBandedMatrix(vec&);
  vec solve(vec&);
  int getFLOP();
};

#endif
