import os
import sys

N = int(input("Insert number of mesh point N: "))

all_cpp_codes = "./cpp_codes/*.cpp"
compiler_flags = "-larmadillo" #Linker to Armadillo.


#os.system("echo compiling...")
os.system("g++ -o main.out" + " " + all_cpp_codes + " " + compiler_flags) #compile codes

#os.system("echo executing...")
os.system("./main.out" + " " + str(N) + " " + algorithm)
