import numpy as np
import matplotlib.pyplot as plt

<<<<<<< HEAD
with open("Comparison.txt", "r") as infile:
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
plt.plot(x, u, label="Numerical solution" + " n = " + "%E"% (str(len(x))))
plt.plot(x, v, ":", label="Closed-form solution")
plt.legend()
plt.xlabel("x")
plt.ylabel("y")
plt.savefig(figurename)
plt.show()

with open("ErrorData.txt", "r") as infile:
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
=======
if len(sys.argv)!=3:
    print("You need to enter the name of the comparison- and the error-file")
else:
    comparison_name = str(sys.argv[1])
    error_name = str(sys.argv[2])

    with open(comparison_name, "r") as infile:
        u = []
        v = []
        for line in infile:
            element = line.split()
            u.append(float(element[0]))
            v.append(float(element[1]))

    with open(error_name, "r") as infile:
        n = []
        eps = []
        for line in infile:
            element = line.split()
            n.append(float(element[0]))
            eps.append(float(element[1]))

    hh = 1/(float(len(u))+1)
    u = np.array(u)
    v = np.array(v)
    x = np.array([float((i+1)*hh) for i in range(len(u))])


<<<<<<< HEAD
    figurename1 = comparison_name.strip(".txt") + "n" + str(len(u)-1) + ".png"
    plt.plot(x, u, label="Numerical solution" + " n = " + str(len(x)-1))
=======

    figurename1 = comparison_name.strip(".txt") + "n" + str(len(u)-2) + ".png"
    if comparison_name == "ComparisonSpecial.txt":
        title = "Special algorithm"
    elif comparison_name == "ComparisonGeneral.txt":
        title = "General algorithm"
    else:
        title = ""
    plt.plot(x, u, label="Numerical solution" + " n = " + str(len(x)-2))
>>>>>>> a450839236eeb16f6bd0785ae928a1c49fa82e3b
    plt.plot(x, v, ":", label="Closed-form solution")
    plt.legend()
    plt.title(title)
    plt.xlabel("x")
    plt.ylabel("u(x)")
    plt.savefig(figurename1)
    plt.show()

    h = 1/(np.array(n)+1)
    eps = np.array(eps)

    figurename2 = error_name.strip(".txt") + ".png"
    plt.plot(np.log10(h),eps)
    plt.title(title)
    plt.xlabel("log10(h)")
    plt.ylabel("log10(max_error)")
    plt.savefig(figurename2)
    plt.show()
>>>>>>> fbbfa2215be21fa607f74f1bce9739eb5c9e2abe
