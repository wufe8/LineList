#ifndef _LINELIST_H_
#define _LINELIST_H_

#ifndef NULL
#define NULL 0
#endif

#include <iostream>
#include <string>
#include <vector>

template<typename T>
T abs(T number)
{
	return number > 0 ? number : -1 * number;
} //简单计算绝对值

//----------------------
//实际链表
//----------------------
template<typename T>
class LinkedListDB;

//----------------------
//链表代理
//使用std::list类似的双向链表 成员函数也尽可能完全兼容 
//不使用迭代器管理 使用代理类
//----------------------
template<typename T>
class LinkedList
{
private:
	LinkedListDB<T>* head; //存储实际链表的头节点
	int totalLength; //每次成功的变更链表长度都应主动修改此成员
	LinkedListDB<T>* lastPtr; //上一次写入的地址
	int lastIdx; //上一次写入的位置
public:
	LinkedList(T elem = 0); //构造函数
	~LinkedList(); //析构函数
	T & operator[](int pos); //返回对应位置数据的引用 不会记录lastIdx以及lastPtr TODO 添加返回const引用的重载函数
	void insert(int pos, T elem); //将elem插入到pos位置
	T erase(int pos); //将pos位置的节点删除 返回删除值
	T at(int pos); //返回idx位置节点的数据
	T peek_back(); //返回最后一个节点的数据
	T push_back(); //推出尾部 返回并删除最后一个节点的数据
	void pop_back(T elem); //压入尾部 将elem插入到尾部
	T peek_front(); //返回第一个节点的数据
	T push_front(); //推出头部 返回并删除第一个节点的数据
	void pop_front(T elem); //压入头部 将elem插入到头部
	int size(); //返回链表长度 直接返回totalLength 时间复杂度应该为O(1)
	int hard_size(); //同上 但进行递归计数 不建议使用 时间复杂度应该为O(N)
};

//实际链表原型
template<typename T>
class LinkedListDB
{
public:
	T node;
	LinkedListDB* next;
	LinkedListDB* prev;
	LinkedListDB(T elem = 0);
	~LinkedListDB();
	//void operator=(T elem);
};

template<typename T>
LinkedListDB<T>::LinkedListDB(T elem)
{
	this->node = elem;
	this->next = nullptr;
	this->prev = nullptr;
} //构造函数

template<typename T>
LinkedListDB<T>::~LinkedListDB()
{
} //析构函数

//template<typename T>
//void LinkedListDB<T>::operator=(T elem)
//{
	//this->node = elem;
//} //重载赋值符

template<typename T>
LinkedList<T>::LinkedList(T elem)
{
	this->head = new LinkedListDB<T>(elem); //存储实际链表的头节点
	this->head->next = this->head;
	this->head->prev = this->head;
	this->totalLength = 1; //每次成功的变更链表长度都应主动修改此成员
	this->lastPtr = this->head;
	this->lastIdx = 0;
} //构造函数

template<typename T>
LinkedList<T>::~LinkedList()
{
	if (this->head->prev == this->head) //如果长度等于1 直接删除并结束函数
	{
		delete this->head;
		return;
	}
	else if (this->head->prev == this->head->next) //如果长度等于1 直接删除并结束函数
	{
		delete this->head->next;
		delete this->head;
		return;
	}
	LinkedListDB<T>* tmp = this->head->prev; //长度大于等于3 从尾部开始删除
	while (tmp != this->head->next) //重复删除直到总长为2
	{
		tmp = tmp->prev; //tmp指针往前移动
		delete tmp->next; //删除原节点
	}
	delete this->head->next; //将剩余2个节点也删除
	delete this->head;
} //析构函数

template<typename T>
T & LinkedList<T>::operator[](int pos)
{
	if (pos > this->totalLength - 1) //请求节点大于链表长度-1 报错
	{
		std::cout << "[ERROR] LinkedList::operator[] : input index is out of LinkedList length" << std::endl;
		return *(T*)NULL; //返回空引用
	}
	else if (pos == this->totalLength - 1) //请求节点为尾部 直接返回结果
	{
		return this->head->prev->node;
	}
	else if (pos == 0) //请求节点为头部 直接返回结果
	{
		return this->head->node;
	}
	LinkedListDB<T>* tmp = this->head;
	for (int i = 0; i < pos ;i++)
	{
		tmp = tmp->next;
	}
	//lastIdx = pos;
	//lastPtr = tmp;
	//注意可能导致通过重载赋值不会记录到lastIdx与lastPtr中
	return tmp->node;
} //返回对应位置数据的引用

template<typename T>
void LinkedList<T>::insert(int pos, T elem)
{
	if(pos == 0) //头节点插入 使用pop_front(T)方法
	{
		this->pop_front(elem);
		return;
	}
	else if (pos == this->totalLength) //尾节点插入 使用pop_back(T)方法 
	{
		this->pop_back(elem);
		return;
	}
	else
	{
		if (pos > this->totalLength) //请求节点大于链表长度 报错
		{
			std::cout << "[ERROR] LinkedList::insert : input index is out of LinkedList length" << std::endl;
			return;
		}
		int headToPos = pos;
		int tailToPos = this->size() - 1 - pos;
		int lastToPos = this->lastIdx - abs(pos);
		//三分比较距离 理论上最大时间复杂度为只从链表头开始循环的三分之一 TODO 完成判断与不同情况的循环方式
		LinkedListDB<T>* tmpPtrNext = this->head;
		for (int i = 0; i < pos ;i++)
		{
			tmpPtrNext = tmpPtrNext->next;
		}
		LinkedListDB<T>* tmpPtrPrev = tmpPtrNext->prev;
		tmpPtrPrev->next = new LinkedListDB<T>(elem);
		tmpPtrNext->prev = tmpPtrPrev->next;
		tmpPtrPrev->next->prev = tmpPtrPrev;
		tmpPtrPrev->next->next = tmpPtrNext;
		this->lastIdx = pos;
		this->lastPtr = tmpPtrPrev->next;
		(this->totalLength)++;
		return;
	}
} //将elem插入到pos位置 返回插入后位置

