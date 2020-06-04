#pragma once
#ifndef _LINELIST_H_
#define _LINELIST_H_

#define NULL 0

class TLinkedList
{
private:
	int data;
	TLinkedList* prev;
	TLinkedList* next;
protected:
	inline int checkNextIsNull();
	inline int checkPrevIsNull();
public:
	int addList(int data = 0, int pos = 0); //add a TList, add in next to the last one when pos == 0
	int delList(int pos); //delete a TList, return 0 -> sucess, -1 -> fail
	int addData(int data = 0, int pos = 0);
	int getData(int pos = 0);
	int getDataAlloy(int* alloy, int length, int pos = 0);
	int getLength(); //return this link list length
	int setLength(); //set to <TList>[0]->data, WILL CHANGE HEAD DATA!!
	TLinkedList* getPos(int pos = 0);
	TLinkedList(int data = 0);
};

class TStack : public TLinkedList //使用前请务必使用setLength()方法检测链表长度!!
{
public:
	void push(int data);
	int pop();
	using TLinkedList::TLinkedList; //C++11
	//TStack() : TLinkedList(1){};
};

class TQueue : public TLinkedList
{

};

#endif
