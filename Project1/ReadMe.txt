For this project there is a terminal based menu to aid you in running the program.
To start this simply type 'make all' in the terminal.
You are then asked what you want the program to do. You're given two options.
You can choose one by typing '1' or '2', corresponding to the option you want to pick.

The first option compares time, and amount of floating operations between the general,
the special and the armadillo LU decomposition. The last one is only included by default if the matrix
is smaller or equal to 1000x1000. You choose the dimension yourself in the terminal based menu.

The second option lets you write two files. One is a comparison between the closed form solution
and either the special or the general method's solution. You get to choose which one you want,
as well as the dimension of the matrix used to calculate it. The second text file is a comparison
of the logarithmic absolute of the maximum error between the closed form solution and the method you chose.
It prints this information for 7 different values of 'n'.

To plot the information you just wrote to file, run: Python3 project1_plot.py <comparison file> <error file>
depending on which files you wrote, these might have different names.
comparison file: {ComparisonGeneral.txt, ComparisonSpecial.txt}
error file: {ErrorGeneral.txt, ErrorSpecial.txt}
