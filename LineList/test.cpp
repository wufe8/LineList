#include <iostream>
#include <string>
#include "LinkTemplate.h"
#include "Toolkit.h"
#include "SignalSlot.h"
//#include "SignalSlot.cpp"

int main(int argc, char* argv[])
{
	Keyboard ThisIsKeyboard;
	Beeper ThisIsBeeper;
	std::cout << "ThisIsKeyboard.transfur = 0x" << &ThisIsKeyboard << " + " << &Keyboard::transfur << std::endl;
	std::cout << "ThisIsBeeper.beep = 0x" << &ThisIsBeeper << " + " << &Beeper::beep << std::endl;
	Connect/*<Keyboard, Beeper>*/ Bus0(&ThisIsKeyboard, &Keyboard::transfur, &ThisIsBeeper, &Beeper::beep);
	int keyboardInput = 0;
;	while(1)
	{
		printf_s("%s", "local > ");
		if (scanf_s("%d", &keyboardInput) == 0)
		{
			while (getchar() != '\n');
			std::cout << "200 error input" << std::endl;
			continue;
		}
		//std::cin >> keyboardInput;
		//std::cin.clear(); std::cin.ignore();
		ThisIsKeyboard.touch(keyboardInput);
	}
	system("pause");
	return 0;
}

//int main()
//{
//	TStack<float> boat;
//	printLineList(&boat);
//	boat.setLength();
//	printLineList(&boat);
//	boat.push(10);
//	printLineList(&boat);
//	boat.push(20);
//	printLineList(&boat);
//	boat.push(30);
//	printLineList(&boat);
//	boat.peek();
//	printLineList(&boat);
//	boat.pop();
//	printLineList(&boat);
//	boat.push(40);
//	printLineList(&boat);
//	boat.pop();
//	printLineList(&boat);
//	boat.pop();
//	printLineList(&boat);
//	boat.peek();
//	printLineList(&boat);
//	boat.push(50);
//	printLineList(&boat);
//	boat.pop();
//	printLineList(&boat);
//	boat.pop();
//	printLineList(&boat);
//	boat.pop();
//	printLineList(&boat);
//	boat.peek();
//	printLineList(&boat);
//	boat.pop();
//	std::cout << "\n================================\n\n";
//	TQueue<double> unit;
//	unit.setLength();
//	printLineList(&unit);
//	unit.push(10);
//	printLineList(&unit);
//	unit.push(20);
//	printLineList(&unit);
//	unit.push(30);
//	printLineList(&unit);
//	unit.peek();
//	printLineList(&unit);
//	unit.pop();
//	printLineList(&unit);
//	unit.push(40);
//	printLineList(&unit);
//	unit.pop();
//	printLineList(&unit);
//	unit.pop();
//	printLineList(&unit);
//	unit.peek();
//	printLineList(&unit);
//	unit.push(50);
//	printLineList(&unit);
//	unit.pop();
//	printLineList(&unit);
//	unit.pop();
//	printLineList(&unit);
//	unit.pop();
//	printLineList(&unit);
//	unit.peek();
//	printLineList(&unit);
//	unit.pop();
//	std::cout << "\n================================\n\n";
//	TLinkedList<long> head(1);
//	printLineList(&head);
//	head.addData(10, 0);
//	printLineList(&head);
//	head.addList(2, 0);
//	printLineList(&head);
//	head.addData(20, 1);
//	printLineList(&head);
//	head.addList(3, 1);
//	printLineList(&head);
//	head.addList(4, 2);
//	printLineList(&head);
//	head.addList(5, 2);
//	printLineList(&head);
//	head.delList(0);
//	printLineList(&head);
//	head.addList(100, -1);
//	printLineList(&head);
//	head.delList(3);
//	printLineList(&head);
//	head.delList(3);
//	printLineList(&head);
//	head.delList(3);
//	printLineList(&head);
//	system("pause");
//	return 0;
//}