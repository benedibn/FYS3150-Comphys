#include "TridiagonalMatrix.hpp"
#include <iostream>
#include <cmath>
#include "armadillo"

using namespace std;
using namespace arma;

int main(int argc, char const *argv[]){
  vec a(2), b(3), c(2);
  a(0) = 1.; a(1) = 2.;
  b(0) = 1.; b(1) = 2.; b(2) = 3.;
  c(0) = 1.; c(1) = 2.;
  TridiagonalMatrix triMat;
  triMat.initialize(a,b,c);
  vec v(3);
  v(0) = 1.; v(1) = 2.; v(2) = 1.;
  if (!triMat.checkVector(v)){
    cout << "The vector dimension does not match the matrix \n";
    return 1;
  }
  vec u;
  u = triMat.rightMultiplication(v);
  for (int i = 0; i < u.n_rows; i++){
    cout << u[i] << endl;
  }
  return 0;
}
