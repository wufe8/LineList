#include "LineList.h"
#include <iostream>

#include "pch.h"

template<typename T>
void TQueue<T>::push(T data)
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the queue!" << std::endl;
	}
	this->addList(data, arrayLength - 1);
	std::cout << "pushed: " << data << std::endl;
}

template<typename T>
T TQueue<T>::pop()
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the queue!" << std::endl;
		return -1;
	}
	T data = this->delList(0);
	std::cout << "poped: " << data << std::endl;
	return data;
} 



template<typename T>
T TQueue<T>::peek()
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the queue!" << std::endl;
		return -1;
	}
	T data = this->getData(1);
	std::cout << "peeked: " << data << std::endl;
	return data;
}
