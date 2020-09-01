#include "UpperBandedMatrix.hpp"
#include <iostream>

UpperBandedMatrix::UpperBandedMatrix(vec& g, vec& c){
  m_g = g;
  m_c = c;
  m_N = m_g.n_rows;
  m_FLOP = 0;
}

vec UpperBandedMatrix::solve(vec& b){
  /*
  Solves the equation Ux = b for x.
  Counts floating point operations (FLOPS).
  */
  vec& x = b; //Temporary (wrong) solution to make the program compile and run.
  return x;
}

int UpperBandedMatrix::getFLOP(){
  return m_FLOP;
}
