#ifndef _SIMPLELINKEDLIST_H_
#define _SIMPLELINKEDLIST_H_

#include <iostream>
#include <string>
#include <vector>

//----------------------
//简单双向链表
//----------------------
template<typename T>
class TSimpleDoubleLL
{
private:
	T data;
	TSimpleDoubleLL* prev;
	TSimpleDoubleLL* next;
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
	TSimpleDoubleLL* getPos(int pos = 0);
	TSimpleDoubleLL(T data = 0);
};

template<typename T>
TSimpleDoubleLL<T>::TSimpleDoubleLL(T data) :
	data(data),
	next(nullptr),
	prev(nullptr)
{
}
template<typename T>
inline int TSimpleDoubleLL<T>::checkNextIsNull() //检查下一个节点是否为nullptr
{
	if (this->next == nullptr)
	{
		std::cout << "ERROR: this->next == nullptr; in " << this << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename T>
inline int TSimpleDoubleLL<T>::checkPrevIsNull() //检查上一个节点是否为nullptr
{
	if (this->prev == nullptr)
	{
		std::cout << "ERROR: this->prev == nullptr; in " << this << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename T>
T TSimpleDoubleLL<T>::getData(int pos) //获取pos节点的data
{
	TSimpleDoubleLL* point = this; //loop
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
int TSimpleDoubleLL<T>::getDataArray(std::string* array, int pos, int length) //将pos到length间的节点data赋到array[0 to length]
{
	if (array == nullptr) //check array
	{
		std::cout << "array is nullptr!" << std::endl;
		return -1;
	}
	if (array + length - 1 == nullptr) //check array[length - 1]
	{
		std::cout << "length is wrong!" << std::endl;
		return -2;
	}
	array[pos] = std::to_string(this->data); //get data
	if (pos < length -1)
	{
		if (this->next == nullptr) //check next is nullptr
		{
			return -3;
		}
		this->next->getDataArray(array, length, pos + 1);
	}
	return 0;
}

template<typename T>
TSimpleDoubleLL<T>* TSimpleDoubleLL<T>::getPos(int pos) //获取pos节点的内存地址
{
	TSimpleDoubleLL* point = this; //loop
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
	/*TSimpleDoubleLL* next; //recursive
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
int TSimpleDoubleLL<T>::addData(T data, int pos) //在pos节点给data赋值
{
	TSimpleDoubleLL* point = this; //loop
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
int TSimpleDoubleLL<T>::addList(T data, int pos) //在pos节点后添加新节点, 并赋data
{
	if (pos == -1) //create in head, in fact it just create next to head and copy head, add new data and next in head 
	{
		TSimpleDoubleLL* pointerBuffer = this->next;
		TSimpleDoubleLL* newNode = new TSimpleDoubleLL(this->data);
		this->next = newNode;
		newNode->next = pointerBuffer;
		this->data = data;
		std::cout << "added " << data << " in [" << pos << "] ;add type: head" << std::endl;
		return 0;
	}
	TSimpleDoubleLL* point = this;
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
	if (point->next == nullptr) //create in tail
	{
		TSimpleDoubleLL* newNode = new TSimpleDoubleLL(data);
		newNode->prev = point;
		point->next = newNode;
		std::cout << "added " << data << " in [" << pos << "] ;add type: tail" << std::endl;
		return 0;
	}
	else
	{
		TSimpleDoubleLL* newNode = new TSimpleDoubleLL(data);
		newNode->prev = this;
		TSimpleDoubleLL* pointerBuffer = this->next;
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
		if (this->next == nullptr) //create in tail
		{
			TSimpleDoubleLL* newNode = new TSimpleDoubleLL(data);
			newNode->prev = this;
			this->next = newNode;
			std::cout << "added "  << data << " in [" << pos << "] ;add type: tail" << std::endl;
			return 0;
		}
		else
		{
			TSimpleDoubleLL* newNode = new TSimpleDoubleLL(data);
			newNode->prev = this;
			TSimpleDoubleLL* pointerBuffer = this->next;
			this->next = newNode;
			this->next->next = pointerBuffer;
			std::cout << "added "  << data << " in [" << pos << "] ;add type: insert" << std::endl;
			return 0;
		}
	}*/
	return 0;
}

template<typename T>
T TSimpleDoubleLL<T>::delList(int pos) //删除pos节点
{
	T deletedData = 0;
	if (pos == 0) //del the head, in fact it just copy this->next, then delete this->next
	{
		if (this->next == nullptr) //No node left
		{
			deletedData = this->data;
			this->data = 0;
			return deletedData;
		}
		deletedData = this->data;
		TSimpleDoubleLL* pointerBuffer = this->next->next;
		T data = this->next->data;
		delete this->next;
		this->next = pointerBuffer;
		this->data = data;
		std::cout << "deleted [" << pos << "] ;delete type: head" << std::endl;
		return 0;
	}
	TSimpleDoubleLL* pointerBuffer = this; //loop
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
	if (pointerBuffer->next == nullptr) //del the tail
	{
		pointerBuffer->prev->next = nullptr;
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
	//		TSimpleDoubleLL* pointerBuffer = this->next->next;
	//		T data = this->next->data;
	//		deletedData = this->data;
	//		delete this->next;
	//		this->next = pointerBuffer;
	//		this->data = data;
	//		std::cout << "deleted [" << pos << "] ;delete type: head" << std::endl;
	//		return 0;
	//	}
	//	else if (this->next == nullptr) //del the tail
	//	{
	//		this->prev->next = nullptr; //flash prev.next to prevent wrong recursive
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
int TSimpleDoubleLL<T>::getLength() //递归获取链表长度 效率可能过低 推荐使用setLength()进行记录而非直接调用
{
	if (this->next == nullptr) //check if this->next == nullptr, that return tail
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
int TSimpleDoubleLL<T>::setLength() //将链表长度记录到this->data
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
//栈实现 父类:TSimpleDoubleLL
//----------------------
template<typename T>
class TStackSDLL : private TSimpleDoubleLL<T> //使用前请务必使用setLength()方法检测链表长度!!
{
public:
	void push(T data);
	T pop();
	T peek();
	using TSimpleDoubleLL<T>::TSimpleDoubleLL; //C++11
	//TStackSDLL() : TSimpleDoubleLL<T>(1){};
	using TSimpleDoubleLL<T>::getDataArray;
	using TSimpleDoubleLL<T>::getLength;
	using TSimpleDoubleLL<T>::setLength;
};

template<typename T>
void TStackSDLL<T>::push(T data)
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
T TStackSDLL<T>::pop()
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
T TStackSDLL<T>::peek()
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
//队列实现 父类:TSimpleDoubleLL
//----------------------
template<typename T>
class TQueueSDLL : private TSimpleDoubleLL<T>
{
public:
	void push(T data);
	T pop();
	T peek();
	using TSimpleDoubleLL<T>::TSimpleDoubleLL; //C++11
	using TSimpleDoubleLL<T>::getDataArray;
	using TSimpleDoubleLL<T>::getLength;
	using TSimpleDoubleLL<T>::setLength;
};

template<typename T>
void TQueueSDLL<T>::push(T data)
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
T TQueueSDLL<T>::pop()
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
T TQueueSDLL<T>::peek()
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
