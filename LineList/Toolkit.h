#pragma once

#define LIST_LENGTH  32

template<class T>
int printLineList(T* target);

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
