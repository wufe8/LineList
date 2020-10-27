#pragma once
#include <iostream>

#define LIST_LENGTH 32

//输出整条链表数据 限定TSimpleDoubleLL类(原TLinkedList)及其子类
//或者模板T类含int getLength() 以及int getDataArray(string[], int, int)成员函数 详细定义与功能见SimpleLinkedList.h
template<class T>
int printTSLL(T & target);

template<class T>
void printEachNode(T & target);

template<class T>
int printTSLL(T & target)
{
	const int listLength = target.getLength();
	if (target.getLength() > LIST_LENGTH) //check output array length
	{
		std::cout << "invalue length! change LIST_LENGTH in test.cpp!" << std::endl;
		return 1;
	}
	std::cout << "length = " << target.getLength() << "; ";
	std::string lineList[LIST_LENGTH];
	for (int i = 0; i < LIST_LENGTH; i++)
	{
		lineList[i] = "0"; //init
	}
	target.getDataArray(lineList, listLength);
	std::cout << "linelist[] = {";
	for (int i = 0; i < listLength; i++)
	{
		std::cout << lineList[i] << ", ";
	}
	std::cout << "\b\b};" << std::endl << std::endl;
	return 0;
}

//通过[]后缀输出整个数组/已重载运算符的类 T & target形参接受任意符合上述要求的类
template<class T>
void printEachNode(T & target)
{
	std::cout << "size = " << target.size() << std::endl;
	std::cout << "testlist = {";
	for (int i = 0; i < target.size(); i++)
	{
		std::cout << target[i] << ", ";
	}
	std::cout << "\b\b}" << std::endl;
}
