#include "LowerBandedMatrix.hpp"
#include <iostream>

LowerBandedMatrix::LowerBandedMatrix(vec& h){
  m_h = h;
  m_N = m_h.n_rows +1;
  m_FLOP = 0;
}


vec LowerBandedMatrix::solve(vec& b){
  /*
  Solves the equation Lu = b for u.
  Counts floating point operations (FLOPS).
  */
  vec u(m_N);
  u[0] = b[0];
  for (int i = 1; i < m_N; i++){
    u[i] = b[i] - m_h[i-1]*u[i-1];
  }
  m_FLOP += 2*(m_N-1);
  return u;
}
int LowerBandedMatrix::getFLOP(){
  /*
  Returns FLOP.
  */
  return m_FLOP;
}
