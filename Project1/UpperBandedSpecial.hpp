#ifndef UPPERBANDEDSPECIAL_HPP
#define UPPERBANDEDSPECIAL_HPP
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

class UpperBandedSpecial{
private:
  vec m_g;
  double m_c;
  int m_N, m_FLOP;

public:
  UpperBandedSpecial(vec&, double&);
  vec solve(vec&);
  int getFLOP();
};

#endif
