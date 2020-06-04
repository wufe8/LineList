#include "LineList.h"
#include <iostream>

void TStack::push(int data)
{
	addList(data, getData(0) - 1);
	addData(getData(0) + 1, 0);
	std::cout << "pushed: " << data << std::endl;
}

int TStack::pop()
{
	
	if (getData(0) <= 1)
	{
		std::cout << "ERROR: Nothing in the stack!" << std::endl;
		return -1;
	}
	addData(getData(0) - 1, 0);
	int data = getData(getData(0));
	delList(getData(0));
	std::cout << "poped: " << data << std::endl;
	return data;
}