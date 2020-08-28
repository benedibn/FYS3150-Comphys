#include "TridiagonalMatrix.hpp"
#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

void TridiagonalMatrix::initialize(vec a, vec b, vec c){
  /*Initializes the triangular matrix with 3 vectors. Their sizes must be correct for this to work*/
  /*An exception should be added to stop this if the sizes are wrong*/
  m_N = b.n_rows;
  if (a.n_rows != m_N-1 || c.n_rows != m_N-1){
    cout << "These vectors are not the right size. To make the matrix you need: |a| = |c| = |b| -1 \n";
  }
  else{
    m_a = a;
    m_b = b;
    m_c = c;
  }
}
vec TridiagonalMatrix::rightMultiplication(vec v){
  /*Matrix vector multiplication from the right: u = Av*/
  if (v.n_rows != m_N){
    cout << "The dimension of v is: " << v.n_rows << ", it's supposed to be: " << m_N << endl;
  }
  vec u(m_N);

  u[0] = v[0]*m_b[0] + v[1]*m_c[0];

  for (int i = 1; i < m_N-1; i++){
    /*This for loop calculate all rows except the first and the last*/
    u[i] = v[i-1]*m_a[i-1] + v[i]*m_b[i] + v[i+1]*m_c[i];
  }
  u[m_N-1] = v[m_N-2]*m_a[m_N-2] + v[m_N-1]*m_b[m_N-1];

  return u;
}

vec TridiagonalMatrix::leftMultiplication(vec v){
  /*Matrix-vector multiplication for the left: u^T = v^T*/
  if (v.n_rows != m_N){
    cout << "The dimension of v is: " << v.n_rows << ", it's supposed to be: " << m_N << endl;
  }
  vec u(m_N);

  u[0] = v[0]*m_b[0] + v[1]*m_a[0];

  for (int i = 1; i < m_N-1; i++){
    /*This for loop calculate all rows except the first and the last*/
    u[i] = v[i-1]*m_c[i-1] + v[i]*m_b[i] + v[i+1]*m_a[i];
  }
  u[m_N-1] = v[m_N-2]*m_c[m_N-2] + v[m_N-1]*m_b[m_N-1];

  return u;
}

bool TridiagonalMatrix::checkVector(vec v){
  if (v.n_rows == m_N){return true;}
  return false;
}








int o = 0;
