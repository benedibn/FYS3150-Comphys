





void special(double* v_s, int& n, double& time){
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

  double *d = new double[n];

  clock_t c_start = clock();
  d[0] = 2;

  for (int i = 1; i < n; i++){
    /*
    Gives new values to the diagonal vector and the right hand side according to row reduction
    */
    d[i] = (i+2.)/(i+1);
    b_v[i] += b_v[i-1]/d[i-1];
  }

  v_s[n-1] = b_v[n-1]/d[n-1];
  for (int i = n-1; i > 0; i--){
    /*
    Backwards substitution
    */
    v_s[i-1] = (b_v[i-1] + v_s[i])/d[i-1];
  }
  delete[] d;
  delete[] b_v;
  clock_t c_end = clock();
  time += (1000.0 * (c_end-c_start)/CLOCKS_PER_SEC);
}
