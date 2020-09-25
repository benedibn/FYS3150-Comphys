#ifndef EigenValueSolver_HPP
#define EigenValueSolver_HPP
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;

class TriMat{
private:
  int m_N;
  double m_a;
  double m_d;
public:
  TriMat(int, int, int);
  vec findEigenValues();
};























#endif
