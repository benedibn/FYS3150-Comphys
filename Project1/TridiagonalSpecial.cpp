#include "TridiagonalSpecial.hpp"
#include "UpperBandedSpecial.hpp"
#include "LowerBandedMatrix.hpp"
#include <iostream>

using namespace std;

TridiagonalSpecial::TridiagonalSpecial(int& n, double& a, double& b, double& c){
  /*
  Initializes the triangular matrix with 3 doubles
  */
  m_N = n;
  m_a = a;
  m_b = b;
  m_c = c;
  m_FLOP = 0;   //Number of floating point operators.
}
vec TridiagonalSpecial::rightMultiplication(vec& p){
  /*Matrix vector multiplication from the right: u = Av*/
  if (p.n_rows != m_N){
    cout << "The dimension of v is: " << p.n_rows << ", it's supposed to be: " << m_N << endl;
  }
  vec u(m_N);

  u[0] = p[0] * m_b + p[1] * m_c;

  for (int i = 1; i < m_N-1; i++){
    /*This for loop calculate all rows except the first and the last*/
    u[i] = p[i-1] * m_a + p[i] * m_b + p[i+1] * m_c;
  }
  u[m_N-1] = p[m_N-2] * m_a + p[m_N-1] * m_b;
  m_FLOP += (6 + (m_N-2)*5);
  return u;
}


bool TridiagonalSpecial::checkVector(vec& v){
  if (v.n_rows == m_N){return true;}
  return false;
}

vec TridiagonalSpecial::solve(vec& v){
  /*
  The upper bound matrix is defined by two vectors 'g', and 'm_c'.
  The lower bound matrix is defined by 'h'. 'g' and 'h' are defined below.
  */
  vec g(m_N);
  vec h(m_N-1);
  g[0] = m_b;
  double aDotC; //a*c
  for (int i = 0; i < m_N-1; i++){
    /*
    This for loop defines the elements in the UL matrices.
    the 'g' elements correspond to the elements on the diagonal after a row operation
    has made that column into a pivot column.
    The 'h' elements are the elements below the diagonal on the inverse product
    of the row operation matrices.
    In simpler terms, each element in 'h' correspond to a row operation.
    */
    g[i+1] = m_b - aDotC/g[i];
    h[i] = g[i]/m_b;
  }
  m_FLOP += (3*(m_N-2)); //Amount of FLOPs in the for loop
  UpperBandedSpecial U(g,m_c);
  LowerBandedMatrix L(h);

  vec solution, tempSolution;
  tempSolution = L.solve(v);
  m_FLOP += L.getFLOP();
  solution = U.solve(tempSolution);
  m_FLOP += U.getFLOP();
  return solution;
}
int TridiagonalSpecial::getFLOP(){
  return m_FLOP;
}
