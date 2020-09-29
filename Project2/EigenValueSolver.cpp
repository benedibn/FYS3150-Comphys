#include "EigenValueSolver.hpp"
<<<<<<< HEAD
<<<<<<< HEAD
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;


EigenValueSolver::EigenValueSolver(int a, int d, int N){
  /*Initializes the matrix*/
  m_a = a;
  m_d = d;
  m_N = N;
}

/*
void EigenValueSolver::write_to_file(string filename){
}
*/
=======
=======
<<<<<<< HEAD
>>>>>>> d63e2852cb13728ae1ced03b7a677d850bfb769b


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
=======
=======
>>>>>>> 0d003a1d584f2fbad57c3d025e22dd47eaf408cd
#include <armadillo>
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
<<<<<<< HEAD
>>>>>>> 7d56601e0e21ce58f22707d3a2e2283f4dcf8ffd
=======
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
>>>>>>> 0d003a1d584f2fbad57c3d025e22dd47eaf408cd
}
void EigenValueSolver::writeToFile(ofstream& file){

  for (int i = 0; i < m_lambda.n_rows; i++){
    file << m_lambda(i) << " ";
  }
  file << endl;
}
>>>>>>> 0a97263b71751cd2bae799d7eb8de9e89da18de3
