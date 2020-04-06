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
	int pp = head.getLength() - 1;
	std::cout << "lineList[" << pp << "] = " << head.getData(pp)  << " in " << head.getPos(pp) << std::endl;
	head.delList(0);
	printLineList(&head);
	head.addList(100, -1);
	printLineList(&head);
	system("pause");
	return 0;
}

int printLineList(TList* target)
{
	const int listLength = target->getLength();
	if (target->getLength() > LIST_LENGTH) //check output alloy length
	{
		std::cout << "invalue length! change LIST_LENGTH in test.cpp!" << std::endl;
		return 1;
	}
	std::cout << "length = " << target->getLength() << std::endl;
	int lineList[LIST_LENGTH];
	for (int i = 0; i < LIST_LENGTH; i++)
	{
		lineList[i] = 0; //init
	}
	target->getDataAlloy(lineList, listLength);
	std::cout << "linelist[] = {";
	for (int i = 0; i < listLength; i++)
	{
		std::cout << lineList[i] << ", ";
	}
	std::cout << "\b\b};" << std::endl;
	return 0;
}
