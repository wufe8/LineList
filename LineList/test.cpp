#include <cmath>
#include <iostream>
#include <string>
#include <type_traits>
#include "Toolkit.h"
#include "SignalSlot.h"
#include "LinkedList.h"
#include "SimpleLinkedList.h"
#include "OldDoubleLinkedList.h"
#include "SearchTree.h"
#include "AVLTree.h"

#define _CRT_SECURE_NO_WARNINGS true
#pragma warning (disable: 4996)
//msvc下忽略对scanf要求使用scanf_s的报错

void SubBinaryTree();
void SubLinkedList();
void SubSimpleLinkedList(int mode = 0);
void SubSignalSlot();

int main(int argc, char* argv[])
{
	SubBinaryTree();
	SubLinkedList();
	SubSimpleLinkedList(0);
	SubSignalSlot();
	return 0;
}

void SubBinaryTree()
{
	SearchTree<int> testTree(10);
	testTree.insert(5);
	testTree.printAll();
	testTree.insert(15);
	testTree.insert(12);
	testTree.insert(3);
	testTree.insert(8);
	testTree.insert(9);
	testTree.insert(9);
	testTree.printAll();
	std::cout << testTree.find(9) << std::endl;
	std::cout << testTree.find(1) << std::endl;
	std::cout << "min = " << testTree.findMin() << std::endl;
	testTree.remove(5);
	testTree.printAll();
	testTree.remove(10);
	testTree.remove(3);
	testTree.printAll();
	system("pause");
}

void SubLinkedList()
{
	LinkedList<int> testList(100);
	std::cout << testList[0] << std::endl;
	testList[0] = 50;
	std::cout << testList[0] << std::endl;
	testList.pop_back(250);
	testList.pop_back(500);
	testList.pop_back(750);
	std::cout << "realSize = " << testList.hard_size() << std::endl;
	printArray(testList, testList.size());
	testList.erase(1);
	printArray(testList, testList.size());
	testList.insert(2, 1000);
	printArray(testList, testList.size());
	testList.insert(1, 1250);
	printArray(testList, testList.size());
	testList.erase(2);
	printArray(testList, testList.size());
	testList.insert(4, 1500);
	printArray(testList, testList.size());
	std::cout << "testList[3] == " << testList[3] << std::endl;
	testList.pop_front(1750);
	testList.pop_front(2000);
	printArray(testList, testList.size());
	std::cout << "testList.push_front() return: " << testList.push_front() << std::endl;
	testList.pop_back(2250);
	printArray(testList, testList.size());
	system("pause");
	return;
}

void SubSimpleLinkedList(int mode) //0->linelist, 1->stack, 2->queue
{
	ODLL<long> head(1);
	TStackODLL<float> boat;
	TQueueODLL<double> unit;
	switch (mode)
	{
	case 0:
		std::cout << "\n================================\n\n";
		printODLL(head);
		head.addData(10, 0);
		printODLL(head);
		head.addList(2, 0);
		printODLL(head);
		head.addData(20, 1);
		printODLL(head);
		head.addList(3, 1);
		printODLL(head);
		head.addList(4, 2);
		printODLL(head);
		head.addList(5, 2);
		printODLL(head);
		printODLL(head);
		head.delList(0);
		head.addList(100, -1);
		printODLL(head);
		head.delList(3);
		printODLL(head);
		head.delList(3);
		printODLL(head);
		head.delList(3);
		printODLL(head);
		std::cout << "\n================================\n\n";
		break;
	case 1:
		std::cout << "\n================================\n\n";
		printODLL(boat);
		boat.setLength();
		printODLL(boat);
		boat.push(10);
		printODLL(boat);
		boat.push(20);
		printODLL(boat);
		boat.push(30);
		printODLL(boat);
		boat.peek();
		printODLL(boat);
		boat.pop();
		printODLL(boat);
		boat.push(40);
		printODLL(boat);
		boat.pop();
		printODLL(boat);
		boat.pop();
		printODLL(boat);
		boat.peek();
		printODLL(boat);
		boat.push(50);
		printODLL(boat);
		boat.pop();
		printODLL(boat);
		boat.pop();
		printODLL(boat);
		boat.pop();
		printODLL(boat);
		boat.peek();
		printODLL(boat);
		boat.pop();
		std::cout << "\n================================\n\n";
		break;
	case 2:
		std::cout << "\n================================\n\n";
		unit.setLength();
		printODLL(unit);
		unit.push(10);
		printODLL(unit);
		unit.push(20);
		printODLL(unit);
		unit.push(30);
		printODLL(unit);
		unit.peek();
		printODLL(unit);
		unit.pop();
		printODLL(unit);
		unit.push(40);
		printODLL(unit);
		unit.pop();
		printODLL(unit);
		unit.pop();
		printODLL(unit);
		unit.peek();
		printODLL(unit);
		unit.push(50);
		printODLL(unit);
		unit.pop();
		printODLL(unit);
		unit.pop();
		printODLL(unit);
		unit.pop();
		printODLL(unit);
		unit.peek();
		printODLL(unit);
		unit.pop();
		break;
	}
	system("pause");
	return;
}


void SubSignalSlot()
{
	Keyboard ThisIsKeyboard;
	Beeper ThisIsBeeper;
	std::cout << "ThisIsKeyboard.transfur = 0x" << &ThisIsKeyboard << " + " << &Keyboard::transfur << std::endl;
	std::cout << "ThisIsBeeper.beep = 0x" << &ThisIsBeeper << " + " << &Beeper::beep << std::endl;
	Connect/*<Keyboard, Beeper>*/ Bus0(&ThisIsKeyboard, &Keyboard::transfur, &ThisIsBeeper, &Beeper::beep);
	int keyboardInput = 0;
	while(1)
	{
		printf("%s", "local > ");
		if (scanf("%d", &keyboardInput) == 0)
		{
			while (getchar() != '\n');
			std::cout << "200 error input" << std::endl;
			continue;
		}
		//std::cin >> keyboardInput;
		//std::cin.clear(); 
		//td::cin.ignore();
		if (ThisIsKeyboard.touch(keyboardInput) == 1)
		{
			break;
		}
	}
	system("pause");
	return;
}

