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
  mat A;
  mat m_V;
  vec m_lambda;


//  mat initialize(vec,vec);
  void findCS(double&, double&, double&, double&, double&);
  vec eigenFunc(double);
  bool testSelection();
  //bool testEigenVectors();
public:
  int simTran;
//JacobiSolver(vec,vec);
  JacobiSolver(double a, double b, int N, double V(double rho));
  vec solve();
  void writeToFile(ofstream&);
  vec getLambda();
  bool unitTests();
  void selection(double&, int&, int&, mat);
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
}


#endif
