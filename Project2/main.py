import os
import sys

N = int(input("Insert number of mesh point N: "))
#algorithm = input("Choose algorithm: ")
"""
filename_plot = "_".join([algorithm, "solution", str(N)]) + ".pdf" #Name of figure file
filename_data = "_".join([algorithm, "N", str(N)]) + ".txt" #Name of data file.
plot_path = "/".join([".", "plots", algorithm]) #Directory to place the figure
data_path = "/".join([".", "results", algorithm])

all_cpp_codes = "./Project2/*.cpp"
compiler_flags = "-larmadillo" #Links to Armadillo.
"""

os.system("echo compiling...") #prints "compiling..."
os.system("g++ -o main.out" + " " + all_cpp_codes + " " + compiler_flags) #compile codes

os.system("echo executing...")
os.system("./main.out")

"""
if not os.path.exists(data_path):
    os.makedirs(data_path) #Creates the directory
os.system("mv" + " " + filename_data + " " + data_path) #Move data file to results directory.


os.system("echo creating plots...")
os.system("python3 plot.py" + " " + filename_plot + " " + "/".join([data_path, filename_data]))


if not os.path.exists(plot_path):
    os.makedirs(plot_path)

os.system(" ".join(["mv", filename_plot, plot_path])) #Move file to correct directory.
"""
os.system("echo done.")
