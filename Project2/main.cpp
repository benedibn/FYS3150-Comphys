#include "JacobiSolver.hpp"
#include <fstream>
#include <armadillo>
#include "JacobiSolver.cpp"

using namespace std;
using namespace arma;

double V_0(double rho);
double V_1(double rho);
double V_2(double rho);
double omega;

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
    double omega_r[] = {0.01, 0.5, 1, 5};

    for (int i = 0; i < 4; i++){
      string fileName = problem +"_omega_"+to_string(i)+".txt";
      ofstream file;
      file.open(fileName);
      double a = 0;
      double b = 5;
      omega = omega_r[i];

      JacobiSolver J(a,b,N,V_2);
      J.solve();
      J.writeToFile(file);
      file.close();
    }
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
  return omega*omega*rho*rho + 1./rho;
}
