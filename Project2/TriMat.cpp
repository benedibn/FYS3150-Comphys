#include "EigenValueSolver.hpp"
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;


TriMat::TriMat(int a, int d, int N){
  /*Initializes the matrix*/
  m_a = a;
  m_d = d;
  m_N = N;
}
vec TriMat::findEigenValues(){
  /*returns a vector of eigenvalues*/
  mat A(m_N,m_N,fill::zeros);
  A(0,0) = m_d; A(0,1) = m_a;
  A(m_N-1,m_N-1) = m_d; A(m_N-1,m_N-2) = m_a;
  for (int i = 1; i < m_N - 1; i++){
    A(i,i) = m_d;
    A(i,i-1) = m_a;
    A(i,i+1) = m_a;
  }
  vec diag(m_N);
  return eig_sym(A);
}
