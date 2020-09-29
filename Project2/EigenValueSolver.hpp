#ifndef EigenValueSolver_HPP
#define EigenValueSolver_HPP
#include <fstream>
#include <armadillo>
#include <iostream>

using namespace std;
using namespace arma;

class EigenValueSolver{
protected:
  int m_N;
  mat m_A;
  vec m_lambda;

  EigenValueSolver(vec,vec);
  EigenValueSolver(double, double, int);

public:
  void writeToFile(ofstream&);
};

class JacobiSolver : public EigenValueSolver{
private:
  void findCS(double&, double&, double&, double&, double&);
public:
  JacobiSolver(double a, double d, int N) : EigenValueSolver(a, d, N){}
  JacobiSolver(vec a, vec d) : EigenValueSolver(a, d){}
  vec solve();
};

class ArmaSolver : public EigenValueSolver{
public:
  ArmaSolver(double a, double d, int N) : EigenValueSolver(a, d, N){}
  ArmaSolver(vec a, vec d) : EigenValueSolver(a, d){}
  vec solve();
};

namespace tFunk{
  int sign(double& x){
    if (x < 0){
      return -1;
    }
    return 1;
  }


  template<typename Base, typename T>
  inline bool instanceOf(const T*){
    return  is_base_of<Base, T>::value;
  }
}


#endif
