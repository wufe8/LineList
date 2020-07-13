#ifndef _LINELIST_H_
#define _LINELIST_H_

#define NULL 0

#include <string>

template<typename T>
class TLinkedList
{
private:
	T data;
	TLinkedList* prev;
	TLinkedList* next;
protected:
	inline int checkNextIsNull();
	inline int checkPrevIsNull();
public:
	int addList(T data = 0, int pos = 0); //add a TList, add in next to the last one when pos == 0
	T delList(int pos); //delete a TList, return 0 -> sucess, -1 -> fail
	int addData(T data = 0, int pos = 0);
	T getData(int pos = 0);
	int getDataArray(std::string* array, int length, int pos = 0);
	int getLength(); //return this link list length
	int setLength(); //set to <TList>[0]->data, WILL CHANGE HEAD DATA!!
	TLinkedList* getPos(int pos = 0);
	TLinkedList(T data = 0);
};

template<typename T>
class TStack : public TLinkedList<T> //使用前请务必使用setLength()方法检测链表长度!!
{
public:
	void push(T data);
	T pop();
	T peek();
	using TLinkedList<T>::TLinkedList; //C++11
	//TStack() : TLinkedList<T>(1){};
};

template<typename T>
class TQueue : public TLinkedList<T>
{
public:
	void push(T data);
	T pop();
	T peek();
	using TLinkedList<T>::TLinkedList; //C++11
};

#endif
