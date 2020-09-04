import matplotlib.pyplot as plt

with open("filnavn", "r") as infile:
    u = []
    x = []
    for line in infile:
        element = line.split()
        u.append(float(element[0]))
        x.append(float(element[1]))

plt.plot(x, u)
plt.show()
