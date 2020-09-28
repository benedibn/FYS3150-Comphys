#include "EigenValueSolver.hpp"
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
