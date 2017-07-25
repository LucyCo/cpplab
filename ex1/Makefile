all: SetBinaryOperations

SetBinaryOperations: SetBinaryOperations.o MySet.o
	g++ -Wextra -Wall -std=c++11 SetBinaryOperations.o MySet.o -o SetBinaryOperations -lm
	
SetBinaryOperations.o: SetBinaryOperations.cpp
	g++ -c -Wextra -Wall SetBinaryOperations.cpp

MySet.o: MySet.cpp
	g++ -c -Wextra -Wall MySet.cpp

tar: MySet.cpp MySet.h SetBinaryOperations.cpp Makefile
	tar cvf ex1.tar MySet.cpp MySet.h SetBinaryOperations.cpp Makefile Extension.pdf
	
clean: 
	rm SetBinaryOperations*.o MySet*.o SetBinaryOperations
