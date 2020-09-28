#include "EigenValueSolver.hpp"
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

vec ArmaSolver::solve(){
  /*returns a vector of eigenvalues*/
  return eig_sym(m_A);
}
