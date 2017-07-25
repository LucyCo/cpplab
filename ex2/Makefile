all: MIR

MIR: CompositionTypes.o CompositionFactory.o RankerTypes.o RankerFactory.o MIR.o
	g++ -Wextra -Wall -std=c++11 CompositionTypes.o CompositionFactory.o RankerTypes.o RankerFactory.o MIR.o -o MIR -lm
	
CompositionTypes.o: CompositionTypes.cpp
	g++ -c -Wextra -Wall -std=c++11 CompositionTypes.cpp

CompositionFactory.o: CompositionFactory.cpp
	g++ -c -Wextra -Wall -std=c++11 CompositionFactory.cpp

RankerTypes.o: RankerTypes.cpp
	g++ -c -Wextra -Wall -std=c++11 RankerTypes.cpp

RankerFactory.o: RankerFactory.cpp
	g++ -c -Wextra -Wall -std=c++11 RankerFactory.cpp

MIR.o: MIR.cpp
	g++ -c -Wextra -Wall -std=c++11 MIR.cpp

tar: CompositionTypes.cpp CompositionTypes.h BaseComposition.h  CompositionFactory.cpp CompositionFactory.h  BaseWeightRanker.h RankerTypes.cpp RankerTypes.h RankerFactory.cpp RankerFactory.h SavedWords.h MIR.cpp Makefile extension.pdf README
	tar cvf ex2.tar CompositionTypes.cpp CompositionTypes.h BaseComposition.h  CompositionFactory.cpp CompositionFactory.h  BaseWeightRanker.h RankerTypes.cpp RankerTypes.h RankerFactory.cpp RankerFactory.h SavedWords.h MIR.cpp Makefile extension.pdf README
	
clean: 
	rm CompositionFactory*.o RankerTypes*.o CompositionTypes*.o RankerFactory*.o MIR*.o MIR
