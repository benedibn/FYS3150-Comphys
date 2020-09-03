#ifndef UPPERBANDEDMATRIX_HPP
#define UPPERBANDEDMATRIX_HPP
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class UpperBandedMatrix{
private:
  vec m_g, m_c;
  int m_N, m_FLOP;

public:
  UpperBandedMatrix(vec&, vec&);
  vec solve(vec&);
  int getFLOP();
};

#endif