template<typename T>
T LinkedList<T>::erase(int pos)
{
	if (pos == 0) //头节点删除 使用push_front()方法
	{
		return this->push_front();
		//break;
	}
	else if (pos == this->totalLength - 1) //尾节点删除 使用push_back()方法 
	{
		return this->push_back();
		//break;
	}
	else
	{
		if (pos > this->size() - 1) //请求节点大于链表长度-1 报错
		{
			std::cout << "[ERROR] LinkedList::insert : input index is out of LinkedList length" << std::endl;
			return *(T*)NULL; //返回空引用
		}
		int headToPos = pos;
		int tailToPos = this->size() - 1 - pos;
		int lastToPos = this->lastIdx - abs(pos);
		//三分比较距离 理论上最大时间复杂度为只从链表头开始循环的三分之一 TODO 完成判断与不同情况的循环方式
		LinkedListDB<T>* tmpPtr = this->head;
		for (int i = 0; i < pos ;i++)
		{
			tmpPtr = tmpPtr->next;
		}
		T tmpData = tmpPtr->node;
		tmpPtr->next->prev = tmpPtr->prev;
		tmpPtr->prev->next = tmpPtr->next;
		this->lastIdx = pos;
		this->lastPtr = tmpPtr->next;
		delete tmpPtr;
		(this->totalLength)--;
	}
	return 0;
} //将pos位置的节点删除 返回删除值

template<typename T>
T LinkedList<T>::at(int pos)
{
	return this->operator[](pos);
} //返回pos位置节点的数据

template<typename T>
T LinkedList<T>::peek_back()
{
	//this->lastIdx = this->totalLength - 1;
	//this->lastPtr = this->head->prev;
	return this->head->prev->node;
} //返回最后一个节点的数据

template<typename T>
T LinkedList<T>::push_back()
{
	T tmpData = this->head->node;
	LinkedListDB<T>* tmpPtr = this->head->prev;
	tmpPtr->next->prev = tmpPtr->prev; //将头节点的上一个节点更新为倒二节点
	tmpPtr->prev->next = tmpPtr->next; //将倒二节点的下一个节点更改为头节点
	delete tmpPtr; //删除根节点
	(this->totalLength)--; //刷新链表长度
	this->lastIdx = this->totalLength - 1;
	this->lastPtr = this->head->prev;
	return tmpData;
} //推出尾部 返回并删除最后一个节点的数据

template<typename T>
void LinkedList<T>::pop_back(T elem)
{
	LinkedListDB<T>* tmpPtr = this->head->prev;
	this->head->prev = new LinkedListDB<T>(elem);
	this->head->prev->prev = tmpPtr;
	this->head->prev->next = this->head;
	tmpPtr->next = this->head->prev;
	(this->totalLength)++; //刷新链表长度
	this->lastIdx = this->totalLength - 1;
	this->lastPtr = this->head->prev;
} //压入尾部 将elem插入到尾部

template<typename T>
T LinkedList<T>::peek_front()
{
	//this->lastIdx = 0;
	//this->lastPtr = this->head;
	return this->head->node;
} //返回第一个节点的数据

template<typename T>
T LinkedList<T>::push_front()
{
	T tmpData = this->head->node;
	LinkedListDB<T>* tmpPtrPrev = this->head->prev;
	LinkedListDB<T>* tmpPtrNext = this->head->next;
	tmpPtrNext->prev = tmpPtrPrev; //将第二个节点的上一个节点更新为尾节点
	tmpPtrPrev->next = tmpPtrNext; //将尾节点的下一个节点更改为第二个节点
	delete this->head; //删除根节点
	this->head = tmpPtrNext; //更新根节点
	(this->totalLength)--; //刷新链表长度
	this->lastIdx = 0;
	this->lastPtr = this->head;
	return tmpData;
} //推出头部 返回并删除第一个节点的数据

template<typename T>
void LinkedList<T>::pop_front(T elem)
{
	LinkedListDB<T>* tmpPtrPrev = this->head->prev;
	LinkedListDB<T>* tmpPtrNext = this->head;
	this->head = new LinkedListDB<T>(elem);
	this->head->prev = tmpPtrPrev;
	this->head->next = tmpPtrNext;
	tmpPtrPrev->next = this->head;
	tmpPtrNext->prev = this->head;
	(this->totalLength)++; //刷新链表长度
	this->lastIdx = 0;
	this->lastPtr = this->head;
} //压入头部 将elem插入到头部

template<typename T>
int LinkedList<T>::size()
{
	return this->totalLength;
} //返回链表长度 直接返回totalLength 时间复杂度应该为O(1)

template<typename T>
int LinkedList<T>::hard_size()
{
	int getLength = 1;
	LinkedListDB<T>* tmp = this->head->next;
	while (tmp != this->head)
	{
		tmp = tmp->next;
		getLength++;
	}
	return getLength;
} //同上 但进行递归计数 不建议使用 时间复杂度应该为O(N)

#endif
