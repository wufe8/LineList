#include "LineList.h"
#include <iostream>

#include "pch.h"

template<typename T>
void TStack<T>::push(T data)
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the stack!" << std::endl;
	}
	this->addList(data, this->getLength() - 1);
	std::cout << "pushed: " << data << std::endl;
}

template<typename T>
T TStack<T>::pop()
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the stack!" << std::endl;
		return -1;
	}
	T data;
	return this->delList(this->getLength() - 1);
	std::cout << "poped: " << data << std::endl;
	return data;
}

template<typename T>
T TStack<T>::peek()
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the stack!" << std::endl;
		return -1;
	}
	T data = this->getData(arrayLength - 1);
	std::cout << "peeked: " << data << std::endl;
	return data;
}