
#include "JacobiSolver.hpp"
#include <fstream>
#include <armadillo>
#include "JacobiSolver.cpp"

using namespace std;
using namespace arma;

double V(double rho);

int main(int argc, char const *argv[]){
  /*(void) argc;*/

  int N = atoi(argv[1]);
  string problem = string(argv[2]);

  if (problem == "bucklingbeam"){

    string fileName = problem + ".txt";
    ofstream file;
    file.open(fileName);
    double a = 0;
    double b = 1;
    JacobiSolver J(a,b,N,V);
    cout << "hallo" << endl;
/*
    if (J.unitTests(V)){
      cout << "it worked\n";
    }
*/
    J.solve();
    J.writeToFile(file);
    file.close();
  }

  return 0;
}

double V(double rho){
  return 0.;
}
