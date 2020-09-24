a=test.o LinkedList.o Stack.o Queue.o SignalSlot.o 
h=LineList.h SignalSlot.h

test:$a
	g++ -o test $a

LinkedList.o:LinkedList.cpp LineList.h
	g++ -c LinkedList.cpp
Stack.o:Stack.cpp LineList.h
	g++ -c Stack.cpp
Queue.o:Queue.cpp LineList.h
	g++ -c Queue.cpp

SignalSlot.o: SignalSlot.cpp SignalSlot.h
	g++ -c SignalSlot.cpp

test.o:test.cpp $h
	g++ -c test.cpp

#SignalSlotTest: test.o SignalSlot.o
	#g++ -o SignalSlotTest test.o SignalSlot.o
#test: test.cpp SignalSlot.h
	#g++ -c test.cpp
