#ifndef EigenValueSolver_HPP
#define EigenValueSolver_HPP
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;

class EigenValueSolver{
protected:
  int m_N;
  mat m_A;

public:
  EigenValueSolver(double, double, int);
  //void writeToFile();
};

class JacobiSolver : public EigenValueSolver{
private:
  void findCS(double&, double&, double&, double&, double&);
public:
  JacobiSolver(double a, double d, int N) : EigenValueSolver(a, d, N){
    cout << "made jacobi solver \n";
  };
  vec solve(int);
  vec solve();
};

class ArmaSolver : public EigenValueSolver{
public:
  ArmaSolver(double a, double d, int N) : EigenValueSolver(a, d, N){
    cout << "made arma solver\n";
  };
  vec solve();
};

namespace tFunk{
  int sign(double& x){
    if (x < 0){
      return -1;
    }
    return 1;
  }
}









#endif
