all: program1 program2

program1:
	g++ -pthread VariableLengthSolution1.cpp -o VariableLengthSolution1

program2:
	g++ -pthread VariableLengthSolution2.cpp -o VariableLengthSolution2
