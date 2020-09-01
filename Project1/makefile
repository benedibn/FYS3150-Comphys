all: compile execute
compile:
	c++ -o main.out main.cpp TridiagonalMatrix.cpp UpperBandedMatrix.cpp LowerBandedMatrix.cpp TridiagonalSpecial.cpp UpperBandedSpecial.cpp -larmadillo -llapack -lblas

execute:
	./main.out
