import os
import sys


os.system("c++ -o main.out *.cpp")      

N = int(input("Insert number of mesh point N: "))
problem = input("Choose problem (buckling beam/one electron/two electron): ")
"""
filename_plot = "_".join([problem, "solution", str(N)]) + ".pdf" #Name of figure file
filename_data = "_".join([problem, "N", str(N)]) + ".txt" #Name of data file.
plot_path = "/".join([".", "plots", problem]) #Directory to place the figure
data_path = "/".join([".", "results", problem])
"""
all_cpp_codes = "./*.cpp"
compiler_flags = "-larmadillo" #Links to Armadillo.

#compile
os.system("echo compiling...")
os.system("g++ -o main.out" + " " + all_cpp_codes + " " + compiler_flags) #compile codes

#execute
os.system("echo executing...")
os.system("./main.out")

"""
#moves data files to result directory
if not os.path.exists(data_path):
    os.makedirs(data_path)
os.system(" ".join(["mv", filename_data, data_path]))

#runs code for python plot
os.system("echo creating plots...")
#os.system("python3 plot.py" + " " + filename_plot + " " + "/".join([data_path, filename_data]))

#moves plots to directory
if not os.path.exists(plot_path):
    os.makedirs(plot_path)
os.system(" ".join(["mv", filename_plot, plot_path]))
#done
os.system("echo done.")
"""
