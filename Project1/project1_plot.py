import numpy as np
import matplotlib.pyplot as plt
#import sys
"""
if sys.argc==3:
    comparison_name = str(sys.argv[1])
    error_name = str(sys.argv[2])
else:
    print("You need to enter the name of the comparison- and the error-file")
"""
with open("ComparisonSpecial.txt", "r") as infile:
    u = []
    v = []
    for line in infile:
        element = line.split()
        u.append(float(element[0]))
        v.append(float(element[1]))

hh = 1/(float(len(u))+1)
u = np.array(u)
v = np.array(v)
x = np.array([float((i+1)*hh) for i in range(len(u))])

print(len(x))
print(len(u))

figurename = "comparison_n" + str(len(u))
plt.plot(x, u, label="Numerical solution" + " n = " + str(len(x)))
plt.plot(x, v, ":", label="Closed-form solution")
plt.legend()
plt.xlabel("x")
plt.ylabel("y")
plt.savefig(figurename)
plt.show()

with open("ErrorSpecial", "r") as infile:
    n = []
    eps = []
    for line in infile:
        element = line.split()
        n.append(float(element[0]))
        eps.append(float(element[1]))

h = 1/(np.array(n)+1)
eps = np.array(eps)

plt.plot(np.log10(h),eps)
plt.xlabel("log10(h)")
plt.ylabel("log10(max_error)")
plt.show()
