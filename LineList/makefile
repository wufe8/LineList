a=test.o SignalSlot.o
h=SearchTree.h AVLTree.h LinkedList.h SignalSlot.h Toolkit.h SimpleLinkedList.h

test:$a
	g++ -o test $a

SignalSlot.o: $h
	g++ -c SignalSlot.cpp

test.o:test.cpp $h
	g++ -c test.cpp

#SignalSlotTest: test.o SignalSlot.o
	#g++ -o SignalSlotTest test.o SignalSlot.o
#test: test.cpp SignalSlot.h
	#g++ -c test.cpp
