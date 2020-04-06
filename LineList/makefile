a=test.o LineList.o

LineList:$a
	g++ -o LineList $a
LineList.o:LineList.cpp LineList.h
	g++ -c LineList.cpp
test.o:test.cpp LineList.h
	g++ -c test.cpp
