SHELL := /bin/bash

all: program1 program2 program3 program4 program5 program6

program1:
	mkdir -p -m 777 Executables
	mkdir -p -m 777 OutputFiles
	g++ -pthread src/Parallel1.cpp -o Executables/Parallel1

program2:
	g++ -pthread src/Parallel2_2T.cpp -o Executables/Parallel2_2T

program3:
	g++ src/Serial.cpp -o Executables/Serial

program4:
	g++ -pthread src/Parallel2_4T.cpp -o Executables/Parallel2_4T

program5:
	g++ -pthread src/Parallel2_4T_LargeSet.cpp -o Executables/Parallel2_4T_LargeSet

program6:
	g++ -pthread src/Parallel2_4T_OptimizeTest.cpp -o Executables/Parallel2_4T_OptimizeTest
