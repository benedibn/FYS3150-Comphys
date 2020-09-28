#include "EigenValueSolver.hpp"
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

void findCS(double& d1, double& d2, double& a, double& c, double& s){
  double tau = (d1-d2)/(2*a);
  double t = -tau + sign(tau)*sqrt(1+pow(tau,2));
  c = 1/(sqrt(1+pow(t,2)));
  s = c*t;
}

int sign(double& x){
  if (x < 0){
    return -1;
  }
  return 1;
}
