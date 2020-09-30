import os
import sys

N = int(input("Insert number of mesh point N: "))
problem = input("Choose problem (bucklingbeam/oneelectron/twoelectrons): ")


filename_plot = "_".join([problem, "solution", str(N)]) + ".pdf"
filename_data = ".".join([problem, "txt"])
#Directory to place the figure
plot_path = "/".join([".", "plots"])
data_path = "/".join([".", "results"])


#compile
os.system("echo compiling...")
os.system("g++ -o main.out main.cpp -larmadillo")
#os.system("g++ -o main.out" + " " + all_cpp_codes + " " + compiler_flags) #compile codes

#execute
os.system("echo executing...")
os.system("./main.out" + " " + str(N) + " " + problem)

"""
#moves data files to result directory
if not os.path.exists(data_path):
    os.makedirs(data_path)
os.system(" ".join(["mv", filename_data, data_path]))
"""
#runs code for python plot
os.system("echo creating plots...")
os.system("python3 plot.py" + " " + filename_plot + " " + filename_data)

#moves plots to directory
if not os.path.exists(plot_path):
    os.makedirs(plot_path)
os.system(" ".join(["mv", filename_plot, plot_path]))

#done
os.system("echo done.")
