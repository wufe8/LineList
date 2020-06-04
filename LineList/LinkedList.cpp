#include "LineList.h"
#include <iostream>

TLinkedList::TLinkedList(int data) :
	data(data),
	next(NULL),
	prev(NULL)
{
}

inline int TLinkedList::checkNextIsNull() //检查下一个节点是否为NULL
{
	if (this->next == NULL)
	{
		//std::cout << "ERROR: this->next == NULL; in " << this << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

inline int TLinkedList::checkPrevIsNull() //检查上一个节点是否为NULL
{
	if (this->prev == NULL)
	{
		//std::cout << "ERROR: this->prev == NULL; in " << this << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

int TLinkedList::getData(int pos) //获取pos节点的data
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
	/*int data; //recursive
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

int TLinkedList::getDataAlloy(int* alloy, int length, int pos) //将pos到length间的节点data赋到alloy[0 to length]
{
	if (alloy == NULL) //check alloy
	{
		//std::cout << "alloy is NULL!" << std::endl;
		return -1;
	}
	if (alloy + length - 1 == NULL) //check alloy[length - 1]
	{
		//std::cout << "length is wrong!" << std::endl;
		return -2;
	}
	alloy[pos] = this->data; //get data
	if (pos < length -1)
	{
		if (this->next == NULL) //check next is NULL
		{
			return -3;
		}
		this->next->getDataAlloy(alloy, length, pos + 1);
	}
	return 0;
}

TLinkedList* TLinkedList::getPos(int pos) //获取pos节点的内存地址
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

int TLinkedList::addData(int data, int pos) //在pos节点给data赋值
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

int TLinkedList::addList(int data, int pos) //在pos节点后添加新节点, 并赋data
{
	if (pos == -1) //create in head, in fact it just create next to head and copy head, add new data and next in head 
	{
		TLinkedList* buffer = this->next;
		TLinkedList* newNode = new TLinkedList(this->data);
		this->next = newNode;
		newNode->next = buffer;
		this->data = data;
		//std::cout << "add type: head" << std::endl;
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
		//std::cout << "add type: tail" << std::endl;
		return 0;
	}
	else
	{
		TLinkedList* newNode = new TLinkedList(data);
		newNode->prev = this;
		TLinkedList* buffer = this->next;
		this->next = newNode;
		this->next->next = buffer;
		//std::cout << "add type: insert" << std::endl;
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
			//std::cout << "add type: tail" << std::endl;
			return 0;
		}
		else
		{
			TLinkedList* newNode = new TLinkedList(data);
			newNode->prev = this;
			TLinkedList* buffer = this->next;
			this->next = newNode;
			this->next->next = buffer;
			//std::cout << "add type: insert" << std::endl;
			return 0;
		}
	}*/
	return 0;
}

int TLinkedList::delList(int pos) //删除pos节点
{
	if (pos == 0) //del the head, in fact it just copy this->next, then delete this->next
	{
		if (this->next == NULL)
		{
			//std::cout << "ERROR: No node left!" << std::endl;
			return -1;
		}
		TLinkedList* buffer = this->next->next;
		int data = this->next->data;
		delete this->next;
		this->next = buffer;
		this->data = data;
		//std::cout << "delete type: head" << std::endl;
		return 0;
	}
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
	if (point->next == NULL) //del the tail
	{
		point->prev->next = NULL;
		delete point;
		//std::cout << "delete type: tail" << std::endl;
	}
	else //del the middle
	{
		point->prev->next = point->next;
		point->next->prev = point->prev;
		delete point;
		//std::cout << "delete type: middle" << std::endl;
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
	//		TLinkedList* buffer = this->next->next;
	//		int data = this->next->data;
	//		delete this->next;
	//		this->next = buffer;
	//		this->data = data;
	//		//std::cout << "delete type: head" << std::endl;
	//		return 0;
	//	}
	//	else if (this->next == NULL) //del the tail
	//	{
	//		this->prev->next = NULL; //flash prev.next to prevent wrong recursive
	//		delete this;
	//		//std::cout << "delete type: tail" << std::endl;
	//	}
	//	else //del the middle
	//	{
	//		this->prev->next = this->next;
	//		this->next->prev = this->prev;
	//		delete this;
	//		//std::cout << "delete type: middle" << std::endl;
	//	}
	//}
	return 0;
}

int TLinkedList::getLength() //递归获取链表长度 效率可能过低 推荐使用setLength()进行记录而非直接调用
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

int TLinkedList::setLength() //将链表长度记录到this->data
{
	this->data = getLength();
	if (this->data == 0)
	{
		//std::cout << "ERROR: fail to get linkedList length.";
		return 1;
	}
	return 0;
}