#include "TridiagonalMatrix.hpp"
#include "UpperBandedMatrix.hpp"
#include "LowerBandedMatrix.hpp"
#include <iostream>

using namespace std;

TridiagonalMatrix::TridiagonalMatrix(vec& a, vec& b, vec& c){
  /*
  Initializes the triangular matrix with 3 vectors. Their sizes must be correct for this to work
  */
  m_N = (b).n_rows;
  if ((a).n_rows != m_N-1 || (c).n_rows != m_N-1){
    cout << "These vectors are not the right size. To make the matrix you need: |a| = |c| = |b| -1 \n";
  }
  else{
    m_a = a;
    m_b = b;
    m_c = c;
    m_FLOP = 0;   //Number of floating point operators.
  }
}
vec TridiagonalMatrix::rightMultiplication(vec& p){
  /*Matrix vector multiplication from the right: u = Av*/
  if (p.n_rows != m_N){
    cout << "The dimension of v is: " << p.n_rows << ", it's supposed to be: " << m_N << endl;
  }
  vec u(m_N);

  u[0] = p[0] * m_b[0] + p[1] * m_c[0];

  for (int i = 1; i < m_N-1; i++){
    /*This for loop calculate all rows except the first and the last*/
    u[i] = p[i-1] * m_a[i-1] + p[i] * m_b[i] + p[i+1] * m_c[i];
  }
  u[m_N-1] = p[m_N-2] * m_a[m_N-2] + p[m_N-1] * m_b[m_N-1];
  m_FLOP += (6 + (m_N-2)*5);
  return u;
}


bool TridiagonalMatrix::checkVector(vec& v){
  if (v.n_rows == m_N){return true;}
  return false;
}

vec TridiagonalMatrix::solve(vec& v){
  /*
  The upper bound matrix is defined by two vectors 'g', and 'm_c'.
  The lower bound matrix is defined by 'h'. 'g' and 'h' are defined below.
  */
  vec g(m_N);
  vec h(m_N-1);
  g[0] = m_b[0];
  for (int i = 0; i < m_N-1; i++){
    /*
    This for loop defines the elements in the UL matrices.
    the 'g' elements correspond to the elements on the diagonal after a row operation
    has made that column into a pivot column.
    The 'h' elements are the elements below the diagonal on the inverse product
    of the row operation matrices.
    In simpler terms, each element in 'h' correspond to a row operation.
    */
    g[i+1] = m_b[i+1] - (m_a[i]*m_c[i])/g[i];
    h[i] = g[i]/m_b[i];
  }
  m_FLOP += (4*(m_N-2)); //Amount of FLOPs in the for loop
  UpperBandedMatrix U(g,m_c);
  LowerBandedMatrix L(h);

  vec solution, tempSolution;
  tempSolution = L.solve(v);
  m_FLOP += L.getFLOP();
  solution = U.solve(tempSolution);
  m_FLOP += U.getFLOP();
  return solution;
}
int TridiagonalMatrix::getFLOP(){
  return m_FLOP;
}
