#include "LineList.h"
#include <iostream>

#include "pch.h"

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