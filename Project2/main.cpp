<<<<<<< HEAD
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>

using namespace arma;
=======
#include "EigenValueSolver.hpp"
#include <fstream>
#include <armadillo>
#include "TriMat.cpp"

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]){
  double d = 2.;
  double a = -1.;
  int N = 2;
  TriMat aTriMat(a,d,N);
  vec eigen(N);
  eigen = aTriMat.findEigenValues();
  for (int i = 0; i < N; i++){
    cout << eigen(i) << endl;
  }


  return 0;
}
>>>>>>> c0e13af333f4e8647b448ed0babc0a688389dae2
