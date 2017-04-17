all: program1 program2 program3 program4 program5 program6

program1:
	g++ -pthread Parallel1.cpp -o Parallel1

program2:
	g++ -pthread Parallel2_2T.cpp -o Parallel2_2T

program3:
	g++ Serial.cpp -o Serial

program4:
	g++ -pthread Parallel2_4T.cpp -o Parallel2_4T

program5:
	g++ -pthread Parallel2_4T_LargeSet.cpp -o Parallel2_4T_LargeSet

program6:
	g++ -pthread Parallel2_4T_OptimizeTest.cpp -o Parallel2_4T_OptimizeTest
