SHELL := /bin/bash

all: program1 program2 program3 program4 program5 program6 program7 program8 program9 program10

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

program7:
	g++ -pthread src/Alphabet_Switch.cpp -o Executables/Alphabet_Switch

program8:
	g++ -pthread src/Parallel_Variable2.cpp -w -o Executables/Parallel_Variable2

program9:
	g++ src/Hash_Source.cpp -w  -pthread -lcrypto -o Executables/hash
	
program10:
	g++ -pthread src/Parallel_Variable2_LargeSet.cpp -w -o Executables/Parallel_Variable2_LargeSet
