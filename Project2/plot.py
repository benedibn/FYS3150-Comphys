import numpy as np
import matplotlib.pyplot as plt
import sys
import os

plot_filename = sys.argv[1]
infile_filename = sys.argv[2]

with open(infile_filename, "r") as infile:
    k = int(infile.readline())
    arma_lambda = infile.readline()
    arma_lambda = arma_lambda.split()
    jacobi_lambda = infile.readline()
    jacobi_lambda = jacobi_lambda.split()
    min_eigvec_jacobi = infile.readline()
    min_eigvec_jacobi = min_eigvec_jacobi.split()
N = len(arma_lambda)
for i in range (N):
    arma_lambda[i] = float(arma_lambda[i])
    jacobi_lambda[i] = float(jacobi_lambda[i])
    min_eigvec_jacobi[i] = float(min_eigvec_jacobi[i])

rho0 = 0
rhomax = 1
h = rhomax/N

rho = [rho0 + i*h for i in range(0,len(arma_lambda))]

def analytical_eigenvalues(N):
    pass


def analytical_eigenvectors(N):
    pass



plt.plot(rho, min_eigvec_jacobi, label = 'Numerical solution')
plt.legend()
plt.xlabel('')
plt.ylabel('')
plt.savefig(plot_filename)
plt.show()
