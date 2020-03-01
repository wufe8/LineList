#include "LineList.h"
#include <iostream>

#define LIST_LENGTH  32

int printLineList(TList* target);

int main()
{
	TList head(1);
	std::cout << "lineList[0] = " << head.getData(0) << ", sizeof = " << head.getLength() << std::endl;
	head.addData(20, 0);
	std::cout << "lineList[0] = " << head.getData(0) << std::endl;
	head.addList(5, 0);
	std::cout << "lineList[1] = " << head.getData(1) << ", sizeof = " << head.getLength() << std::endl;
	head.addData(10, 1);
	std::cout << "lineList[1] = " << head.getData(1) << std::endl;
	printLineList(&head);
	head.addList(12, 1);
	head.addList(14, 2);
	head.addList(18, 2);
	printLineList(&head);
	std::cout << head.getPos(head.getLength() - 1) << std::endl;
	system("pause");
	head.delList(0);
	printLineList(&head);
	system("pause");
	return 0;
}

int printLineList(TList* target)
{
	if (target->getLength() > LIST_LENGTH)
	{
		std::cout << "invalue length! change LIST_LENGTH in test.cpp!" << std::endl;
	}
	std::cout << "length = " << LIST_LENGTH << std::endl;
	int lineList[LIST_LENGTH];
	for (int i = 0; i < LIST_LENGTH; i++)
	{
		lineList[i] = 0;
	}
	target->getDataAlloy(lineList, LIST_LENGTH);
	std::cout << "linelist[] = {";
	for (int i = 0; i < target->getLength(); i++)
	{
		std::cout << lineList[i] << ", ";
	}
	std::cout << "\b\b};" << std::endl;
	return 0;
}