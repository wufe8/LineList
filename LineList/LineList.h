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

//实际链表
template<typename T>
class LinkedListDB;

//链表代理 使用std::list类似的双向链表 成员函数也尽可能完全兼容 另不使用迭代器管理 而是代理类
template<typename T>
class LinkedList
{
private:
	LinkedListDB<T>* head; //存储实际链表的头节点
	int totalLength; //每次成功的变更链表长度都应主动修改此成员
	LinkedListDB<T>* lastPtr; //上一次访问位置的地址
	int lastIdx; //上一次操作的位置
public:
	LinkedList(T elem = 0); //构造函数
	~LinkedList(); //析构函数
	T & operator[](int pos); //返回对应位置数据的引用
	void insert(int pos, T elem); //将elem插入到pos位置 返回插入后位置
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
	if (pos > this->totalLength - 1) //请求节点大于链表长度 报错
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
	lastIdx = pos;
	lastPtr = tmp;
	return tmp->node;
} //返回对应位置数据的引用

template<typename T>
void LinkedList<T>::insert(int pos, T elem)
{
	switch (pos)
	{
	case 0: //头节点插入 使用pop_front(T)方法
		pop_front(elem);
		break;
	case this->totalLength - 1: //尾节点插入 使用pop_back(T)方法 
		pop_back(elem);
		break;
	default:
		if (pos > this->totalLength - 1) //请求节点大于链表长度 报错
		{
			std::cout << "[ERROR] LinkedList::insert : input index is out of LinkedList length" << std::endl;
			return;
		}
		int headToPos = pos;
		int tailToPos = this->size() - 1 - pos;
		int lastToPos = this->lastIdx() - abs(pos);
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
	}
} //将elem插入到pos位置 返回插入后位置

