#include "LineList.h"
#include <iostream>


void TQueue::push(int data)
{
	addList(data, getData(0) - 1);
	addData(getData(0) + 1, 0);
	std::cout << "pushed: " << data << std::endl;
}

int TQueue::pop()
{

	if (getData(0) <= 1)
	{
		std::cout << "ERROR: Nothing in the queue!" << std::endl;
		return -1;
	}
	addData(getData(0) - 1, 0);
	int data = getData(1);
	delList(1);
	std::cout << "poped: " << data << std::endl;
	return data;
}

int TQueue::peek()
{

	if (getData(0) <= 1)
	{
		std::cout << "ERROR: Nothing in the queue!" << std::endl;
		return -1;
	}
	int data = getData(1);
	std::cout << "peeked: " << data << std::endl;
	return data;
}