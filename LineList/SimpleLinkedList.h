#ifndef _SIMPLE_LINKED_LIST_H_
#define _SIMPLE_LINKED_LIST_H_
#include "Toolkit.h"

template<class T>
struct LLDB
{
	T node;
	LLDB<T>* next;
};

template<class T>
class LL
{
private:
	LLDB<T>* head;
	int length;
public:
	LL(T node = 0);
	LLDB<T>* dataFindPosPrev(T data); //找到其data节点的父节点地址
	LLDB<T>* posFindPosPrev(int pos); //找到其第pos个节点的父节点地址
	void insertNode(int pos, T node); //在第pos节点后添加新节点
	void deleteNode(T node); //找到node并删除
	void printAll();
};

template<class T>
LL<T>::LL(T node)
{
	this->head = new LLDB<T>(node);
}

template<class T>
LLDB<T>* LL<T>::dataFindPosPrev(T data) //找到其data节点的父节点地址
{
	LL<T>* pointer = this->head;
	while (pointer->next->node != data && pointer->next != nullptr) //遍历
	{
		pointer = pointer->next;
	}
	return pointer;
}

template<class T>
LLDB<T>* LL<T>::posFindPosPrev(int pos) //找到其第pos个节点的父节点地址
{
	LL<T>* pointer = this->head;
	int i = pos - 1;
	while (i != 0 && pointer->next != nullptr) //遍历
	{
		pointer = pointer->next;
		pos--;
	}
	return pointer;
}

template<class T>
void LL<T>::insertNode(int pos, T node) //在第pos节点后添加新节点
{
	LL<T>* getPointerRoot = this->posFindPosPrev(pos); //获取父节点位置
	if (pos != 0) //非头插入
	{
		LL<T>* tmpNext = getPointerRoot->next; //临时备份下一节点
		getPointerRoot->next = new LL<T>(node); //创建节点
		getPointerRoot->next->next = tmpNext; //将新节点与旧节点连接
	}
	else //头插入
	{
		LL<T>* tmpNext = this->head; //临时备份下一节点
		this->head = new LL<T>(node); //创建节点
		this->head->next = tmpNext; //将新节点与旧节点连接
	}
}

template<class T>
void LL<T>::deleteNode(T node) //找到node并删除
{
	LL<T>* getPointerRoot = this->dataFindPosPrev(node); //获取父节点位置
	if (this->head->node != node) //非头删除
	{
		LL<T>* tmpNext = getPointerRoot->next->next; //临时备份下一节点
		delete getPointerRoot->next; //删除节点
		getPointerRoot->next = tmpNext; //将新节点与旧节点连接
	}
	else //头删除
	{
		LL<T>* tmpNext = this->head->next; //临时备份下一节点
		delete this->head; //删除节点
		this->head = tmpNext; //将新节点与旧节点连接
	}
}

template<class T>
void LL<T>::printAll()
{
	LL<T>* printHead = this->head;
	while(printHead != nullptr)
	{
		cout << printHead->node << " ";
		printHead = printHead->next;
	}
	cout << endl;
}

#endif
