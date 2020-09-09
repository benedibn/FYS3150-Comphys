#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

double f_b(double&);
double* general(int&, double&);
double* special(int&, double&);
vec preBuilt(int&);
int dimensionChoice();
double* relError(double*, double*, int&);
double* closedForm(int&);
double maxValue(double*, int&);
void writeFile(double*, double*, int&, ofstream&);
void compareMethods(int&);

int main(int argc, char const *argv[]){
  /*
  Main function
  */
  (void) argc; (void) argv;
  cout << "Do you want to to compare methods or run the program? \n";
  cout << "--------------------------------------------------------\n";
  cout << "1: Compare methods\n";
  cout << "2: Write information files for comparison and error\n";
  cout << "Input: ";
  int input;
  cin >> input;


  int n;
  if (input == 1){
    /*
    Compares the general, special and armadillo methods for a matrix whose dimensions are chosen by user
    */
    n = dimensionChoice();
    compareMethods(n);
  }
  if (input == 2){
    /*
    Writes two text files:
    1 for comparing the closed form solution to the algorhitm of choice.
    1 for comparing the logaritmic absolute value of the error.
    */
    double *v;
    double *u;
    double *errList;
    double *nList;
    int input2, input3 = 0;
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

    int nPow = 7;
    nList = new double[nPow];
    errList = new double[nPow];

    while (input3 != 1 && input3 != 2){
      /*
      Runs until the user has figured out how the menu works
      */
      cout << "Do you want to use the special or the general method?\n";
      cout << "-----------------------------------------------------\n";
      cout << "1: General\n";
      cout << "2: Special\n";
      cout << "Input: ";
      cin >> input3;
    }

    string name, errorName;
    double time = 0.0;
    ofstream myFile, myFile2;
    for (int i = 1; i < (nPow+1); i++){
      /*
      writes the error information
      */
      n = pow(10,i);

      if (input3 == 1){
        v = general(n,time);
        name = "ComparisonGeneral.txt";
        errorName = "ErrorGeneral.txt";
      }
      else{
        v = special(n,time);
        name = "ComparisonSpecial.txt";
        errorName = "ErrorSpecial.txt";
      }
      u = closedForm(n);

      if (n == nPlot){
        /*
        chooses which file is written for plotting
        */

        myFile.open(name);
        myFile << 0 << " " << 0 << endl;
        writeFile(v,u,n,myFile);
        myFile << 0 << " " << 0 << endl;
        myFile.close();
      }
      nList[i-1] = (double) n;
      double* eps = relError(u,v,n);
      errList[i-1] = maxValue(eps,n);
      delete[] eps;
      delete[] u;
      delete[] v;

    }
    myFile2.open(errorName);
    writeFile(nList, errList, nPow,myFile2);
    myFile2.close();
    delete[] nList;
    delete[] errList;

  }

  return 0;
}

double f_b(double& x_i){
  /*
  Part of the closed form algorhitm
  */
  return exp(-10*x_i);
}


