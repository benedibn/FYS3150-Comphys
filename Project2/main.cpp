
#include "JacobiSolver.hpp"
#include <fstream>
#include <armadillo>
#include "JacobiSolver.cpp"

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]){
  /*(void) argc;*/

  int N = atoi(argv[1]);
  problem = string(argv[2]);

  double h = 1./(N+1);
  double rho_0 = 0;
  vec rho = rho(N-1,fill::ones);
  for (int i = 0; i < N; i++){
    rho[i] = rho_0 + i*h;
  }

  double a = -1./pow(h,2);
  double d = 2./pow(h,2);


  string fileName = problem + '.txt';
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
