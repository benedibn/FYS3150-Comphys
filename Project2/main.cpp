#include "JacobiSolver.hpp"
#include <fstream>
#include <armadillo>
<<<<<<< HEAD
//#include "EigenValueSolver.cpp"
//#include "JacobiSolver.cpp"
//#include "ArmaSolver.cpp"
=======
#include "JacobiSolver.cpp"
>>>>>>> 962985443d67e7ce8c278a5ac3d4f747d4b2d1c9

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]){
  (void) argc; (void) argv;

  int N = 3;
  double a = -1;
  double d = 2;

  vec va(N-1,fill::ones);
  va *= a;
  vec vd(N,fill::ones);
  vd *= d;

  string fileName = "Eigenvalue.txt";
  ofstream file;
  file.open(fileName);
<<<<<<< HEAD

  cout << "The numer of iterations the Jacobi method needed to make the off diagonal elements smaller than the tolerance" << endl;
  cout << "dimension:    " << "iterations:" << endl;
  for (int i = 3; i < 10; i++){
    JacobiSolver J(a,d,i);
    J.solve();
    J.writeToFile(file);
    J.~JacobiSolver();
=======
  JacobiSolver J(a,d,N);
  if (J.unitTests()){
    cout << "it worked\n";
>>>>>>> 962985443d67e7ce8c278a5ac3d4f747d4b2d1c9
  }
  J.solve();
  J.writeToFile(file);


  file.close();


  return 0;
}
