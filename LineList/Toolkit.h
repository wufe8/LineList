#pragma once

#define LIST_LENGTH 32

#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T>
T abs(T number); //绝对值
template<class T>
T aluAdd(T a, T b); //模拟ALU加法
void binToDex(bool* bitArray, int length, int &a); //二进制转十进制
void dexToBin(int a, bool* bitArray); //十进制转二进制
template<class T>
void printArray(T& array, int length, string name = "Array"); //输出数组
template<class T>
void tnirpArray(T& array, int length, string name = "Array"); //倒序输出数组
template<class T>
int findElem(T* array, int length, T target); //查找元素
template<class T>
void initArray(T* array, int length, T initNum = 0); //初始化数组
int log2(int num); //log2向上取整
template<class T>
void sortInsert(T& array, int length); //插入排序
template<class T>
void sortHill(T& array, int length); //希尔排序
template<class T>
void swapNum(T& a, T& b); //交换两值

//----------------------
//输出整条链表数据 限定TSimpleDoubleLL类(原TLinkedList)及其子类
//或者模板T类含int getLength() 以及int getDataArray(string[], int, int)成员函数 详细定义与功能见SimpleLinkedList.h
//----------------------
template<class T>
int printODLL(T & target);

template<class T>
int printODLL(T & target)
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

//----------------------
//绝对值
//----------------------
template<typename T>
T abs(T number)
{
	return number > 0 ? number : -1 * number;
}

//----------------------
//查找长length的array数组 是否存在target 返回下标
//不存在则返回length
//O(n)
//----------------------
template<class T>
int findElem(T* array, int length, T target)
{
	if (length == 0)
	{
		return length;
	}
	for (int i = length - 1; i >= 0; i--)
	{
		if (array[i] == target)
		{
			return i;
		}
	}
	return length;
}

template<class T>
int findElem(T& array, int length, T target)
{
	if (length == 0)
	{
		return length;
	}
	for (int i = length - 1; i >= 0; i--)
	{
		if (array[i] == target)
		{
			return i;
		}
	}
	return length;
}
//----------------------
//交换a与b
//----------------------
template<class T>
void swapNum(T& a, T& b)
{
	T tmp = a; //swap
	a = b;
	b = tmp;
}

//----------------------
//顺序打印array
//----------------------
template<class T>
void printArray(T& array, int length, string name) //循序print
{
	cout << name << " = ";
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

template<class T>
void printArray(T* array, int length, string name) //循序print
{
	cout << name << " = ";
	for (int i = 0; i < length; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}
//----------------------
//逆序打印array 每四位一空格 供十六进制使用
//----------------------
template<class T>
void tnirpArray(T& array, int length, string name) //反向print
{
	cout << name << " = ";
	for (int i = length - 1; i >= 0; i--)
	{
		cout << array[i] << " ";
		if (i % 4 == 0)
		{
			cout << " ";
		}
	}
	cout << endl;
}

template<class T>
void tnirpArray(T* array, int length, string name) //反向print
{
	cout << name << " = ";
	for (int i = length - 1; i >= 0; i--)
	{
		cout << array[i] << " ";
		if (i % 4 == 0)
		{
			cout << " ";
		}
	}
	cout << endl;
}
//----------------------
//插入排序 O(n^2)
//----------------------
template<class T>
void sortInsert(T& array, int length)
{
	int pos = 0;
	for (int i = 0; i < length - 1; i++)
	{
		pos = i;
		for (int j = length - 1; j > i; j--)
		{
			if (array[j] < array[pos]) //比较
			{
				pos = j; //记录位置调节
			}
		}
		if (pos != 0) //非0 有匹配到需要交换的元素
		{
			swapNum(array[i], array[pos]);
		}
	}
}

//----------------------
//希尔排序 O(n^2/3)
//----------------------
//template<class T> //TODO 完成排序
//void sortHill(T& array, int length)
//{
	//int increase = length;
	//for (int i = 0; i < log2(length); i++)
	//{
		//int increase /= 2;
		//for (int j = ; j > i; j--)
		//{
		//}
	//}
//}
//----------------------
//交换a与b
//----------------------
template<class T>
T aluAdd(T a, T b)
{
		int bitRateA = log2(a);
		int bitRateB = log2(b);
		//cout << bitRateA << " < A bitRate B > "<< bitRateB << endl;
		T CarryHalf = a & b; //半加进位
		T StdHalf = a ^ b; //半加本位
		//cout << CarryHalf << " < CH, SH > " << StdHalf << endl;
		int biggerRate = bitRateA > bitRateB ? bitRateA : bitRateB;
		bool bitCarryHalf[biggerRate];
		bool bitStdHalf[biggerRate];
		initArray(bitCarryHalf, biggerRate); //初始化为0
		initArray(bitStdHalf, biggerRate);
		dexToBin(CarryHalf, bitCarryHalf); //为全加进位作准备 转为二进制
		dexToBin(StdHalf, bitStdHalf);
		//Tnirp(bitCarryHalf, biggerRate); //Debug
		//Tnirp(bitStdHalf, biggerRate);
		bool bitCarryFull[biggerRate];
		initArray(bitCarryFull, biggerRate); //初始化为0
		bitCarryFull[0] = bitCarryHalf[0]; //第0位没有上一位 所以半加进位等同于全加进位
		for (int i = 1; i < biggerRate;i++) //逐位运算全加进位
		{
			bitCarryFull[i] = (bitCarryFull[i - 1] & bitStdHalf[i]) | bitCarryHalf[i];
		}
		//Tnirp(bitCarryFull, biggerRate);
		T CarryFull;
		binToDex(bitCarryFull, biggerRate, CarryFull);
		//cout << "StdHalf = " << StdHalf << ";CarryFull = " << CarryFull << endl;
		T StdFull = StdHalf ^ (CarryFull << 1); //全加本位
		return StdFull;
}

//----------------------
//初始化数组为0
//----------------------
template<class T>
void initArray(T* array, int length, T initNum)
{
	for (int i = 0; i < length; i++)
	{
		array[i] = initNum;
	}
}

//----------------------
//如函数名 log2(num) 向上取整
//----------------------
int log2(int num)
{
	int result = 1; //向上取整
	while (num > 1)
	{
		num /= 2;
		result++;
	}
	return result;
}

//----------------------
//十进制转二进制
//----------------------
void dexToBin(int a, bool* bitArray)
{
	for (int i = 0; i < log2(a); i++)
	{
		bitArray[i] = a & (1 << i);
	}
}

//----------------------
//二进制转十进制
//----------------------
void binToDex(bool* bitArray, int length, int &a)
{
	a = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		a <<= 1;
		a += bitArray[i];
	}
}


#endif
