import os
import sys

N = int(input("Insert number of mesh point N: "))
problem = input("Choose problem (bucklingbeam/oneelectron/twoelectrons): ")

if problem == "twoelectrons":
    filename_plot = "_".join([problem, "solution", str(N)]) + ".pdf"

    #Directory to place the figure
    plot_path = "/".join([".", "plots"])

    #compile
    os.system("echo compiling...")
    os.system("g++ -o main.out main.cpp -larmadillo")

    #execute
    os.system("echo executing...")
    os.system("./main.out" + " " + str(N) + " " + problem)


    #runs code for python plot
    os.system("echo creating plots...")
    os.system("python3 plot.py" + " " + filename_plot + " " + problem)

    #moves plots to directory
    if not os.path.exists(plot_path):
        os.makedirs(plot_path)
    os.system(" ".join(["mv", filename_plot, plot_path]))

    #done
    os.system("echo done.")

else:
    filename_plot = "_".join([problem, "solution", str(N)]) + ".pdf"
    filename_data = ".".join([problem, "txt"])

    #Directory to place the figure
    plot_path = "/".join([".", "plots"])

    #compile
    os.system("echo compiling...")
    os.system("g++ -o main.out main.cpp -larmadillo")

    #execute
    os.system("echo executing...")
    os.system("./main.out" + " " + str(N) + " " + problem)


    #runs code for python plot
    os.system("echo creating plots...")
    os.system("python3 plot.py" + " " + filename_plot + " " + filename_data)

    #moves plots to directory
    if not os.path.exists(plot_path):
        os.makedirs(plot_path)
    os.system(" ".join(["mv", filename_plot, plot_path]))

    #done
    os.system("echo done.")
