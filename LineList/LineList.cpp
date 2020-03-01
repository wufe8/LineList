#include "LineList.h"
#include <iostream>

TList::TList(int data) :
	data(data),
	next(NULL),
	prev(NULL)
{
}

int TList::checkNextIsNull()
{
	if (this->next == NULL)
	{
		std::cout << "NULL next found!" << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

int TList::checkPrevIsNull()
{
	if (this->prev == NULL)
	{
		std::cout << "NULL prev found!" << std::endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

int TList::getData(int pos)
{
	int data;
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
	return data;
}

int TList::getDataAlloy(int* alloy, int length, int pos)
{
	if (alloy == NULL) //check alloy
	{
		std::cout << "alloy is NULL!" << std::endl;
		return -1;
	}
	if (alloy + length - 1 == NULL) //check alloy[length - 1]
	{
		std::cout << "length is wrong!" << std::endl;
		return -2;
	}
	alloy[pos] = this->data; //get data
	if (pos < length -1)
	{
		if (this->checkNextIsNull()) //check next is NULL
		{
			return -3;
		}
		this->next->getDataAlloy(alloy, length, pos + 1);
	}
	return 0;
}

TList* TList::getPos(int pos)
{
	TList* next;
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
	}
	return next;
}

int TList::addData(int data, int pos)
{
	if (pos > 0)
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
	}
	return 0;
}

int TList::addList(int data, int pos)
{
	if (pos > 0)
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
			TList* next = new TList(data);
			next->prev = this;
			this->next = next;
			std::cout << "add type: tail" << std::endl;
			return 0;
		}
		else
		{
			TList* next = new TList(data);
			next->prev = this;
			TList* buffer = this->next;
			this->next = next;
			this->next->next = buffer;
			std::cout << "add type: insert" << std::endl;
			return 0;
		}
	}
	return 0;
}

int TList::delList(int pos)
{
	if (pos > 0)
	{
		if (checkNextIsNull())
		{
			return -1;
		}
		this->next->delList(pos - 1);
	}
	else
	{
		if (this->next == NULL) //del the tail
		{
			this->prev = NULL;
			delete this;
			std::cout << "delete type: tail" << std::endl;
		}
		else if (this->prev == NULL) //del the head, in fact it just copy this->next, then delete this->next
		{
			TList* next = this->next->next;
			int data = this->next->data;
			delete this->next;
			this->next = next;
			this->data = data;
			std::cout << "delete type: head" << std::endl;
		}
		else
		{
			this->prev->next = this->next;
			this->next->prev = this->prev;
			delete this;
			std::cout << "delete type: middle" << std::endl;
		}

	}
	return 0;
}

int TList::getLength()
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