#include "JacobiSolver.hpp"
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;
using namespace tFunk;

JacobiSolver::JacobiSolver(double a, double b, int N, double V(double rho)){
  /*Initializes the matrix with numbers*/
  simTran = 0;
  m_N = N;
  m_lambda = vec(m_N,fill::zeros);
  double h = (b-a)*(1./(N+1));
  double hh_inv = 1./(h*h);

  vec rho = linspace(a+h,b-h, N);

  m_V = mat(m_N,m_N,fill::zeros);

  m_V(0,0) = 1; m_V(m_N-1,m_N-1) = 1;
  A = mat(m_N,m_N,fill::zeros);

  for (int i = 0; i < N - 1; i++){
    m_V(i,i) = 1;
    A(i,i) = 2*hh_inv+V(rho(i));
    A(i+1,i) = -hh_inv;
    A(i,i+1) = -hh_inv;
  }

  A(N-1, N-1) = 2*hh_inv + V(rho(N-1));
}


vec JacobiSolver::solve(){
  /*Find approximate eigenvalues by using Jacobis method*/

  if (m_lambda(0) != 0 || m_lambda(m_N-1) != 0){
    /*
    Returns the eigenvalues if they have already been found.
    Because the vector is sorted in increasing order, every element is 0 if the endpoints are
    */
    return m_lambda;
  }

  //mat A = m_A;

  vec tempVec;
  rowvec tempRow;
  double tol = 1e-8;

  int maxi = 0, maxj = 0;
  double maxa;
  double c, s;
  for (int k = 0; true; k++){
    /*Transforms the matrix n times*/
    maxa = 0;

    selection(maxa,maxi,maxj,A); //Finds max value on offdiag, and its indices
    if (pow(maxa,2) < tol){
      simTran = k;
      break;
    }
    findCS(A(maxi,maxi),A(maxj,maxj),A(maxi,maxj),c,s);  /*Finds the cosine and sine to set the largest value equal to zero*/

    /*
    The next section corresponds to the matrix multiplication AS
    */

    tempVec = A.col(maxi);
    A.col(maxi) *= c;
    A.col(maxi) -= s*A.col(maxj);
    A.col(maxj) *= c;
    A.col(maxj) += s*tempVec;

    /*
    The next section corresponds to the matrix mulitplication S^T(AS)
    */
    tempRow = A.row(maxi);
    A.row(maxi) *= c;
    A.row(maxi) -= s*A.row(maxj);
    A.row(maxj) *= c;
    A.row(maxj) += s*tempRow;

    /*
    The next section corresponds to the matrix mulitplication RS (Updates the eigenvectors)
    */

    tempVec = m_V.col(maxi);
    m_V.col(maxi) *= c;
    m_V.col(maxi) -= s*m_V.col(maxj);
    m_V.col(maxj) *= c;
    m_V.col(maxj) += s*tempVec;

  }
  vec lambda(m_N);
  for (int i = 0; i < m_N; i++){
    lambda(i) = A(i,i);
  }

  m_lambda = lambda;
  return m_lambda;
}

void JacobiSolver::findCS(double& d1, double& d2, double& a, double& c, double& s){
  /*Finds c and s*/
  double tau = (d2-d1)/(2*a);
  double t;

  double t = -tau + sign(tau)*sqrt(1+pow(tau,2));
  c = 1.0/(sqrt(1+pow(t,2)));
  s = c*t;
}
void JacobiSolver::selection(double& maxa, int& maxi, int& maxj,mat A){
  /*
  Select the largest values in upper diagonal, and it's indices
  */
  int n = A.n_rows;
  for (int i = 0; i < n-1; i++){
    /*Loops over all rows except the last one*/
    for (int j = i+1; j < n; j++){
      /*Loops over all elements to the right of the diagonal in a given row*/
      if (abs(A(i,j)) > abs(maxa)){
        maxi = i;
        maxj = j;
        maxa = A(i,j);
      }
    }
  }
}

void JacobiSolver::writeToFile(ofstream& file){
  /*
  Writes amount of iterations, analytic eigenvalues, computed eigenvalues, and calculated eigenvector of smallest eigenvalue
  */
  vec j_lambda = sort(m_lambda);

  int minLam = m_lambda.index_min();
  vec smallestEigenVec = m_V.col(minLam);
  vec a_lambda = eig_sym(A);
  file << simTran << endl;
  writeVecToFile(file, a_lambda);
  writeVecToFile(file, j_lambda);
  writeVecToFile(file, smallestEigenVec);
}
vec JacobiSolver::getLambda(){
  return m_lambda;
}

bool JacobiSolver::unitTests(){
  /*
  Makes sure both tests work
  */

  bool b1 = testSelection();
  //bool b2 = testEigenVectors();
  if (b1) {//&& b2){
    return true;
  }
  return false;
}
bool JacobiSolver::testSelection(){
  /*
  Tests if the selection algorithm picks out the highest value, and the correct indices
  */
  int n = 5;
  int i = 0, j = 0;
  double max = 0;
  mat B(n,n,fill::zeros);
  B(1,3) = 1;
  selection(max,i,j,B);
  if (i != 1 || j != 3){
    return false;
  }
  B(2,4) = 2;
  selection(max,i,j,B);
  if (i != 2 || j != 4){
    return false;
  }
  return true;
}

/*
bool JacobiSolver::testEigenVectors(){

  Tests if the eigenvalues found from The jacobi method matches the real eigenvalues


  JacobiSolver testJ(0.,1.,3.,V);
  testJ.solve();
  vec computed = sort(testJ.getLambda());
  vec calculated(3);
  mat A(3,3,fill::ones);
  A(0,0) = 2;
  A(1,1) = 2;
  A(2,2) = 2;
  A(0,2) = 0;
  A(2,0) = 0;
  calculated = eig_sym(A);

  vec diff = calculated - computed;
  double size = 0;
  for (int i = 0; i < 3; i++){
    size += abs(diff(i));
  }
  if (size < 1e-6){
    return true;
  }

  return false;

}
*/
