a=test.o LinkedList.o Stack.o Queue.o
h=LineList.h

test:$a
	g++ -o test $a
LinkedList.o:LinkedList.cpp $h
	g++ -c LinkedList.cpp
Stack.o:Stack.cpp $h
	g++ -c Stack.cpp
Queue.o:Queue.cpp $h
	g++ -c Queue.cpp
test.o:test.cpp $h
	g++ -c test.cpp
