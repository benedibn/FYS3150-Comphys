#ifndef JacobiSolver_HPP
#define JacobiSolver_HPP
#include <fstream>
#include <armadillo>
#include <iostream>


using namespace std;
using namespace arma;

class JacobiSolver{
private:
  int m_N;
  mat m_A;
  mat m_V;
  vec m_lambda;

  int simTran = 0;

  mat initialize(vec,vec);
  void findCS(double&, double&, double&, double&, double&);
  vec eigenFunc(double);
  bool testSelection();
  bool testEigenVectors();
public:
  JacobiSolver(vec,vec);
  JacobiSolver(double, double, int);
  vec solve();
  void writeToFile(ofstream&);
  bool unitTests();
  void selection(double&, int&, int&, mat A);
};


namespace tFunk{
  int sign(double& x){
    if (x < 0){
      return -1;
    }
    return 1;
  }
  void writeVecToFile(ofstream& file, vec& v){
    for (int i = 0; i < v.n_rows; i++){
      file << v(i) << " ";
    }
    file << endl;
  }

  template<typename Base, typename T>
  inline bool instanceOf(const T*){
    return  is_base_of<Base, T>::value;
  }
}


#endif
