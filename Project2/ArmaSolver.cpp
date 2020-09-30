#include "EigenValueSolver.hpp"
//#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

vec ArmaSolver::solve(){
  /*returns a vector of eigenvalues*/
  if (m_lambda(0) != 0 || m_lambda(m_N-1) != 0){
    /*
    Because the vector is sorted in increasing order, every element is 0 if the endpoints are
    */
    return m_lambda;
  }
  m_lambda = eig_sym(m_A);

  return m_lambda;
}
