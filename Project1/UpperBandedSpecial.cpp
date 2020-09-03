#include "UpperBandedSpecial.hpp"
#include <iostream>

UpperBandedSpecial::UpperBandedSpecial(vec& g, double& c){
  m_g = g;
  m_c = c;
  m_N = m_g.n_rows;
  m_FLOP = 0;
}

vec UpperBandedSpecial::solve(vec& b){
  /*
  Solves the equation Ux = b for x.
  Counts floating point operations (FLOPS).
  */
  vec& x = b; //Temporary (wrong) solution to make the program compile and run.
  return x;
}

int UpperBandedSpecial::getFLOP(){
  return m_FLOP;
}
