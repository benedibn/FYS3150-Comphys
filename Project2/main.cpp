#include "EigenValueSolver.hpp"
#include <fstream>
#include <armadillo>
#include "TriMat.cpp"
#include "functions.cpp"

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]){
  double d = 2.;
  double a = -1.;
  int N = 2;
  TriMat aTriMat(a,d,N);
  vec eigen(N);
  vec eigen2(N);
  eigen = aTriMat.findEigenValues();
  for (int i = 0; i < N; i++){
    cout << eigen(i) << endl;
  }
  cout << "------------------------------\n";
  eigen2 = aTriMat.jacobiEigen(10);
  for (int i = 0; i < N; i++){
    cout << eigen2(i) << endl;
  }

  return 0;
}
