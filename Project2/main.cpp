#include "JacobiSolver.hpp"
#include <fstream>
#include <armadillo>
#include "JacobiSolver.cpp"

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
  JacobiSolver J(a,d,N);
  if (J.unitTests()){
    cout << "it worked\n";
  }
  J.solve();
  J.writeToFile(file);


  file.close();


  return 0;
}
