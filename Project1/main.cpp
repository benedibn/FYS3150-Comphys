#include "TridiagonalMatrix.hpp"
#include "UpperBandedMatrix.hpp"
#include "LowerBandedMatrix.hpp"
#include "TridiagonalSpecial.hpp"
#include "UpperBandedSpecial.hpp"
#include <iostream>
#include <ctime>

using namespace std;

double f_b(double&);
void menu();
void task1b();
void task1c();
int dimensionChoice();

int main(int argc, char const *argv[]){
  /*
  Main function
  */
  menu();
  return 0;
}

double f_b(double& x_i){
  return exp(x_i);
}

void menu(){
  int input, input2;
  while(true){
    cout << "Choose a number below by writing it in the terminal. \n";
    cout << "---------------------------------------------------\n";
    cout << "0: stop \n";
    cout << "1: Task 1b \n";
    cout << "2: Task 1c \n";


    cout << "Input: ";
    cin >> input;
    if (input == 0){
      break;
    }
    if (input == 1){
      while (true){
        /*1b menu*/
        cout << "Choose a number below by writing it in the terminal. \n";
        cout << "---------------------------------------------------\n";
        cout << "0: Go back \n";
        cout << "1: Look at information about Task 1b \n";
        cout << "2: Solve 1b \n";
        cout << "Input: ";
        cin >> input2;
        if (input2 == 0){
          break;
        }
        if (input2 == 1){
          /*Info about 1b*/
          cout << "1b solves the linear algebra problem Ax = b where A is a Tridiagonal matrix ";
          cout << "with the value 2 on the diagonal and -1 on the neighbouring diagonal lines. ";
          cout << "The algorithm is built for a general case where these values can be whatever. \n";
          cout << "The equation is solved by decomposing the matix into a lower and and an upper ";
          cout << "banded matrix and solving these inidividually.\n";
          cout << "The program then plots the result alongside the data it's supposed to approximate.\n";
        }
        if (input2 == 2){
          /*Solution of 1b*/
          task1b();
        }
      }
    }
    if (input == 2){
      while(true){
        /*1c menu*/
        cout << "Choose a number below by writing it in the terminal. \n";
        cout << "---------------------------------------------------\n";
        cout << "0: Go back \n";
        cout << "1: Look at information about Task 1c \n";
        cout << "2: Solve 1c \n";
        cout << "Input: ";
        cin >> input2;
        if (input2 == 0){
          break;
        }
        if (input2 == 1){
          /*Info about 1c*/
          cout << "1c solves the linear algebra problem Ax = b where A is a Tridiagonal matrix ";
          cout << "with the value 2 on the diagonal and -1 on the neighbouring diagonal lines. ";
          cout << "The algorithm is built specifically for this case. \n";
          cout << "The equation is solved by decomposing the matix into a lower and and an upper ";
          cout << "banded matrix and solving these inidividually.\n";
          cout << "The program then plots the result alongside the data it's supposed to approximate.\n";
        }
        if (input2 == 2){
          task1c();
        }
      }
    }
  }
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
void task1b(){

  int n = dimensionChoice(); //Change this if you want to prevent the user from choosing the matrix size

  clock_t c_start = clock();

  double h = 1./(1+n); //flop++
  int flop = 1;        //FLoating Point Operations
  vec a(n-1), b(n), c(n-1), x(n), b_v(n), u(n); //Initializes vectors
  x[0] = h;
  double coeff = 100*h*h;
  flop += 2;
  b_v[0] = coeff*f_b(x[0]);

  for (int i = 0; i< n-1; i++){
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

  flop += 3*n - 1;

  for (int i = 1; i < n; i++){
    b[i] -= a[i]*c[i-1]/b[i-1];
    b_v[i] -= a[i]*b_v[i-1]/b[i-1];
  }
  flop += 6*(n-1);


  u[n-1] = b_v[n-1]/b[n-1];
  for (int i = n-1; i > 0; i--){
    u[i-1] = (b_v[i-1]-c[i-1]*u[i])/b[i-1];
  }
  flop += 3*n-2;

  /*
  TridiagonalMatrix triMat(a,b,c); //Initializes the matrix
  vec u = triMat.solve(b_v);
  flop += triMat.getFLOP();
  */

  cout << "1b used: " << flop << " floating point operations \n";

  /*
  Plotting goes here
  */

  clock_t c_end = clock();
  double time_ms = 1000.0 * (c_end-c_start)/CLOCKS_PER_SEC;
  cout << "CPU time: " << time_ms << "ms\n";
}

void task1c(){

  int n = dimensionChoice();

  clock_t c_start = clock();

  double h = 1./(1+n); //flop++
  int flop = 1;        //FLoating Point Operations
  vec x(n), b_v(n); //Initializes vectors
  x[0] = h;
  double coeff = 100*h*h;
  flop += 2;
  b_v[0] = coeff*f_b(x[0]);

  for (int i = 0; i< n-1; i++){
    /*
    Gives values to the right hand side vector.
    */
    x[i+1] = x[i] + h;
    b_v[i+1] = coeff*f_b(x[i+1]);
  }
  flop += 3*n - 1;  //one for multiplication, and one for power for each f_b.


  double a = -1., b = 2., c = -1.;


  vec d(n), u(n);
  for (int i = 0; i < n; i++){
    d[i] = (i+2)/(i+1);
    b_v[i] += (i*b_v[i-1])/(i+1);
  }
  flop += 4*n;

  u[n-1] = b_v[n-1]/d[n-1];
  for (int i = n-1; i > 0; i--){
    u[i-1] = (i * (b_v[i-1] + u[i]))/i+1;
  }
  flop += 3*n-1;


  cout << "1c used: " << flop << " floating point operations \n";

  /*
  Plotting goes here
  */
  clock_t c_end = clock();
  double time_ms = 1000.0 * (c_end-c_start)/CLOCKS_PER_SEC;
  cout << "CPU time: " << time_ms << "ms\n";
}


int o = 0;
