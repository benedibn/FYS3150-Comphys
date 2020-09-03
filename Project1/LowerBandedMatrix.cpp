#include "LowerBandedMatrix.hpp"
#include <iostream>

LowerBandedMatrix::LowerBandedMatrix(vec& h){
  m_h = h;
  m_N = m_h.n_rows +1;
  m_FLOP = 0;
}


vec LowerBandedMatrix::solve(vec& b){
  /*
  Solves the equation Lx = b for x.
  Counts floating point operations (FLOPS).
  */
  vec& x = b; //Temporary (wrong) solution to make the program copmile and run.
  return x;
}
int LowerBandedMatrix::getFLOP(){
  return m_FLOP;
}
