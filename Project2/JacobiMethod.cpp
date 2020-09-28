#include "EigenValueSolver.hpp"
#include <armadillo>
#include <fstream>

using namespace std;
using namespace arma;

vec TriMat::jacobiEigen(int n){
  /*Find approximate eigenvalues by using Jacobis method*/
  mat A(m_N,m_N,fill::zeros);
  A(0,0) = m_d; A(m_N-1,m_N-1) = m_d;
  A(0,1) = m_a; A(m_N-1,m_N-2) = m_a;
  vec tempVec;
  rowvec tempRow;
  double tol = pow(10.,-8);
  for (int i = 1; i < m_N-1; i++){
    /*Fills the diagonal and sub/superdiagonals*/
    A(i,i) = m_d;
    A(i,i+1) = m_a;
    A(i,i-1) = m_a;
  }
  int maxi = 0, maxj = 0;
  double maxa;
  double c, s;
  for (int k = 0; k < n; k++){
    /*Transforms the matrix n times*/
    maxa = 0;
    for (int i = 0; i < m_N-1; i++){
      /*Loops over all rows except the last one*/
      for (int j = i+1; j < m_N; j++){
        /*Loops over all elements to the right of the diagonal in a given row*/
        if (abs(A[i,j]) > abs(maxa)){
          maxi = i;
          maxj = j;
          maxa = A[maxi,maxj];
        }
      }
    }
    if (abs(maxa) < tol){
      cout << "The method needed " << k << " iterations to make the off diagonal elements smaller than " << tol << endl;
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

  }
  vec lambda(m_N);
  for (int i = 0; i < m_N; i++){
    lambda(i) = A(i,i);
  }
  return lambda;
}
