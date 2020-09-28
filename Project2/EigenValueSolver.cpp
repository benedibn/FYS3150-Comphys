#include "EigenValueSolver.hpp"
<<<<<<< HEAD
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

EigenValueSolver::EigenValueSolver(double a, double d, int N){
  /*Initializes the matrix*/
  m_N = N;
  m_A = mat(m_N,m_N,fill::zeros);
  m_A(0,0) = d; m_A(0,1) = a;
  m_A(m_N-1,m_N-1) = d; m_A(m_N-1,m_N-2) = a;
  for (int i = 1; i < m_N - 1; i++){
    m_A(i,i) = d;
    m_A(i,i-1) = a;
    m_A(i,i+1) = a;
  }
=======


void TridiagonalMatrixSolver::initialize(int N, double lambda)
{
  m_N = N;
  double h = 1./(m_N+1); //Local variable, only needed in this function.
  m_q = vec(m_N);
  m_v = vec(m_N);
  m_x = linspace(h, 1-h, m_N); //Only interior points of the mesh.
  m_q = h*h*f(m_x);
}

void TridiagonalMatrixSolver::write_to_file(string filename)
{
  m_ofile.open(filename);
  for (int i = 0; i < m_N; i++){
    m_ofile << m_x(i) << " " << m_v(i) << endl;
  }
  m_ofile.close();
>>>>>>> 0a97263b71751cd2bae799d7eb8de9e89da18de3
}
