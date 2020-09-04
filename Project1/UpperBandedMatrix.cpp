#include "UpperBandedMatrix.hpp"
#include <iostream>

UpperBandedMatrix::UpperBandedMatrix(vec& g, vec& c){
  m_g = g;
  m_c = c;
  m_N = m_g.n_rows;
  m_FLOP = 0;
}

vec UpperBandedMatrix::solve(vec& u){
  /*
  Solves the equation Uv = u for v.
  Counts floating point operations (FLOPS).
  */
  vec v(m_N);

  v[m_N-1] = u[m_N-1]/m_g[m_N-1];
  for (int i = m_N-2; i >= 0; i--){
    v[i] = (u[i] - m_c[i]*v[i+1])/m_g[i];
  }
  m_FLOP += 3*m_N - 2;
  return v;
}

int UpperBandedMatrix::getFLOP(){
  return m_FLOP;
}
