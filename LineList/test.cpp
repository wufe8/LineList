#include "LineList.h"
#include <iostream>
#include <string>

#include "LinkedList.cpp"
#include "Stack.cpp"
#include "Queue.cpp"

#define LIST_LENGTH  32

template<class T>
int printLineList(T* target);

int main()
{
	TStack<float> boat;
	printLineList(&boat);
	boat.setLength();
	printLineList(&boat);
	boat.push(10);
	printLineList(&boat);
	boat.push(20);
	printLineList(&boat);
	boat.push(30);
	printLineList(&boat);
	boat.peek();
	printLineList(&boat);
	boat.pop();
	printLineList(&boat);
	boat.push(40);
	printLineList(&boat);
	boat.pop();
	printLineList(&boat);
	boat.pop();
	printLineList(&boat);
	boat.peek();
	printLineList(&boat);
	boat.push(50);
	printLineList(&boat);
	boat.pop();
	printLineList(&boat);
	boat.pop();
	printLineList(&boat);
	boat.pop();
	printLineList(&boat);
	boat.peek();
	printLineList(&boat);
	boat.pop();
	std::cout << "\n================================\n\n";
	TQueue<double> unit;
	unit.setLength();
	printLineList(&unit);
	unit.push(10);
	printLineList(&unit);
	unit.push(20);
	printLineList(&unit);
	unit.push(30);
	printLineList(&unit);
	unit.peek();
	printLineList(&unit);
	unit.pop();
	printLineList(&unit);
	unit.push(40);
	printLineList(&unit);
	unit.pop();
	printLineList(&unit);
	unit.pop();
	printLineList(&unit);
	unit.peek();
	printLineList(&unit);
	unit.push(50);
	printLineList(&unit);
	unit.pop();
	printLineList(&unit);
	unit.pop();
	printLineList(&unit);
	unit.pop();
	printLineList(&unit);
	unit.peek();
	printLineList(&unit);
	unit.pop();
	std::cout << "\n================================\n\n";
	TLinkedList<long> head(1);
	printLineList(&head);
	head.addData(10, 0);
	printLineList(&head);
	head.addList(2, 0);
	printLineList(&head);
	head.addData(20, 1);
	printLineList(&head);
	head.addList(3, 1);
	printLineList(&head);
	head.addList(4, 2);
	printLineList(&head);
	head.addList(5, 2);
	printLineList(&head);
	head.delList(0);
	printLineList(&head);
	head.addList(100, -1);
	printLineList(&head);
	head.delList(3);
	printLineList(&head);
	head.delList(3);
	printLineList(&head);
	head.delList(3);
	printLineList(&head);
	system("pause");
	return 0;
}

template<class T>
int printLineList(T* target)
{
	const int listLength = target->getLength();
	if (target->getLength() > LIST_LENGTH) //check output array length
	{
		std::cout << "invalue length! change LIST_LENGTH in test.cpp!" << std::endl;
		return 1;
	}
	std::cout << "length = " << target->getLength() << "; ";
	std::string lineList[LIST_LENGTH];
	for (int i = 0; i < LIST_LENGTH; i++)
	{
		lineList[i] = "0"; //init
	}
	target->getDataArray(lineList, listLength);
	std::cout << "linelist[] = {";
	for (int i = 0; i < listLength; i++)
	{
		std::cout << lineList[i] << ", ";
	}
	std::cout << "\b\b};" << std::endl << std::endl;
	return 0;
}
