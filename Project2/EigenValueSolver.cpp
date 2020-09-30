#include "EigenValueSolver.hpp"
//#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;
using namespace tFunk;

EigenValueSolver::EigenValueSolver(double a, double d, int N){
  /*Initializes the matrix with numbers*/
  m_N = N;
  m_lambda = vec(m_N,fill::zeros);
  m_A = mat(m_N,m_N,fill::zeros);
  m_A(0,0) = d; m_A(0,1) = a;
  m_A(m_N-1,m_N-1) = d; m_A(m_N-1,m_N-2) = a;
  for (int i = 1; i < m_N - 1; i++){
    m_A(i,i) = d;
    m_A(i,i-1) = a;
    m_A(i,i+1) = a;
  }
}
EigenValueSolver::EigenValueSolver(vec a, vec d){
  /*
  Initializes the matrix with vectors
  */

  m_N = d.n_rows;

  m_lambda = vec(m_N,fill::zeros);
  m_A = mat(m_N,m_N,fill::zeros);
  m_A(0,0) = d(0); m_A(0,1) = a(0);
  m_A(m_N-1,m_N-1) = d(m_N-1); m_A(m_N-1,m_N-2) = a(m_N-2);
  for (int i = 1; i < m_N - 1; i++){
    m_A(i,i) = d(i);
    m_A(i,i-1) = a(i-1);
    m_A(i,i+1) = a(i);
  }
}
void EigenValueSolver::writeToFile(ofstream& file){

  for (int i = 0; i < m_lambda.n_rows; i++){
    file << m_lambda(i) << " ";
  }
  file << endl;
}
