import numpy as np
import matplotlib.pyplot as plt
import sys
import os

#plot_filename = sys.argv[1]
#infile_filename = sys.argv[2]

infile_filename = 'Eigenvalue.txt'

with open(infile_filename, "r") as infile:
    eigenvals = []
    N = []
    for line in infile:
        elements = line.split()
        N.append(float(elements[0]))
        eigenvals.append(float(elements[1]))

def analytical_eigenvalues(N):
    pass


def analytical_eigenvectors(N):
    pass

print(N, eigenvals)
plt.plot(N,eigenvals, label = 'Numerical solution')
plt.legend()
plt.xlabel('')
#plt.savefig(plot_filename)
plt.show()
