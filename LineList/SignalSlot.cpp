#include <iostream>
#include "SignalSlot.h"

Keyboard::Keyboard()
{
	std::cout << "Detected keyboard connect!" << std::endl;
	cable = nullptr;
}


Keyboard::~Keyboard()
{
}


void Keyboard::touch(int num)
{
	switch(num)
	{
	case 2:
		std::cout << "100 ok" << std::endl;
		emit transfur();
		break;
	default:
		std::cout << "0   no response" << std::endl;
	}
}


void Keyboard::transfur() //signal
{
	//cable->Active();
	SIGNAL_MODLUS
}


Beeper::Beeper()
{
	std::cout << "Detected beeper connect!" << std::endl;
}


Beeper::~Beeper()
{
}


void Beeper::beep() //slot
{
	std::cout << "Beeeeeeee" << std::endl;
}

//template<class T0, class T1>
Connect/*<T0, T1>*/::Connect(Keyboard* sender, void (Keyboard::* signal)(void), Beeper* receiver, void (Beeper::* slot)(void))
	: sender(sender), receiver(receiver), signal(signal), slot(slot)
{
	if (sender->cable == nullptr)
	{
		this->nextCable = nullptr;
		sender->cable = this;
	}
	else
	{
		this->nextCable = new Connect(sender, signal, receiver, slot);
	}
}

//template<class T0, class T1>
Connect/*<T0, T1>*/::~Connect()
{
	delete this->nextCable;
}

//template<class T0, class T1>
void Connect/*<T0, T1>*/::Active()
{
	if (sender->cable != nullptr)
	{
		(receiver->*slot)();
	}
	else
	{
		this->nextCable = new Connect(sender, signal, receiver, slot);
	}
}
