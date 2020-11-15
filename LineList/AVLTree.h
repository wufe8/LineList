#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <vector>
#include <string>

//----------------------
//二叉查找树 SearchTree 所有节点均符合:左儿子<父亲<右儿子
//----------------------
template<typename T>
class SearchTree
{
private:
	T node;
	SearchTree<T>* left;
	SearchTree<T>* right;
	void printAllR();                      // 中遍历打印所有节点 实际代码
public:
	SearchTree(T elem = 0);                // 构造函数
	~SearchTree();                         // 析构函数
	void clone(const SearchTree* target);  // 拷贝类
	T getNode();                           // 返回node成员变量
	bool insert(T elem);                   // 添加结点
	SearchTree<T>* find(T elem);           // 查找节点 返回节点地址
	bool remove(T elem);                   // 删除节点 有则返回1 无则返回0
	SearchTree<T>*  findMin();             // 查找最小节点 返回节点地址
	void printAll();                       // 中遍历打印所有节点 初步引用
};

//----------------------
//AVL树 原于二叉查找树 SearchTree
//属于平衡树 最大节点高度差不大于1
//通过旋转达到效果
//----------------------
//template<typename T>
//class AVLTree
//{
//private:
//public:

//};

template<typename T>
SearchTree<T>::SearchTree(T elem)
	:node(elem)
{
	this->left   = nullptr;
	this->right  = nullptr;
}

template<typename T>
SearchTree<T>::~SearchTree()
{

}

template<typename T>
void SearchTree<T>::clone(const SearchTree<T>* target)
{
	this->node  = target->node;
	this->left  = target->left;
	this->right = target->right;
}

template<typename T>
T SearchTree<T>::getNode()
{
	return this->node;
}

template<typename T>
bool SearchTree<T>::insert(T elem)
{
	if (elem < this->node) //左节点递归
	{
		if (this->left == nullptr)
		{
			this->left = new SearchTree<T>(elem);
			return true;
		}
		else
		{
			return this->left->insert(elem);
		}
	}
	else if (elem > this->node) //右节点递归
	{
		if (this->right == nullptr)
		{
			this->right = new SearchTree<T>(elem);
			return true;
		}
		else
		{
			return this->right->insert(elem);
		}		
	}
	else //二叉树不允许有相同内容的节点
	{
		//std::cout << "[ERROR] binary search tree not allow have several same node" << std::endl;
		return false;
	}
}

template<typename T>
SearchTree<T>* SearchTree<T>::find(T elem) // 查找节点 返回节点地址
{
	if (this == nullptr) //找不到elem 返回nullptr
	{
		return nullptr;
	}
	if (elem < this->node) //左节点递归
	{
		return this->left->find(elem);
	}
	else if (elem > this->node) //右节点递归
	{
		return this->right->find(elem);
	}
	else //找到elem 返回地址
	{
		return this;
	}
}

template<typename T>
bool SearchTree<T>::remove(T elem)
{
	SearchTree<T>* ptr = this->find(elem);   //递归获取节点
	if (ptr->left != nullptr && ptr->right != nullptr)
	{
		SearchTree<T>* closestNode = ptr->right->findMin(); //获取右子节点中的最小节点 应为最接近原节点的值(之一)
		ptr->node = closestNode->node;
		ptr->right->remove(closestNode->node);
	}
	else
	{
		SearchTree<T>* copyTarget = (ptr->left == nullptr) ? ptr->right : ptr->left;
		ptr->clone(copyTarget); //拷贝函数
		delete copyTarget;
	}
	return true;
}

template<typename T>
SearchTree<T>* SearchTree<T>::findMin()
{
	if (this == nullptr)
	{
		return nullptr;
	}
	if (this->left == nullptr)
	{
		return this;
	}
	return this->left->findMin();
}

template<typename T>
void SearchTree<T>::printAllR()
{
	if (this == nullptr)
	{
		return;
	}
	this->left->printAllR();
	std::cout << this->node << " ";
	this->right->printAllR();
}

template<typename T>
void SearchTree<T>::printAll()
{
	printAllR();
	std::cout << std::endl;
}

#endif
