#include "TridiagonalMatrix.hpp"
#include "UpperBandedMatrix.hpp"
#include "LowerBandedMatrix.hpp"
#include "TridiagonalSpecial.hpp"
#include "UpperBandedSpecial.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

ofstream ofile_sol, ofile_error;

double f_b(double&);
void menu();
double* general(int&);
double* special(int&);
int dimensionChoice();
double* relError(double*, double*, int&);
double* closedForm(int&);
double maxValue(double*, int&);
void writeFile(double*, double*, string&, int&);
void compareMethods(int&);


int main(int argc, char const *argv[]){
  /*
  Main function
  */
  cout << "Do you want to to compare methods or run the program? \n";
  cout << "--------------------------------------------------------\n";
  cout << "1: Compare\n";
  cout << "2: Run the program\n";
  cout << "Input: ";
  int input;
  cin >> input;
  double *u,*v;

  int n;
  if (input == 1){
    n = dimensionChoice();
    compareMethods(n);
  }
  if (input == 2){
    int input2;
    cout << "What dimension matrix do you want to plot?\n";
    cout << "------------------------------------------\n";
    cout << "1: 10\n";
    cout << "2: 100\n";
    cout << "3: 1000\n";
    cout << "4: 10000\n";
    cout << "5: 100000\n";
    cout << "6: 1000000\n";
    cout << "Input: ";
    cin >> input2;
    int nPlot = pow(10,input2);
    string errorName = "errorData.txt";
    double maxError;
    double *nList = new double[7];
    double *errList = new double[7];
    int nPow = 7;
    for (int i = 1; i < (nPow+1); i++){
      n = pow(10,i);

      v = general(n);
      u = closedForm(n);

      if (n == nPlot){
        string name = "Comparison.txt";
        writeFile(v,u,name,n);
      }
      nList[i-1] = (double) n;
      errList[i-1] = maxValue(relError(u,v,n),n);
      writeFile(nList, errList, errorName, nPow);
    }
  }


  //menu();
  return 0;
}

double f_b(double& x_i){
  return exp(-10*x_i);
}


int dimensionChoice(){
  /*
  Lets the user decide the dimension of the matrix
  */
  int n;
  while(true){
    cout << "What do you want the dimension of the square matrix to be?\n";
    cout << "----------------------------------------------------------\n";
    cout << "1: 10\n";
    cout << "2: 100\n";
    cout << "3: 1000\n";
    cout << "4: something else\n";
    cout << "Input: ";
    int input;
    cin >> input;
    if (input == 1){
      n = 10;
      break;
    }
    if (input == 2){
      n = 100;
      break;
    }
    if (input == 3){
      n = 1000;
      break;
    }
    if (input == 4){
      cout << "Dimension of the matrix: ";
      cin >> n;
      break;
    }
    cout << input << " is not a valid choice\n";
  }
  return n;
}
double* general(int& n){

  double h = 1./(1+n);

  double *a = new double[n-1], *b = new double[n], *c = new double[n-1];
  double *x = new double[n], *b_v = new double[n], *u = new double[n];//Initializes vectors
  x[0] = h;
  double coeff = 100*h*h;

  b_v[0] = coeff*f_b(x[0]);

  for (int i = 0; i < n-1; i++){
    /*
    Gives values to the vectors making up the matrix as well as the right hand side vector.
    */
    a[i] = -1;
    c[i] = -1;
    b[i] = 2;
    x[i+1] = x[i] + h;
    b_v[i+1] = coeff*f_b(x[i+1]);
  }

  b[n-1] = 2;

  for (int i = 1; i < n; i++){
    b[i] -= a[i]*c[i-1]/b[i-1];
    b_v[i] -= a[i]*b_v[i-1]/b[i-1];
  }

  u[n-1] = b_v[n-1]/b[n-1];
  for (int i = n-1; i > 0; i--){
    u[i-1] = (b_v[i-1]-c[i-1]*u[i])/b[i-1];
  }

  return u;
}

double* special(int& n){
  /*
  Solves the problem where all elements in vectors making up the diagonals are the same
  */

  double h = 1./(1+n);
  double *x = new double[n], *b_v = new double[n]; //Initializes vectors
  x[0] = h;
  double coeff = 100*h*h;
  b_v[0] = coeff*f_b(x[0]);

  for (int i = 0; i< n-1; i++){
    /*
    Gives values to the right hand side vector.
    */
    x[i+1] = x[i] + h;
    b_v[i+1] = coeff*f_b(x[i+1]);
  }

  double a = -1., b = 2., c = -1.;
  double *d = new double[n], *u = new double[n];

  for (int i = 0; i < n; i++){
    d[i] = (i+2)/(i+1);
    b_v[i] += (i*b_v[i-1])/(i+1);
  }

  u[n-1] = b_v[n-1]/d[n-1];
  for (int i = n-1; i > 0; i--){
    u[i-1] = (i * (b_v[i-1] + u[i]))/(i+1);
  }
  return u;
}

double* relError(double* u, double* v, int& dim){
  int n = dim;
  double *epsilon= new double[n];
  for (int i = 0; i < n; i++){
    epsilon[i] = log10(abs((v[i]-u[i])/u[i]));
  }
  return epsilon;
}
double* closedForm(int& n){
  double h = 1./(n+1);
  double* x = new double[n];
  for (int i = 0; i < n; i++){
    x[i] = h*(i+1);
  }

  double *u = new double[n];
  double temp = 1 - exp(-10);
  for (int i = 0; i < n; i++){
    u[i] = 1 - temp*x[i] - exp(-10*x[i]);
  }
  return u;
}

double maxValue(double* g, int& dim){
  double max = g[0];
  int o = 0;
  int n = dim;
  for (int i = 0; i < n; i++){
    if (g[i] > max){
      o = i;
    }
  }
  return g[o];
}
void writeFile(double* v, double* u, string& name, int& dim){
  ofstream myFile;
  myFile.open(name);
  int n = dim;
  for (int i = 0; i < n; i++){
    myFile << v[i] << " " << u[i] << endl;
  }
  myFile.close();
}
void compareMethods(int& n){
  /*
  compares CPU time and amount of flops for general and special method of solving the problem as well as armadillo matrix method
  */

  clock_t c_start1 = clock();
  double *u1 = general(n);
  clock_t c_end1 = clock();
  double time_ms = 1000.0 * (c_end1-c_start1)/CLOCKS_PER_SEC;
  cout << "CPU time for general method: " << time_ms << "ms\n";
  cout << "The general method used: " << 12*n - 6 << " floating point operations \n";

  clock_t c_start2 = clock();
  double *u2 = special(n);
  clock_t c_end2 = clock();
  time_ms = 1000.0 * (c_end2-c_start2)/CLOCKS_PER_SEC;
  cout << "CPU time for special method: " << time_ms << "ms\n";
  cout << "The special method used: " << 10*n + 1 << " floating point operations \n";
}
