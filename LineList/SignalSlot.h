#pragma once

#define signals public
#define slots public
#define emit
#define SIGNAL_MODLUS if (cable == nullptr) \
					{ \
						return; \
					} \
					cable->Active(); \

//template<class T0, class T1>
class Connect;

class Device //base to Signal-Slot contect
{
public:
	Connect* cable;
};


class Keyboard : public Device
{
public:
	Keyboard();
	~Keyboard();
	int touch(int num);
signals:
	void transfur();
};


class Beeper : public Device
{
public:
	Beeper();
	~Beeper();
slots:
	void beep();
};

//template<class T0, class T1>
class Connect //work for connect the Signal-Slot
{
private:
	Keyboard* sender;
	void (Keyboard::* signal)(void);
	Beeper* receiver;
	void (Beeper::* slot)(void);
	Connect* nextCable;
public:
	Connect(Keyboard* sender, void (Keyboard::* signal)(void), Beeper* receiver, void (Beeper::* slot)(void));
	~Connect();
	void Active();
};

//class SingletonPattern
//{
//private:
//	SingletonPattern();
//	static SingletonPattern Onlyone = new SingletonPattern;
//
//};
