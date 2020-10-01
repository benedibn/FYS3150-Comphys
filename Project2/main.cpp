#include "JacobiSolver.hpp"
#include <fstream>
#include <armadillo>
#include "JacobiSolver.cpp"

using namespace std;
using namespace arma;

double V_0(double rho);
double V_1(double rho);
double V_2(double rho);

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
    JacobiSolver J(a,b,N,V_0);
/*
    if (J.unitTests(V)){
      cout << "it worked\n";
    }
*/
    J.solve();
    J.writeToFile(file);
    file.close();
  }

  if (problem == "oneelectron"){
    string fileName = problem + ".txt";
    ofstream file;
    file.open(fileName);
    double a = 0;
    double b = 6;
    JacobiSolver J(a,b,N,V_1);

    J.solve();
    J.writeToFile(file);
    file.close();
  }

  if (problem == "twoelectrons"){
    string fileName = problem + ".txt";
    ofstream file;
    file.open(fileName);
    double a = 0;
    double b = 1;
    JacobiSolver J(a,b,N,V_2);

    J.solve();
    J.writeToFile(file);
    file.close();
  }

  return 0;
}


double V_0(double rho){
  return 0.;
}
double V_1(double rho){
  return rho*rho;
}
double V_2(double rho){
  double omega = 0.01;
  return omega*rho*rho + 1./rho;
}
