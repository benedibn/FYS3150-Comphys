#include "EigenValueSolver.hpp"
#include <fstream>
#include <armadillo>
#include "EigenValueSolver.cpp"
#include "JacobiSolver.cpp"
#include "ArmaSolver.cpp"

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]){
  (void) argc; (void) argv;

  int N = 6;
  double a = -1;
  double d = 2;

  vec va(N-1,fill::ones);
  va *= a;
  vec vd(N,fill::ones);
  vd *= d;

  string fileName = "Eigenvalue.txt";
  ofstream file;
  file.open(fileName);

  cout << "The numer of iterations the Jacobi method needed to make the off diagonal elements smaller than the tolerance" << endl;
  cout << "dimension:    " << "iterations:" << endl;
  for (int i = 3; i < 10; i++){
    JacobiSolver J(a,d,i);
    J.solve();
    J.writeToFile(file);
    J.~JacobiSolver();
  }


  file.close();


  return 0;
}
