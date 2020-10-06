#include <iostream>
#include <string>
#include "Toolkit.h"
#include "SignalSlot.h"
#include "LineList.h"

int SubSignalSlot();
int SubLinkList(int mode = 0);

int main(int argc, char* argv[])
{
	LinkedList<int> testList(100);
	std::cout << testList[0] << std::endl;
	testList[0] = 50;
	std::cout << testList[0] << std::endl;
	testList.pop_back(250);
	testList.pop_back(500);
	testList.pop_back(750);
	std::cout << "size = " << testList.size() << std::endl;
	std::cout << "realSize = " << testList.hard_size() << std::endl;
	for (int i = 0; i < testList.size(); i++)
	{
		std::cout << testList[i] << std::endl;
	}
	//SubLinkList(0);
	//SubSignalSlot();
	return 0;
}

int SubSignalSlot()
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
		ThisIsKeyboard.touch(keyboardInput);
	}
	system("pause");
	return 0;
}

int SubLinkList(int mode) //0->linelist, 1->stack, 2->queue
{
	TLinkedList<long> head(1);
	TStack<float> boat;
	TQueue<double> unit;
	switch (mode)
	{
	case 0:
		std::cout << "\n================================\n\n";
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
		std::cout << "\n================================\n\n";
		break;
	case 1:
		std::cout << "\n================================\n\n";
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
		break;
	case 2:
		std::cout << "\n================================\n\n";
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
		break;
	}
	system("pause");
	return 0;
}
