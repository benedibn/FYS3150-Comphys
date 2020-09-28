#ifndef EigenValueSolver_HPP
#define EigenValueSolver_HPP
#include <fstream>
#include <armadillo>

using namespace std;
using namespace arma;

class EigenValueSolver{
protected:
  int m_N;
  double m_a;
  double m_d;

public:
  EigenValueSolver(int, int, int);
  vec findEigenValues();
  vec jacobiEigen(int);
};


void findCS(double&, double&, double&, double&, double&);
int sign(double&);





















#endif
