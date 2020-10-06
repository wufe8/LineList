#include <iostream>
#include <string>
#include "Toolkit.h"
#include "SignalSlot.h"
#include "LineList.h"
#include "SimpleLinkedList.h"

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
	std::cout << "realSize = " << testList.hard_size() << std::endl;
	printEachNode(testList);
	testList.erase(1);
	printEachNode(testList);

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
	TSimpleDoubleLL<long> head(1);
	TStackSDLL<float> boat;
	TQueueSDLL<double> unit;
	switch (mode)
	{
	case 0:
		std::cout << "\n================================\n\n";
		printTSLL(head);
		head.addData(10, 0);
		printTSLL(head);
		head.addList(2, 0);
		printTSLL(head);
		head.addData(20, 1);
		printTSLL(head);
		head.addList(3, 1);
		printTSLL(head);
		head.addList(4, 2);
		printTSLL(head);
		head.addList(5, 2);
		printTSLL(head);
		head.delList(0);
		printTSLL(head);
		head.addList(100, -1);
		printTSLL(head);
		head.delList(3);
		printTSLL(head);
		head.delList(3);
		printTSLL(head);
		head.delList(3);
		printTSLL(head);
		std::cout << "\n================================\n\n";
		break;
	case 1:
		std::cout << "\n================================\n\n";
		printTSLL(boat);
		boat.setLength();
		printTSLL(boat);
		boat.push(10);
		printTSLL(boat);
		boat.push(20);
		printTSLL(boat);
		boat.push(30);
		printTSLL(boat);
		boat.peek();
		printTSLL(boat);
		boat.pop();
		printTSLL(boat);
		boat.push(40);
		printTSLL(boat);
		boat.pop();
		printTSLL(boat);
		boat.pop();
		printTSLL(boat);
		boat.peek();
		printTSLL(boat);
		boat.push(50);
		printTSLL(boat);
		boat.pop();
		printTSLL(boat);
		boat.pop();
		printTSLL(boat);
		boat.pop();
		printTSLL(boat);
		boat.peek();
		printTSLL(boat);
		boat.pop();
		std::cout << "\n================================\n\n";
		break;
	case 2:
		std::cout << "\n================================\n\n";
		unit.setLength();
		printTSLL(unit);
		unit.push(10);
		printTSLL(unit);
		unit.push(20);
		printTSLL(unit);
		unit.push(30);
		printTSLL(unit);
		unit.peek();
		printTSLL(unit);
		unit.pop();
		printTSLL(unit);
		unit.push(40);
		printTSLL(unit);
		unit.pop();
		printTSLL(unit);
		unit.pop();
		printTSLL(unit);
		unit.peek();
		printTSLL(unit);
		unit.push(50);
		printTSLL(unit);
		unit.pop();
		printTSLL(unit);
		unit.pop();
		printTSLL(unit);
		unit.pop();
		printTSLL(unit);
		unit.peek();
		printTSLL(unit);
		unit.pop();
		break;
	}
	system("pause");
	return 0;
}