template<typename T>
T LinkedList<T>::erase(int pos)
{
	switch (pos)
	{
	case 0: //头节点插入 使用pop_front(T)方法
		return push_front(pos);
		//break;
	case this->totalLength - 1: //尾节点插入 使用pop_back(T)方法 
		return push_back(pos);
		//break;
	default:
		if (pos > this->totalLength - 1) //请求节点大于链表长度 报错
		{
			std::cout << "[ERROR] LinkedList::insert : input index is out of LinkedList length" << std::endl;
			return;
		}
		int headToPos = pos;
		int tailToPos = this->size() - 1 - pos;
		int lastToPos = this->lastIdx() - abs(pos);
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
	return this->head->prev->node;
} //返回最后一个节点的数据

template<typename T>
T LinkedList<T>::push_back()
{
	T tmpData = this->head->node;
	LinkedListDB<T>* tmpPtr = this->head->prev;
	tmpPtr->next->prev = tmpPtr->prev; //将头节点的上一个节点更新为倒二节点
	tmpPtr->prev->next = tmpPtr->next; //将倒二节点的下一个节点更改为头节点
	this->lastIdx = 0;
	this->lastPtr = tmpPtr->prev;
	delete tmpPtr; //删除根节点
	(this->totalLength)--; //刷新链表长度
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
	this->lastIdx = 0;
	this->lastPtr = this->head;
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
	this->lastIdx = 0;
	this->lastPtr = tmpPtrNext;
	delete this->head; //删除根节点
	this->head = tmpPtrNext->prev; //更新根节点
	(this->totalLength)--; //刷新链表长度
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
	tmpPtrNext->prev = this->head
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

//----------------------
//双向链表
//----------------------
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
TLinkedList<T>::TLinkedList(T data) :
	data(data),
	next(NULL),
	prev(NULL)
{
}
template<typename T>
inline int TLinkedList<T>::checkNextIsNull() //检查下一个节点是否为NULL
{
	if (this->next == NULL)
	{
		std::cout << "ERROR: this->next == NULL; in " << this << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename T>
inline int TLinkedList<T>::checkPrevIsNull() //检查上一个节点是否为NULL
{
	if (this->prev == NULL)
	{
		std::cout << "ERROR: this->prev == NULL; in " << this << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename T>
T TLinkedList<T>::getData(int pos) //获取pos节点的data
{
	TLinkedList* point = this; //loop
	for (int i = pos; i > 0; i--)
	{
		if (point->checkNextIsNull())
		{
			return -1;
		}
		else
		{
			point = point->next;
		}
	}
	return point->data;
	/*T data; //recursive
	if (pos > 0)
	{
		if (checkNextIsNull())
		{
			return 0;
		}
		data = this->next->getData(pos - 1);
	}
	else
	{
		return this->data;
	}
	return data;*/
}

template<typename T>
int TLinkedList<T>::getDataArray(std::string* array, int pos, int length) //将pos到length间的节点data赋到array[0 to length]
{
	if (array == NULL) //check array
	{
		std::cout << "array is NULL!" << std::endl;
		return -1;
	}
	if (array + length - 1 == NULL) //check array[length - 1]
	{
		std::cout << "length is wrong!" << std::endl;
		return -2;
	}
	array[pos] = std::to_string(this->data); //get data
	if (pos < length -1)
	{
		if (this->next == NULL) //check next is NULL
		{
			return -3;
		}
		this->next->getDataArray(array, length, pos + 1);
	}
	return 0;
}

template<typename T>
TLinkedList<T>* TLinkedList<T>::getPos(int pos) //获取pos节点的内存地址
{
	TLinkedList* point = this; //loop
	for (int i = pos; i > 0; i--)
	{
		if (point->checkNextIsNull())
		{
			return 0;
		}
		else
		{
			point = point->next;
		}
	}
	return point;
	/*TLinkedList* next; //recursive
	if (pos > 0)
	{
		if (checkNextIsNull())
		{
			return 0;
		}
		next = this->next->getPos(pos - 1);
	}
	else
	{
		return this;
	}*/
}

template<typename T>
int TLinkedList<T>::addData(T data, int pos) //在pos节点给data赋值
{
	TLinkedList* point = this; //loop
	for (int i = pos; i > 0; i--)
	{
		if (point->checkNextIsNull())
		{
			return -1;
		}
		else
		{
			point = point->next;
		}
	}
	point->data = data;
	/*if (pos > 0) //recursive
	{
		if (checkNextIsNull())
		{
			return -1;
		}
		this->next->addData(data, pos - 1);
	}
	else
	{
		this->data = data;
	}*/
	return 0;
}

template<typename T>
int TLinkedList<T>::addList(T data, int pos) //在pos节点后添加新节点, 并赋data
{
	if (pos == -1) //create in head, in fact it just create next to head and copy head, add new data and next in head 
	{
		TLinkedList* pointerBuffer = this->next;
		TLinkedList* newNode = new TLinkedList(this->data);
		this->next = newNode;
		newNode->next = pointerBuffer;
		this->data = data;
		std::cout << "added " << data << " in [" << pos << "] ;add type: head" << std::endl;
		return 0;
	}
	TLinkedList* point = this;
	for (int i = pos; i > 0; i--)
	{
		if (point->checkNextIsNull())
		{
			return -1;
		}
		else
		{
			point = point->next;
		}
	}
	if (point->next == NULL) //create in tail
	{
		TLinkedList* newNode = new TLinkedList(data);
		newNode->prev = point;
		point->next = newNode;
		std::cout << "added " << data << " in [" << pos << "] ;add type: tail" << std::endl;
		return 0;
	}
	else
	{
		TLinkedList* newNode = new TLinkedList(data);
		newNode->prev = this;
		TLinkedList* pointerBuffer = this->next;
		this->next = newNode;
		this->next->next = pointerBuffer;
		std::cout << "added " << data << " in [" << pos << "] ;add type: insert" << std::endl;
		return 0;
	}
	/*else if (pos > 0) //recursive
	{
		if (checkNextIsNull())
		{
			return -1;
		}
		this->next->addList(data, pos - 1);
	}
	else
	{
		if (this->next == NULL) //create in tail
		{
			TLinkedList* newNode = new TLinkedList(data);
			newNode->prev = this;
			this->next = newNode;
			std::cout << "added "  << data << " in [" << pos << "] ;add type: tail" << std::endl;
			return 0;
		}
		else
		{
			TLinkedList* newNode = new TLinkedList(data);
			newNode->prev = this;
			TLinkedList* pointerBuffer = this->next;
			this->next = newNode;
			this->next->next = pointerBuffer;
			std::cout << "added "  << data << " in [" << pos << "] ;add type: insert" << std::endl;
			return 0;
		}
	}*/
	return 0;
}

template<typename T>
T TLinkedList<T>::delList(int pos) //删除pos节点
{
	T deletedData = 0;
	if (pos == 0) //del the head, in fact it just copy this->next, then delete this->next
	{
		if (this->next == NULL) //No node left
		{
			deletedData = this->data;
			this->data = 0;
			return deletedData;
		}
		deletedData = this->data;
		TLinkedList* pointerBuffer = this->next->next;
		T data = this->next->data;
		delete this->next;
		this->next = pointerBuffer;
		this->data = data;
		std::cout << "deleted [" << pos << "] ;delete type: head" << std::endl;
		return 0;
	}
	TLinkedList* pointerBuffer = this; //loop
	for (int i = pos; i > 0; i--)
	{
		if (pointerBuffer->checkNextIsNull())
		{
			return -1;
		}
		else
		{
			pointerBuffer = pointerBuffer->next;
		}
	}
	if (pointerBuffer->next == NULL) //del the tail
	{
		pointerBuffer->prev->next = NULL;
		deletedData = pointerBuffer->data;;
		delete pointerBuffer;
		std::cout << "deleted [" << pos << "] ;delete type: tail" << std::endl;
	}
	else //del the middle
	{
		pointerBuffer->prev->next = pointerBuffer->next;
		pointerBuffer->next->prev = pointerBuffer->prev;
		deletedData = pointerBuffer->data;
		delete pointerBuffer;
		std::cout << "deleted [" << pos << "] ;delete type: middle" << std::endl;
	}
	//if (pos > 0) //recursive
	//{
	//	if (checkNextIsNull())
	//	{
	//		return -1;
	//	}
	//	this->next->delList(pos - 1);
	//}
	//else
	//{
	//	if (this->prev == 0) //del the head, in fact it just copy this->next, then delete this->next
	//	{
	//		TLinkedList* pointerBuffer = this->next->next;
	//		T data = this->next->data;
	//		deletedData = this->data;
	//		delete this->next;
	//		this->next = pointerBuffer;
	//		this->data = data;
	//		std::cout << "deleted [" << pos << "] ;delete type: head" << std::endl;
	//		return 0;
	//	}
	//	else if (this->next == NULL) //del the tail
	//	{
	//		this->prev->next = NULL; //flash prev.next to prevent wrong recursive
	//		delete this;
	//		std::cout << "deleted [" << pos << "] ;delete type: tail" << std::endl;
	//	}
	//	else //del the middle
	//	{
	//		this->prev->next = this->next;
	//		this->next->prev = this->prev;
	//		deletedData = this->data;
	//		delete this;
	//		std::cout << "deleted [" << pos << "] ;delete type: middle" << std::endl;
	//	}
	//}
	return deletedData;
}

template<typename T>
int TLinkedList<T>::getLength() //递归获取链表长度 效率可能过低 推荐使用setLength()进行记录而非直接调用
{
	if (this->next == NULL) //check if this->next == NULL, that return tail
	{
		return 1;
	}
	else
	{
		int length = this->next->getLength();
		return length + 1; //count the length in tail to head
	}
}

template<typename T>
int TLinkedList<T>::setLength() //将链表长度记录到this->data
{
	this->data = T(getLength());
	if (this->data == 0)
	{
		std::cout << "ERROR: fail to get linkedList length.";
		return 1;
	}
	return 0;
}
//----------------------
//栈实现 父类:TLinkedList
//----------------------
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
void TStack<T>::push(T data)
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the stack!" << std::endl;
	}
	this->addList(data, this->getLength() - 1);
	std::cout << "pushed: " << data << std::endl;
}

template<typename T>
T TStack<T>::pop()
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the stack!" << std::endl;
		return -1;
	}
	T data;
	return this->delList(this->getLength() - 1);
	std::cout << "poped: " << data << std::endl;
	return data;
}

template<typename T>
T TStack<T>::peek()
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the stack!" << std::endl;
		return -1;
	}
	T data = this->getData(arrayLength - 1);
	std::cout << "peeked: " << data << std::endl;
	return data;
}

//----------------------
//队列实现 父类:TLinkedList
//----------------------
template<typename T>
class TQueue : public TLinkedList<T>
{
public:
	void push(T data);
	T pop();
	T peek();
	using TLinkedList<T>::TLinkedList; //C++11
};

template<typename T>
void TQueue<T>::push(T data)
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the queue!" << std::endl;
	}
	this->addList(data, arrayLength - 1);
	std::cout << "pushed: " << data << std::endl;
}

template<typename T>
T TQueue<T>::pop()
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the queue!" << std::endl;
		return -1;
	}
	T data = this->delList(0);
	std::cout << "poped: " << data << std::endl;
	return data;
} 



template<typename T>
T TQueue<T>::peek()
{
	int arrayLength = this->getLength();
	if (arrayLength <= 0)
	{
		std::cout << "ERROR: Nothing in the queue!" << std::endl;
		return -1;
	}
	T data = this->getData(1);
	std::cout << "peeked: " << data << std::endl;
	return data;
}
#endif
