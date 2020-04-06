#ifndef _LINELIST_H_
#define _LINELIST_H_
#pragma once

#define NULL 0

class TList
{
private:
	int data;
	TList* prev;
	TList* next;
protected:
	int checkNextIsNull();
	int checkPrevIsNull();
public:
	int addList(int data = 0, int pos = 0); //add a TList, add in next to the last one when pos == 0
	int delList(int pos); //delete a TList, return 0 -> sucess, -1 -> fail
	int addData(int data = 0, int pos = 0);
	int getData(int pos = 0);
	int getDataAlloy(int* alloy, int length, int pos = 0);
	int getLength(); //return this link list length
	TList* getPos(int pos = 0);
	TList(int data);
};

//class PList : public TList
//{
//private:
//	TList* head;
//	TList* tail;
//public:
//	int init();
//	int 
//	PList();
//};

#endif