int dimensionChoice(){
  /*
  Provides the user with a menu for choosing n
  */
  int n;
  while(true){
    /*
    restarts the menu if the user writes an invalid number.
    */
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
double* general(int& n, double& time){
  /*
  Solves the problem with a method that knows the matix is tridiagonal,
  but treats the values on these diagonals like different values.
  */

  double h = 1./(1.+n);

  double *a = new double[n-1], *b = new double[n], *c = new double[n-1];
  double *x = new double[n], *b_v = new double[n], *u_g = new double[n];//Initializes vectors
  x[0] = h;
  double coeff = 100*h*h;

  b_v[0] = coeff*f_b(x[0]);

  for (int i = 0; i < n-1; i++){
    /*
    Initializes the matrix vector as well as the right hand side vector
    */
    a[i] = -1;
    c[i] = -1;
    b[i] = 2;
    x[i+1] = x[i] + h;
    b_v[i+1] = coeff*f_b(x[i+1]);
  }
  delete[] x;

  b[n-1] = 2;
  clock_t c_start = clock();

  for (int i = 1; i < n; i++){
    /*
    Gives new values to the diagonal vector and the right hand side according to row reduction
    */
    b[i] -= c[i-1]*(a[i-1]/b[i-1]);
    b_v[i] -= b_v[i-1]*(a[i-1]/b[i-1]);
  }
  delete[] a;
  u_g[n-1] = b_v[n-1]/b[n-1];

  for (int i = n-1; i > 0; i--){
    /*
    Backwards substitution
    */
    u_g[i-1] = (b_v[i-1]-c[i-1]*u_g[i])/b[i-1];
  }
  delete[] c;
  delete[] b;
  delete[] b_v;
  clock_t c_end = clock();
  time += (1000.0 * (c_end-c_start)/CLOCKS_PER_SEC);

  return u_g;
}

double* special(int& n, double& time){
  /*
  Solves the problem where all elements in the vectors making up the diagonals are the same
  */

  double h = 1./(1+n);
  double *x = new double[n], *b_v = new double[n]; //Initializes vectors
  x[0] = h;
  double coeff = 100*h*h;
  b_v[0] = coeff*f_b(x[0]);

  for (int i = 0; i < n-1; i++){
    /*
    Initializes the right hand side vector
    */
    x[i+1] = x[i] + h;
    b_v[i+1] = coeff*f_b(x[i+1]);
  }
  delete[] x;

  double *d = new double[n], *u_s = new double[n];

  clock_t c_start = clock();
  d[0] = 2;

  for (int i = 1; i < n; i++){
    /*
    Gives new values to the diagonal vector and the right hand side according to row reduction
    */
    d[i] = (i+2.)/(i+1.);
    b_v[i] += b_v[i-1]/d[i-1];
  }

  u_s[n-1] = b_v[n-1]/d[n-1];
  for (int i = n-1; i > 0; i--){
    /*
    Backwards substitution
    */
    u_s[i-1] = (b_v[i-1] + u_s[i])/d[i-1];
  }
  delete[] d;
  delete[] b_v;
  clock_t c_end = clock();
  time += (1000.0 * (c_end-c_start)/CLOCKS_PER_SEC);

  return u_s;
}

double* relError(double* u, double* v, int& dim){
  /*
  Returns the logaritmic relative error between two vectors
  */
  int n = dim;
  double *epsilon = new double[n];
  for (int i = 0; i < n; i++){
    epsilon[i] = log10(abs((v[i]-u[i])/u[i]));
  }
  return epsilon;
}
double* closedForm(int& n){
  /*
  Returns a vector that correspond to the exact solution (although quantified).
  */
  double h = 1./(n+1);
  double* x_c = new double[n];
  x_c[0] = h;
  for (int i = 0; i < n; i++){
    /*
    linspace
    */
    x_c[i] = x_c[i-1] + h;
  }

  double *u_c = new double[n];
  double temp = 1 - exp(-10);
  for (int i = 0; i < n; i++){
    /*
    Correct solution
    */
    u_c[i] = 1 - temp*x_c[i] - exp(-10*x_c[i]);
  }
  delete[] x_c;
  return u_c;
}

double maxValue(double* g, int& dim){
  /*
  returns the largest value in a set
  */
  double max = g[0];
  int o = 0;        //Index corresponding to the largest value counted thus far.
  int n = dim;
  for (int i = 0; i < n; i++){
    if (g[i] > max){
      o = i;
    }
  }
  return g[o];
}
void writeFile(double* v, double* u, int& dim, ofstream& aFile){
  /*
  Writes all elements of two vectors u and v to a file with a given name
  */
  int n = dim;
  for (int i = 0; i < n; i++){
    /*
    Writes one line
    */
    aFile << v[i] << " " << u[i] << endl;
  }

}

vec preBuilt(int& n){
  /*
  Solves the problem with armadillo methods
  */
  unsigned int m = (unsigned int) n;
  mat A(m,m), L, U;
  A(0,0) = 2; A(0,1) = -1; A(m-1,m-2) = -1; A(m-1,m-1) = 2;

  double h = 1./(m + 1);
  vec x(m), b_v(m); //Initializes vectors
  x[0] = h;
  double coeff = 100*h*h;
  b_v[0] = coeff*f_b(x[0]);

  for (unsigned int i = 0; i < m-1; i++){
    /*
    Gives values to the right hand side vector.
    */
    x[i+1] = x[i] + h;
    b_v[i+1] = coeff*f_b(x[i+1]);
  }

  for (unsigned int i = 1; i < m-1; i++){
    /*
    Initializes the matrix
    */
    A(i,i) = 2;
    A(i,i-1) = -1;
    A(i,i+1) = -1;
  }
  lu(L,U,A);      //LU decomposition
  vec temp = solve(L, b_v);     //Forward substitution
  vec u = solve(U,temp);        //Backwards substitution

  return u;
}

void compareMethods(int& n){
  /*
  compares CPU time and amount of flops for general and special method of solving the problem as well as armadillo matrix method
  */
  double time1 = 0;
  double time2 = 0;
  double *u, *v;

  for (int i = 0; i < 1000; i++){
    /*
    Adds the time of running the funcions once. This is average over when printed
    */
    v = general(n,time1);
    u = special(n,time2);
    delete[] v;
    delete[] u;
  }

  cout << "\nCPU time for general method: " << time1/1000 << "ms\n";
  cout << "The general method used: " << 9*n - 8 << " floating point operations \n\n";


  cout << "CPU time for special method: " << time2/1000 << "ms\n";
  cout << "The special method used: " << 4*n - 1 << " floating point operations \n\n";

  if (n > 1000){
    /*
    Gives the user the option to terminate the program if it tries to run the armadillo method for a large matrix.
    */
    int input;
    cout << "The matrix is too large. The armadillo method might not work. Do you want to try anyway?\n";
    cout << "----------------------------------------------------------------------------------------\n";
    cout << "1: No\n";
    cout << "2: Yes\n";
    cout << "Input: ";
    cin >> input;
    if (input == 1){
      return;
    }
  }

  clock_t c_start3 = clock();
  vec u3 = preBuilt(n);
  clock_t c_end3 = clock();
  double time_ms = 1000.0 * (c_end3-c_start3)/CLOCKS_PER_SEC;
  cout << "CPU time for armadillo method: " << time_ms << "ms\n";
  cout << "The armadillo method used approximately: " << n*n*n << " floating point operations \n";
}
