all: bsim

bsim: Event.o EmptyDataCollectionException.o BinaryHeap.h PriorityQueue.h Queue.h BankSimApp.o 
	g++ -Wall  -o bsim BankSimApp.o Event.o  EmptyDataCollectionException.o 

BankSimApp.o: BankSimApp.cpp
	g++ -Wall  -c BankSimApp.cpp 
		
Event.o: Event.h Event.cpp
	g++ -Wall  -c Event.cpp
		
EmptyDataCollectionException.o: EmptyDataCollectionException.h EmptyDataCollectionException.cpp
	g++ -Wall  -c EmptyDataCollectionException.cpp 

clean:
	rm -f bsim *.o